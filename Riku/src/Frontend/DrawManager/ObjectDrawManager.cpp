//
// Created by kamil-xkom on 08.12.2021.
//

#include "ObjectDrawManager.h"
#include "../Shader.h"
#include "../Model.h"
#include "../Window/Scene.h"
#include <iostream>

std::vector<front::DrawObject> front::ObjectDrawManager::meshes;

void drawMesh(const front::DrawObject& object, const Shader& shader, bool isChange) {
    if(!object.mesh)
        return;
    glm::mat4 mat_model = glm::mat4(1.0f);
    if(object.parent)
        mat_model=object.transform.CalculateMatrix(*object.parent);
    else
        mat_model=object.transform.CalculateMatrix();
    glm::mat4 inv_model = glm::mat4(1.0f);
    inv_model = glm::inverse(mat_model);
    inv_model = glm::transpose(inv_model);
    shader.setMat4("model", mat_model);
    shader.setMat4("ti_model", inv_model);
    //drawing
    if(isChange)
        object.mesh->ApplyDrawChanges(shader);
    object.mesh->SimpleDraw(shader);
}

void front::ObjectDrawManager::add(front::Object &object, glm::vec4 color) {
    auto& models = object.GetModel();
    for(auto& m: models.meshes) {
        meshes.emplace_back(m, object.transform, color, object.GetParent());
    }
}

//TODO: function to remove from there
void prepareShader(Shader& shader, float dayPart, const front::Transform& camera, float fogDensity, const glm::mat4& projection, const glm::mat4& view, const front::Light& light) {
    shader.use();
    shader.setMat4("projection", projection);
    shader.setMat4("view", view);
    shader.setVec3("viewPos", camera.position);
    shader.setFloat("material.shininess", 32.0f);
    //default value
    shader.setVec4("color_mod", 1.0f, 1.0f, 1.0f, 1.0f);
    //fog parameters
    shader.setFloat("fog_density",fogDensity);
    shader.setVec4("fog_color", 0.7f * dayPart, 0.7f * dayPart, 0.7f * dayPart, 1.0f);
    light.apply(shader, dayPart);
}

void front::ObjectDrawManager::draw(Shader& shader, const Scene& scene) {
    //TODO: https://learnopengl.com/Advanced-OpenGL/Instancing
    //TODO: add loading special shader
    std::sort(meshes.begin(),meshes.end(),[](const DrawObject& a, const DrawObject& b)
    {
        return a.mesh<b.mesh;
    });
    std::vector<int> changes;
    const Mesh* prevMesh=nullptr;
    //TODO: improving drawing
    for(int i=0;i<(int)meshes.size();i++) {
        if(prevMesh!=meshes[i].mesh)
            changes.push_back(i);
        prevMesh = meshes[i].mesh;
    }
    //vec4 - color
    //mat4 - model matrix
    changes.push_back((int)meshes.size());
    glm::mat4 *modelMatrices;
    for(int i=0;i<(int)changes.size()-1;i++) {
        std::cout << i << "/" << changes.size()-1 <<"\n";
        int count = changes[i]-changes[i-1];
        unsigned int buffer;
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER, count * (int)sizeof(glm::mat4), &modelMatrices[0], GL_STATIC_DRAW);
        modelMatrices = new glm::mat4[changes[i+1]-changes[i]];
        for(int j=changes[i];j<changes[i+1];j++) {
            if(meshes[j].parent)
                modelMatrices[j-changes[i+1]]=meshes[j].transform.CalculateMatrix(*meshes[j].parent);
            else
                modelMatrices[j-changes[i+1]]=meshes[j].transform.CalculateMatrix();
            std::size_t vec4Size = sizeof(glm::vec4);
            glEnableVertexAttribArray(3);
            glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)0);
            glEnableVertexAttribArray(4);
            glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(1 * vec4Size));
            glEnableVertexAttribArray(5);
            glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(2 * vec4Size));
            glEnableVertexAttribArray(6);
            glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(3 * vec4Size));

            glVertexAttribDivisor(3, 1);
            glVertexAttribDivisor(4, 1);
            glVertexAttribDivisor(5, 1);
            glVertexAttribDivisor(6, 1);

            glBindVertexArray(0);
        }
        glm::mat4 projection = glm::perspective(glm::radians(scene.config.fov), scene.aspect, 0.1f, 100.0f);
        glm::mat4 view = scene.movingCameraTransform.calculateViewMatrix();
        prepareShader(shader, 0.5f, scene.movingCameraTransform, scene.fogDensity, projection, view, scene.light);
        for(unsigned int j = 0; j < count; j++)
        {
            std::cout << "\t" << j << "\n";
            glBindVertexArray(meshes[changes[i]].mesh->getVAO());
            glDrawElementsInstanced(
                    GL_TRIANGLES, meshes[changes[i]].mesh->indices.size(), GL_UNSIGNED_INT, nullptr, count);

        }
    }
    std::cout << "Ok\n";
    delete[] modelMatrices;
    /*for(auto& m: meshes) {
        drawMesh(m, shader, prevMesh!=m.mesh);
        prevMesh = m.mesh;
    }*/
    meshes.clear();

}
