#pragma once
#include "third_party/Include/glm/gtc/matrix_transform.hpp"
#include "third_party/Include/glm/gtc/type_ptr.hpp"


enum  CameraMovement {
	CAMERA_FORWARD, 
	CAMERA_BACKWARD, 
	CAMERA_LEFT, 
	CAMERA_RIGHT,
	CAMERA_UP,
	CAMERA_DOWN
};

class Camera
{
private:
	//Camera attributes
	glm::vec3 position_;
	glm::vec3 up_;
	glm::vec3 front_;
	glm::vec3 right_;
	glm::vec3 world_up_;

	//Rotate
	float yaw_;
	float pitch_;

	//Camera options
	float move_speed_;
	float mouse_sensitivity_;
	float zoom_;

	//Update function
	void update_camera();
public:
	Camera();
	Camera(glm::vec3 _pos, glm::vec3 _up, float _yaw, float _pitch);
	~Camera() {};
	//Public function
	void rebuild(glm::vec3 _pos, glm::vec3 _up, float _yaw, float _pitch);
	glm::mat4 get_view_matrix();
	void move_camera(CameraMovement _direction, float _delta_time);
	void ratate_camera(float _xoffset, float _yoffset, bool _constrain_pitch);
	void zoom_camera(float _offset) {};
	void set_speed(const float speed);
	void set_mouse_sensitivity(float _sensitivity);
	void set_position(float _x, float _y, float _z);
	void set_position(glm::vec3 _pos);
};