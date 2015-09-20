#include "Reflective.h"

Reflective::Reflective(void)
:	Phong()
{}

Reflective::Reflective(const Reflective& rm)
:	Phong(rm)
{}

Reflective& Reflective::operator= (const Reflective& rhs){
	if(this == &rhs)
		return(*this);

	Phong::operator=(rhs);

	return(*this);
}

Reflective* Reflective::clone(void) const {
	return(new Reflective(*this));
}

Reflective::~Reflective()
{}

RGBColor Reflective::shade(ShadeRec& sr) {
	RGBColor L(Phong::shade(sr));

	Vector3D wo = -sr.ray.d;
	float ndotwo = sr.normal * wo;
	Vector3D wi = -wo + 2.0 * sr.normal * ndotwo;
	Ray reflected_ray(sr.hit_point, wi);

	L += specular * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1);

	return(L);

}