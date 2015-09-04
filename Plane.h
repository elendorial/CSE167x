#ifndef __PLANE__
#define __PLANE__

#include "GeometricObject.h"

class Plane: public GeometricObject{

	public:

		Plane(void);

		Plane(const Point3D& point, const Normal& normal);

		Plane(const Plane& plane);

		virtual Plane* clone(void) const;

		Plane& operator= (const Plane& rhs);

		virtual ~Plane(void);

		virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const;

		virtual void set_color(float r, float g, float b);

		virtual RGBColor get_color() const;

	private:

		Point3D a;
		Normal n;

		static const double kEpsilon;

};

inline void Plane::set_color(float r, float g, float b) {

	temp_color.r = r;
	temp_color.g = g;
	temp_color.b = b;
}

inline RGBColor Plane::get_color() const {
	return (temp_color);
}

#endif