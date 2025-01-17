#ifndef WINDOW_CAMERA_HPP
#define WINDOW_CAMERA_HPP

#include <glm/glm.hpp>
using namespace glm;

class Camera {
	void updateVectors();
public:
	vec3 x_dir;
	vec3 y_dir;
	vec3 z_dir;

	vec3 position;
	float fov;
	mat4 rotation;
	Camera(vec3 position, float fov);

	void set_xyz(float x, float y, float z);

	void rotate(float x, float y, float z);

	mat4 getProjection();
	mat4 getView();
};

#endif /* WINDOW_CAMERA_H_ */