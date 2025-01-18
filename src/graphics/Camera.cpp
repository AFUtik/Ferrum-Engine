#include "Camera.hpp"
#include "../window/Window.hpp"

#include <glm/ext.hpp>


Camera::Camera(vec3 position, float fov) : position(position), fov(fov), rotation(1.0f) {
	updateVectors();
}

void Camera::set_xyz(float x, float y, float z) {
	position = glm::vec3(x, y, z);
}

void Camera::updateVectors() {
	x_dir = vec3(rotation * vec4(1, 0, 0, 1));
	y_dir = vec3(rotation * vec4(0, 1, 0, 1));
	z_dir = vec3(rotation * vec4(0, 0, -1, 1));
	
}

void Camera::rotate(float x, float y, float z) {
	rotation = glm::rotate(rotation, z, vec3(0, 0, 1));
	rotation = glm::rotate(rotation, y, vec3(0, 1, 0));
	rotation = glm::rotate(rotation, x, vec3(1, 0, 0));

	updateVectors();
}

mat4 Camera::getOrthoProjview() {
	return glm::ortho(-aspect * scale, aspect * scale, -scale, scale, zNear, zFar) * glm::lookAt(position, position + z_dir, y_dir);
}

mat4 Camera::getPerspectiveProjview() {
	return glm::perspective(fov, aspect, zNear, zFar) * glm::lookAt(position, position + z_dir, y_dir);;
}
 
//mat4 Camera::getView() {
//	return glm::lookAt(position, position + z_dir, y_dir);
//}