#include"Camera.h"
void Camera::update_camera()
{
	glm::vec3 front;
	front.x = cos(glm::radians(yaw_))*cos(glm::radians(pitch_));
	front.y = sin(glm::radians(pitch_));
	front.z = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));
	front_ = glm::normalize(front);
	right_ = glm::cross(front_, world_up_);
	up_ = glm::cross(right_, front_);
}

Camera::Camera()
{
	position_ = glm::vec3(0.0f, 0.0f, 0.0f);
	up_ = glm::vec3(0.0f, 1.0f, 0.0f);
	front_ = glm::vec3(0.0f, 0.0f, -1.0f);
	right_ = glm::vec3(1.0f, 0.0f, 0.0f);
	world_up_ = glm::vec3(0.0f, 1.0f, 0.0f);

	yaw_ = 90.0f;
	pitch_ = 0.0f;
	move_speed_ = 1.0f;
	mouse_sensitivity_ = 1.0f;
	zoom_ = 45.0f;
}

Camera::Camera(glm::vec3 _pos, glm::vec3 _up, float _yaw, float _pitch)
{
	rebuild(_pos, _up, _yaw, _pitch);
}

void Camera::rebuild(glm::vec3 _pos, glm::vec3 _up, float _yaw, float _pitch)
{
	position_ = _pos;
	up_ = _up;
	yaw_ = _yaw;
	pitch_ = _pitch;
	world_up_ = glm::vec3(0.0f, 0.0f, 1.0f);
	update_camera();
}

glm::mat4 Camera::get_view_matrix()
{
	return glm::lookAt(position_, position_ + front_, world_up_);
}

void Camera::move_camera(CameraMovement _direction, float _delta_time)
{
	float distance = _delta_time * move_speed_;
	switch (_direction)
	{
	case CAMERA_FORWARD:
		position_ += (front_*distance);
		break;
	case CAMERA_BACKWARD:
		position_ -= (front_*distance);
		break;
	case CAMERA_LEFT:
		position_ -= (right_*distance);
		break;
	case CAMERA_RIGHT:
		position_ += (right_*distance);
		break;
	case CAMERA_UP:
		position_ += (world_up_*distance);
		break;
	case CAMERA_DOWN:
		position_ -= (world_up_*distance);
		break;
	}
	update_camera();
}

void Camera::ratate_camera(float _xoffset, float _yoffset, bool _constrain_pitch)
{
	_xoffset *= mouse_sensitivity_;
	_yoffset *= mouse_sensitivity_;

	yaw_ += _xoffset;
	pitch_ -= _yoffset;

	if (_constrain_pitch)
	{
		if (pitch_ >= 89.0f)
		{
			pitch_ = 89.0f;
		}
		if (pitch_ < -89.0f)
		{
			pitch_ = -89.0f;
		}
	}

	update_camera();
}

void Camera::set_speed(const float speed)
{
	if (speed >= 0)
	{
		move_speed_ = speed;
	}
}

void Camera::set_mouse_sensitivity(float _sensitivity)
{
	if (_sensitivity >= 0)
		mouse_sensitivity_ = _sensitivity;
}

void Camera::set_position(float _x, float _y, float _z)
{
	position_ = { _x,_y,_z };
	update_camera();
}

void Camera::set_position(glm::vec3 _pos)
{
	position_ = _pos;
	update_camera();
}
