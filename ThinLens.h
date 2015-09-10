#ifndef __THINLENS__
#define __THINLENS__

#include "Point2D.h"
#include "Camera.h"
#include "Vector3D.h"

class World;
class Sampler;

class ThinLens: public Camera {

	public:

		ThinLens();

		ThinLens(const ThinLens& th);

		virtual Camera* clone(void) const;

		ThinLens& operator= (const ThinLens& rhs);

		virtual ~ThinLens();

		void set_sampler(Sampler* sp);

		Vector3D ray_direction(const Point2D& pixel_point, const Point2D& lens_point) const;

		virtual void render_scene(World& w);

		void set_view_distance(float _d);

		void set_zoom(float zoom_factor);

		void set_focal_distance(float dist);

		void set_lens_radius(float r);

	private:

		float lens_radius;
		float d;
		float f;
		float zoom;
		Sampler* sampler_ptr;

};

inline void ThinLens::set_view_distance(float _d) {
	d = _d;
}

inline void ThinLens::set_zoom(float zoom_factor) {
	zoom = zoom_factor;
}

inline void ThinLens::set_focal_distance(float dist) {
	f = dist;
}

inline void ThinLens::set_lens_radius(float r) {
	lens_radius = r;
}



#endif