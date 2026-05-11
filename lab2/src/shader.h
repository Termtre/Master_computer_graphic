#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <concepts>

struct hashShaderType
{
    size_t operator()(GLenum shaderType) const
    {
        switch(shaderType)
        {
            case GL_VERTEX_SHADER: return 1;
            case GL_GEOMETRY_SHADER: return 2;
            case GL_FRAGMENT_SHADER: return 3;
            case GL_COMPUTE_SHADER: return 4;
            default: throw std::invalid_argument("Invalid shader type");
        }
    }
};

class Shader
{
    GLenum type;
    unsigned int shaderID;
    std::string url;

    public:

    Shader(GLenum _type, const std::string& _url) : type(_type), url(_url)
    {
        if (
            type != GL_VERTEX_SHADER &&
            type != GL_FRAGMENT_SHADER &&
            type != GL_GEOMETRY_SHADER &&
            type != GL_COMPUTE_SHADER
        )
        {
            throw std::invalid_argument("Invalid shader type");
        }

        compile();
    }

    ~Shader() 
    {
        if (shaderID != 0) 
        {
            glDeleteShader(shaderID);
        }
    }

    unsigned int getShaderID() const
    {
        return shaderID;
    }

    GLenum getType() const
    {
        return type;
    }

    private:

    void compile()
    {
        std::string source = readShader(url);
        auto source_cstr = source.c_str();

        shaderID = glCreateShader(type);

        if (!shaderID)
        {
            throw std::runtime_error("Failed to create shader of type " + std::to_string(type));
        }

        glShaderSource(shaderID, 1, &source_cstr, NULL);

        glCompileShader(shaderID);

        getLog();
    }

    std::string readShader(const std::string& url)
    {
        std::ifstream file(url);

        if (!file.is_open())
        {
            throw std::runtime_error(url + " file didn't open");
        }

        std::stringstream stream;
        stream << file.rdbuf();

        return stream.str();
    }

    void getLog()
    {
        int status;
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status);

        if (!status)
        {
            char infoLog[512];
            glGetShaderInfoLog(shaderID, 512, NULL, infoLog);

            throw std::runtime_error("Error: Compilation failed " + std::string(infoLog));
        }
    }
    
};