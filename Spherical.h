#ifndef __SPHERICAL__
#define __SPHERICAL__

#include "Point2D.h"
#include "Camera.h"
#include "Vector3D.h"

class World;

class Spherical: public Camera {

	public:

		Spherical();

		Spherical(const Spherical& sph);

		Spherical& operator= (const Spherical& sph);

		virtual ~Spherical();

		Vector3D ray_direction(const Point2D& pp, const int hres, const int vres, const float s) const;

		virtual void render_scene(World& w);

		virtual Spherical* clone(void) const;

	private:

		float l_max;
		float psi_max;

};

#endif