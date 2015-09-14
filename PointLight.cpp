#include "PointLight.h"

PointLight::PointLight()
:	Light(),
	ls(1.0),
	color(1.0),
	location(0, 1, 0)
{}

PointLight::PointLight(const PointLight& pl)
:	Light(pl),
	ls(pl.ls),
	color(pl.color),
	location(pl.location)
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

	return(*this);
}

PointLight::~PointLight() {}

Vector3D PointLight::get_direction(ShadeRec& sr) {
	return((location - sr.hit_point).hat());
}

RGBColor PointLight::L(ShadeRec& sr) {
	return (ls * color);
}

