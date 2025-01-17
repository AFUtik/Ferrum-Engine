#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <glm/glm.hpp>

class Shader {
public:
	unsigned int id;
	Shader(unsigned int id);
	~Shader();

	void uniformMatrix(std::string name, glm::mat4 matrix);
	void use();
};

extern Shader* load_shader(std::string vertexFile, std::string fragmentFile);

#endif