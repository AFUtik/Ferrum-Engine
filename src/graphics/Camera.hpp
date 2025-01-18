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
	float cur_x = 0.0f;
	float cur_y = 0.0f;
	float cur_z = 0.0f;

	float scale = 1.0f;
	float fov;
	float aspect;
	float zNear;
	float zFar;

	vec3 *followed; // Position vec3 of followed entity/object //
	vec3 position;
	mat4 rotation;
	Camera(vec3 position, float fov);

	void update();
	void set_xyz(float x, float y, float z);
	void rotate(float x, float y, float z);
	void follow(vec3 &pos);
	void unfollow();

	mat4 getOrthoProjview();
	mat4 getPerspectiveProjview();
};

#endif /* WINDOW_CAMERA_H_ */