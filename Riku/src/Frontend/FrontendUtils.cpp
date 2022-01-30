#include "FrontendUtils.h"
#include "Model.h"

std::vector<Mesh> front::FrontendUtils::getMeshes( const std::string& modelKey, const AssetHandler& handler, Transform transform, std::vector<Mesh>& meshes)
{
	const std::map<std::string, front::Asset>& assets = handler.getMap();
	if ( assets.find(modelKey) == assets.end())
		return {};
	
	std::vector<Vertex> vert;
	std::vector<unsigned int> indices;
	std::vector<Texture> text;
	for (const auto& model : assets.at(modelKey).assetModels)
	{
		for (auto mesh : model.model->meshes)
		{
			for (Vertex& v : mesh.vertices)
			{
				auto matrix = transform.CalculateMatrix();
				v.Position = matrix * glm::vec4(v.Position, 1);
				v.Normal = matrix * glm::vec4(v.Normal, 0);
				v.Bitangent = matrix * glm::vec4(v.Bitangent, 0);
				v.Tangent = matrix * glm::vec4(v.Tangent, 0);
			}
			meshes.push_back(mesh);
			std::vector<unsigned int> transedIndices;
			for (unsigned int& ind : mesh.indices)
				transedIndices.push_back(ind + vert.size());
			indices.insert(indices.end(), mesh.indices.begin(), mesh.indices.end());
			vert.insert(vert.end(), mesh.vertices.begin(), mesh.vertices.end());
			if (text.size() == 0)
				text = mesh.textures;
		}
	}

	return meshes;
}

std::vector<Mesh> front::FrontendUtils::getMeshes(const std::vector<std::vector<Tile>>& map, const AssetHandler& handler, int x, int y)
{
	std::vector<Mesh> meshes;
	glm::vec3 scale = { .333333f,.333333f,.333333f };
	Transform transform = Transform(glm::vec3((float)x, (float)map[x][y].height * 0.5f, (float)y), glm::vec3(), scale);
	//get sides
	for (int i = 0; i < 4; i++) {
		int dx = i % 2 ? 0 : i - 1;
		int dy = i % 2 ? i - 2 : 0;
		int dh;
		if ((x + dx < 0 || x + dx >= (int)map.size()) || y + dy < 0 || y + dy >= (int)map[0].size())
			dh = 0;
		else
			dh = map[x + dx][y + dy].height - map[x][y].height;
		Transform sideTransform;
		if (dh == 0 || std::abs(dh) >= 2) {
			sideTransform = Transform(glm::vec3((float)x + (float)dx / 3.f, (float)map[x][y].height * 0.5f,
				(float)y + (float)dy / 3.f), glm::vec3(0.0f, 90.0f * i, 0.0f), scale);
			getMeshes("_flat", handler, sideTransform, meshes);
		}
		else if (dh == 1) {
			sideTransform = Transform(glm::vec3((float)x + (float)dx / 3.f, (float)map[x][y].height * 0.5f + 0.125f,
				(float)y + (float)dy / 3.f), glm::vec3(0.0f, -90.0f * i, 0.0f), scale);
			getMeshes("_slope", handler, sideTransform, meshes);
		}
		else if (dh == -1) {
			sideTransform = Transform(glm::vec3((float)x + (float)dx / 3.f, (float)map[x][y].height * 0.5f - 0.125f,
				(float)y + (float)dy / 3.f), glm::vec3(0.0f, -90.0f * i + 180.0f, 0.0f), scale);
			getMeshes("_slope", handler, sideTransform, meshes);
		}
	}
	//draw corner
	for (int i = 0; i < 4; i++) {
		int dx = i % 2 ? 2 - i : i - 1;
		int dy = i % 2 ? i - 2 : i - 1;
		int dhx, dhy, dhz;
		{
			int dxt = dx, dyt = dy;
			if (x + dx < 0 || x + dx >= (int)map.size())
				dxt = 0;
			if (y + dy < 0 || y + dy >= (int)map[0].size())
				dyt = 0;
			dhx = map[x + dxt][y].height - map[x][y].height;
			dhy = map[x][y + dyt].height - map[x][y].height;
			dhz = map[x + dxt][y + dyt].height - map[x][y].height;
		}
		if (i % 2 == 1)
			std::swap(dhx, dhy);
		uint8_t caseUint = 0x0; //____yyxx (bits)
		if (std::abs(dhx) >= 2)
			caseUint = 0x1;
		else
			caseUint = 1 + dhx;
		if (std::abs(dhy) >= 2)
			caseUint += 0x4;
		else
			caseUint += 0x4 * (1 + dhy);
		Transform sideTransform;
		std::string type;
		switch (caseUint) {
		case 0:
			sideTransform = Transform(glm::vec3((float)x + (float)dx / 3.f, (float)map[x][y].height * 0.5f - 0.125f,
				(float)y + (float)dy / 3.f), glm::vec3(0.0f, 90.0f - 90.0f * i, 0.0f), scale);
			type = "_corner+";
			break;
		case 1:
			sideTransform = Transform(glm::vec3((float)x + (float)dx / 3.f, (float)map[x][y].height * 0.5f - 0.125f,
				(float)y + (float)dy / 3.f), glm::vec3(0.0f, -90.0f * i + 90.0f, 0.0f), scale);
			type = "_slope";
			break;
		case 2:
			sideTransform = Transform(glm::vec3((float)x + (float)dx / 3.f, (float)map[x][y].height * 0.5f,
				(float)y + (float)dy / 3.f), glm::vec3(0.0f, 90.0f * i + 90.0f, 0.0f), { -scale.x,scale.y,scale.z });
			type = "_double_corner";
			break;
		case 4:
			sideTransform = Transform(glm::vec3((float)x + (float)dx / 3.f, (float)map[x][y].height * 0.5f - 0.125f,
				(float)y + (float)dy / 3.f), glm::vec3(0.0f, -90.0f * i + 180.0f, 0.0f), scale);
			type = "_slope";
			break;
		case 5:
			sideTransform = Transform(glm::vec3((float)x + (float)dx / 3.f, (float)map[x][y].height * 0.5f,
				(float)y + (float)dy / 3.f), glm::vec3(0.0f, -90.0f * i, 0.0f), scale);
			type = "_flat";
			break;
		case 6:
			sideTransform = Transform(glm::vec3((float)x + (float)dx / 3.f, (float)map[x][y].height * 0.5f + 0.125f,
				(float)y + (float)dy / 3.f), glm::vec3(0.0f, -90.0f * i, 0.0f), scale);
			type = "_slope";
			break;
		case 8:
			sideTransform = Transform(glm::vec3((float)x + (float)dx / 3.f, (float)map[x][y].height * 0.5f,
				(float)y + (float)dy / 3.f), glm::vec3(0.0f, -90.0f * i - 180.0f, 0.0f), scale);
			type = "_double_corner";
			break;
		case 9:
			sideTransform = Transform(glm::vec3((float)x + (float)dx / 3.f, (float)map[x][y].height * 0.5f + 0.125f,
				(float)y + (float)dy / 3.f), glm::vec3(0.0f, -90.0f * i - 90.0f, 0.0f), scale);
			type = "_slope";
			break;
		case 10:
			sideTransform = Transform(glm::vec3((float)x + (float)dx / 3.f, (float)map[x][y].height * 0.5f + 0.125f,
				(float)y + (float)dy / 3.f), glm::vec3(0.0f, -90.0f - 90.0f * i, 0.0f), scale);
			type = "_corner-";
			break;
		}
		getMeshes(type, handler, sideTransform, meshes);

	}
	for (int i = 0; i < 4; i++) {
		int dx = i % 2 == 0 ? 0 : 2 - i;
		int dy = i % 2 == 0 ? i - 1 : 0;
		int dh;
		if ((x + dx < 0 || x + dx >= (int)map.size()) || y + dy < 0 || y + dy >= (int)map[0].size())
			dh = 0;
		else
			dh = map[x + dx][y + dy].height - map[x][y].height;

		if (dh < -1)
		{
			int side = i < 2 ? 1 : -1;
			for (int j = dh + 1; j < 1; j++)
			{
				for (int k = -1; k < 2; k++)
				{
					int zX = x - k * abs(dy);
					int zY = y + k * abs(dx);
					float yScale = 1 / 2.f;
					float yTransition = 0.25f;
					if (j == 0 && zX >= 0 && zY >= 0 && zX < map.size() && zY < map[0].size()
						&& map[zX][zY].height - map[x][y].height == -1)
					{
						yScale = 1 / 4.f;
						yTransition = 0.375f;
					}
					Transform clifTransform = Transform(glm::vec3(
						(float)x + 0.5f * side * (i % 2) + (i % 2 - 1) * k / 3.f,
						(float)map[x][y].height * 0.5f + 0.5f * j - yTransition,
						(float)y + (i % 2 - 1) * side * 0.5 + (i % 2) * k / 3.f),
						glm::vec3(90.0f, 0.0f, 90.0f * i), glm::vec3(1 / 3.f, yScale, 1 / 3.f));
					getMeshes("_cliff", handler, clifTransform, meshes);
				}
			}
		}

	}
	getMeshes("_flat", handler, transform, meshes);
	return meshes;
}

