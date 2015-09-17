#ifndef __CAMERA__
#define __CAMERA__

#include "Point3D.h"
#include "Vector3D.h"

class World;

class Camera {

	public:

		Camera();

		Camera(const Camera& camera);

		virtual Camera* clone(void) const = 0;

		virtual ~Camera();

		virtual void render_scene(World& w) = 0;

		void set_eye(const Point3D& p);

		void set_eye(const float x, const float y, const float z);

		void set_lookat(const Point3D& p);

		void set_lookat(const float x, const float y, const float z);

		void set_up_vector(const Vector3D& u);

		void set_up_vector(const float x, const float y, const float z);

		void set_roll(const float ra);

		void set_exposure_time(const float exposure);

		void compute_uvw(void);

	protected:

		Point3D eye;
		Point3D lookat;
		float ra;
		Vector3D u, v, w;
		Vector3D up;
		float exposure_time;
		

		Camera& operator= (const Camera& camera);

};

inline void Camera::set_eye(const Point3D& p) {
	eye = p;
}

inline void Camera::set_eye(const float x, const float y, const float z) {
	eye.x = x; eye.y = y; eye.z = z;
}

inline void Camera::set_lookat(const Point3D& p) {
	lookat = p;
}

inline void Camera::set_lookat(const float x, const float y, const float z) {
	lookat.x = x; lookat.y = y; lookat.z = z;
}

inline void Camera::set_up_vector(const Vector3D& u) {
	up = u;
}

inline void Camera::set_up_vector(const float x, const float y, const float z) {
	up.x = x; up.y = y; up.z = z;
}

inline void Camera::set_roll(const float r) {
	ra = r;
}

inline void Camera::set_exposure_time(const float exposure){
	exposure_time = exposure;
}

#endif