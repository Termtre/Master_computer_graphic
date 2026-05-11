#pragma once

#include <glad/glad.h>
#include <stdexcept>
#include <vector>

struct VertexAttribute
{
    GLuint index;          // номер атрибута (location в шейдере)
    GLint size;            // количество компонентов
    GLenum type;
    GLboolean normalized;
    GLsizei stride; 
    size_t offset;
};

class Buffers
{

private:
    GLuint VAO = 0;
    GLuint VBO = 0;
    GLuint EBO = 0;
    bool hasIndices = false;

public:
    Buffers() = default;

    void setupBuffers(
        const std::vector<GLfloat>& vertices,
        const std::vector<unsigned int>& indices = {},
        const std::vector<VertexAttribute>& attributes = {})
    {
        if (vertices.empty())
            throw std::invalid_argument("Vertices data is empty");

        cleanup();

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        if (!indices.empty())
        {
            glGenBuffers(1, &EBO);
            hasIndices = true;
        }

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER,
                     vertices.size() * sizeof(GLfloat),
                     vertices.data(),
                     GL_STATIC_DRAW);

        if (attributes.empty())
        {
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,3 * sizeof(float), nullptr);
            glEnableVertexAttribArray(0);
        }
        else
        {
            for (const auto& attr : attributes)
            {
                glVertexAttribPointer(
                    attr.index,
                    attr.size,
                    attr.type,
                    attr.normalized,
                    attr.stride,
                    reinterpret_cast<void*>(attr.offset));
                glEnableVertexAttribArray(attr.index);
            }
        }

        if (hasIndices)
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                         indices.size() * sizeof(unsigned int),
                         indices.data(),
                         GL_STATIC_DRAW);
        }

        glBindVertexArray(0);

        GLenum error = glGetError();
        if (error != GL_NO_ERROR)
            throw std::runtime_error("OpenGL error in setupBuffers: " + std::to_string(error));
    }

    ~Buffers()
    {
        cleanup();
    }

    Buffers(const Buffers&) = delete;
    Buffers& operator=(const Buffers&) = delete;

    GLuint getVAO() const { return VAO; }
    GLuint getVBO() const { return VBO; }
    GLuint getEBO() const { return EBO; }
    bool hasIndexBuffer() const { return hasIndices; }

private:
    void cleanup()
    {
        if (VAO) glDeleteVertexArrays(1, &VAO);
        if (VBO) glDeleteBuffers(1, &VBO);
        if (EBO) glDeleteBuffers(1, &EBO);
        VAO = VBO = EBO = 0;
        hasIndices = false;
    }
};