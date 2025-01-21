#include "Camera.hpp"
#include "../window/Window.hpp"

#include <glm/ext.hpp>


Camera::Camera(vec3 pos, float fov) : fov(fov), rotation(1.0f), position(pos), followed(&position), last_pos(0.0f), smooth_factor(0.05f) {
	updateVectors();
}

void Camera::unfollow() {
	followed = &position;

}

void Camera::follow(vec3 &pos) {
	followed = &pos;
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
    glm::vec3 new_position = glm::mix(this->last_pos, *followed, smooth_factor);

	mat4 projview = glm::ortho(-aspect * scale, aspect * scale, -scale, scale, zNear, zFar) * 
	glm::lookAt(new_position + vec3(0.0f, 0.0f, 0.5f), new_position + z_dir, y_dir);
	this->last_pos = new_position;
	return projview;
}

mat4 Camera::getPerspectiveProjview() {
	return glm::perspective(fov, aspect, zNear, zFar) * glm::lookAt(floor((*followed/(1.0f/16.0f))*1.0f/16.0f), *followed + z_dir, y_dir);;
}
 
//mat4 Camera::getView() {
//	return glm::lookAt(position, position + z_dir, y_dir);
//}