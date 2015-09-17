#include "PointLight.h"

PointLight::PointLight()
:	Light(),
	ls(1.0),
	color(1.0),
	location(0, 1, 0),
	shadows(false)
{}

PointLight::PointLight(const PointLight& pl)
:	Light(pl),
	ls(pl.ls),
	color(pl.color),
	location(pl.location),
	shadows(pl.shadows)
{}

Light* PointLight::clone(void) const {
	return(new PointLight(*this));
}


PointLight& PointLight::operator= (const PointLight& rhs) {
	if(this == &rhs)
		return(*this);

	ls = rhs.ls;
	color = rhs.color;
	location = rhs.location;
	shadows = rhs.shadows;

	return(*this);
}

PointLight::~PointLight() {}

Vector3D PointLight::get_direction(ShadeRec& sr) {
	return((location - sr.hit_point).hat());
}

RGBColor PointLight::L(ShadeRec& sr) {
	float distance = location.d_squared(sr.hit_point);
	return ((ls * color));
}

bool PointLight::in_shadow(const Ray& ray, const ShadeRec& sr) const {
	float t;
	int num_objects = sr.w.objects.size();
	float d = location.distance(ray.o);

	for(int j = 0; j < num_objects; j++)
		if(sr.w.objects[j]->shadow_hit(ray, t) && t < d)
			return(true);
	return(false);
}

bool PointLight::casts_shadows() const {
	return(shadows);
}

