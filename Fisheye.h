#ifndef __FISHEYE__
#define __FISHEYE__

#include "Point2D.h"
#include "Camera.h"
#include "Vector3D.h"

class World;

class Fisheye: public Camera {

	public:

		Fisheye();

		Fisheye(const Fisheye& fs);

		Fisheye& operator= (const Fisheye& fs);

		virtual ~Fisheye();

		Vector3D ray_direction(const Point2D& p, const int hres, const int vres, const float s, float& r) const;

		virtual void render_scene(World& w);

		virtual Fisheye* clone(void) const;

	private:

		float psi_max;
};

#endif