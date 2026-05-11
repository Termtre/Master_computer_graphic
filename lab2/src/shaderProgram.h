#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <variant>
#include <unordered_map>
#include <memory>
#include "shader.h"

class ShaderProgram
{
    private:
    unsigned int shaderProgramID;
    std::unordered_map<GLenum, std::shared_ptr<Shader>, hashShaderType> shaders;

    public:
    ShaderProgram(std::initializer_list<std::shared_ptr<Shader>> _shaders)
    {
        for (const auto& it : _shaders)
        {
            auto type = it->getType();
            if (shaders.find(type) != shaders.end())
            {
                throw std::invalid_argument
                    (
                        "Shader program can't have additional shader of " + std::to_string(type)
                    );
            }

            shaders[type] = it;
        }

        link();
    }

    ~ShaderProgram() 
    {
        if (shaderProgramID != 0) 
        {
            glDeleteProgram(shaderProgramID);
        }
    }

    void use() const
    {
        glUseProgram(shaderProgramID);
    }

    unsigned int getShaderProgramID() const
    {
        return shaderProgramID;
    }


    private:

    void link()
    {
        shaderProgramID = glCreateProgram();

        if (!shaderProgramID)
        {
            throw std::runtime_error("Failed to create OpenGL program");
        }

        for (const auto& it : shaders)
        {
            glAttachShader(shaderProgramID, it.second->getShaderID());
        }

        glLinkProgram(shaderProgramID);

        getLog();
    }

    void getLog()
    {
        int status;
        glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &status);
        if (!status)
        {
            char infoLog[512];
            glGetProgramInfoLog(shaderProgramID, 512, NULL, infoLog);
            throw std::runtime_error("Error: Linking failed\n" + std::string(infoLog));
        }
    }

};