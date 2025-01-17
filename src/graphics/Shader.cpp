#include "Shader.hpp"

#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/type_ptr.hpp>


// Origin -> https://github.com/MihailRis/VoxelEngine-Cpp/blob/main/src/graphics/core/Shader.cpp


const static std::string ABSOLUTE_PATH = "E:/Cpp/FerrumEngine/";

Shader::Shader(unsigned int id) : id(id) {
}

void Shader::use() {
	glUseProgram(id);
}

void Shader::uniformMatrix(std::string name, glm::mat4 matrix) {
    GLuint transformLoc = glGetUniformLocation(id, name.c_str());
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(matrix));
}

Shader::~Shader() {
	glDeleteProgram(id);
}

Shader* load_shader(std::string vertexFile, std::string fragmentFile) {
    //Reading Files
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions(std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::badbit);
    try {
        vShaderFile.open(ABSOLUTE_PATH + vertexFile);
        fShaderFile.open(ABSOLUTE_PATH + fragmentFile);
        std::stringstream vShaderStream, fShaderStream;

        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure& e) {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        return nullptr;
    }
    const GLchar* vShaderCode = vertexCode.c_str();
    const GLchar* fShaderCode = fragmentCode.c_str();

    GLint success;
    GLchar infoLog[512];

    //Vertex Shader
    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, nullptr);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
        std::cerr << "SHADER::VERTEX: compilatinon failed" << std::endl;
        std::cerr << infoLog << std::endl;
        return nullptr;
    }

    //Fragment Shader
    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, nullptr);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
        std::cerr << "SHADER::FRAGMENT: compilatinon failed" << std::endl;
        std::cerr << infoLog << std::endl;
        return nullptr;
    }

    //Shader Program
    GLuint id = glCreateProgram();
    glAttachShader(id, vertex);
    glAttachShader(id, fragment);
    glLinkProgram(id);

    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(id, 512, nullptr, infoLog);
        std::cerr << "SHADER::PROGRAM: compilatinon failed" << std::endl;
        std::cerr << infoLog << std::endl;

        glDeleteShader(vertex);
        glDeleteShader(fragment);
        glDeleteProgram(id);
        return nullptr;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return new Shader(id);
}