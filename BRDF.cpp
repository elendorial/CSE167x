#include "Constants.h"
#include "BRDF.h"

BRDF::BRDF(void)
:	sampler_ptr(NULL)
{}

BRDF::BRDF(const BRDF& brdf) {
	if(brdf.sampler_ptr)
		sampler_ptr = brdf.sampler_ptr->clone();
	else sampler_ptr = NULL;
}

BRDF& BRDF::operator= (const BRDF& rhs) {
	if(this ==&rhs) 
		return(*this);

	if(sampler_ptr){
		delete sampler_ptr;
		sampler_ptr = NULL;
	}

	if(rhs.sampler_ptr)
		sampler_ptr = rhs.sampler_ptr->clone();

	return(*this);
}

BRDF::~BRDF(void) {
	if(sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = NULL;
	}
}

void BRDF::set_sampler(Sampler* sPtr) {
	sampler_ptr = sPtr;
	sampler_ptr -> map_samples_to_hemisphere(1);
}

RGBColor BRDF::f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const {
	return(black);
}

RGBColor BRDF::sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi) const {
	return(black);
}

RGBColor BRDF::sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const {
	return(black);
}

RGBColor BRDF::rho(const ShadeRec& sr, const Vector3D& wo) const {
	return(black);
}