std::map<std::string, Mesh> front::FrontendUtils::createMapMesh(const std::vector<std::vector<Tile>>& map, const AssetHandler& handler)
{
	const std::map<std::string, front::Asset>& assets = handler.getMap();
	std::map<std::string, std::vector<Mesh>> meshes;
	for (int x = 0; x < (int)map.size(); x++)
		for (int y = 0; y < (int)map[x].size(); y++)
		{
			std::string ground = map[x][y].ground.getName();
			if (assets.find(ground) == assets.end())
				continue;
			
			auto vec = getMeshes(map, handler, x, y);
			if (meshes.find(ground) == meshes.end())
				meshes.emplace(ground, std::vector<Mesh>());
			meshes.at(ground).insert(meshes.at(ground).end(), vec.begin(), vec.end());
		}

	std::map<std::string, Mesh> meshesCombined;
	for (auto& pair : meshes)
	{

		std::vector<Vertex> vert;
		std::vector<unsigned int> indices;
		std::vector<Texture> text;
		for (Mesh& mesh : pair.second)
		{
			std::vector<unsigned int> transedIndices;
			for (unsigned int& ind : mesh.indices)
				transedIndices.push_back(ind + vert.size());
			indices.insert(indices.end(), transedIndices.begin(), transedIndices.end());
			vert.insert(vert.end(), mesh.vertices.begin(), mesh.vertices.end());
			if (text.size() == 0)
				text = mesh.textures;
		}
		Mesh mesh = Mesh(vert, indices, text);
		const Asset& assete = handler.getAsset(pair.first);
		const AssetModel& ground = assete.assetModels[0];
		if (ground.diffuse)
			mesh.textures.push_back(*ground.diffuse);
		if (ground.specular)
			mesh.textures.push_back(*ground.specular);
		if (ground.normal)
			mesh.textures.push_back(*ground.normal);
		meshesCombined.emplace(pair.first, mesh);
	}
    return meshesCombined;
}
