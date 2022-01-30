#pragma once
#include <vector>
#include "Mesh.h"
#include "../GameLogic/Tile/Tile.h"
#include "Transform.h"
#include "Asset/FAssetHandler.h"

namespace front 
{
	class FrontendUtils
	{
		static std::vector<Mesh> getMeshes(const std::string& modelKey, const AssetHandler& handler, Transform transform, std::vector<Mesh>& meshes);
		static std::vector<Mesh> getMeshes(const std::vector<std::vector<Tile>>& map, const AssetHandler& handler, int x, int y);
	public:
		static std::map<std::string, Mesh> createMapMesh(const std::vector<std::vector<Tile>>& map, const AssetHandler& handler);
	};

}
