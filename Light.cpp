#include "Light.h"
#include "Constants.h"
#include "ShadeRec.h"

Light::Light(void) {}

Light::Light(const Light& ls) {}

Light& Light::operator= (const Light& rhs) {
	if(this == &rhs)
		return(*this);

	return(*this);
}

Light::~Light(void) {}

RGBColor Light::L(ShadeRec& s) {
	return (black);
}

bool Light::in_shadow(const Ray& ray, const ShadeRec& sr) const {
	return(false);
}

bool Light::casts_shadows() const {
	return(false);
}