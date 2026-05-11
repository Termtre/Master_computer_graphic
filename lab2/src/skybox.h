#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <memory>

class Skybox
{

private:
    GLuint textureID = 0;
    GLuint VAO = 0, VBO = 0;
    void setupCube();
    
public:
    Skybox();
    ~Skybox();

    bool loadCrossMap(const std::string& url);

    // order: right, left, top, bottom, front, back
    bool loadCubeMap(const std::vector<std::string>& faces);

    void draw(const glm::mat4& view, const glm::mat4& projection) const;
};