#include "Blinn.h"
#include "MultiJittered.h"
#include "Constants.h"

Blinn::Blinn(void)
:	ks(0.0),
	cs(1.0),
	sampler(NULL)
{}

Blinn::Blinn(const Blinn& bl)
:	ks(bl.ks),
	cs(bl.cs),
	sampler(bl.sampler)
{}

Blinn& Blinn::operator=(const Blinn& rhs) {
	if(this == &rhs)
		return(*this);

	BRDF::operator=(rhs);

	ks = rhs.ks;
	cs = rhs.cs;
	exp = rhs.exp;
	sampler = rhs.sampler;

}

Blinn::~Blinn(void) {
	if(sampler) {
		delete sampler;
		sampler = NULL;
	}
}

Blinn* Blinn::clone(void) const {
	return(new Blinn(*this));
}

void Blinn::set_sampler(Sampler* sp, const float exp) {
	sampler_ptr = sp;
	sampler_ptr->map_samples_to_hemisphere(exp);
}

void Blinn::set_samples(const int num_samples, const float exp) {
	sampler_ptr = new MultiJittered(num_samples);
	sampler_ptr->map_samples_to_hemisphere(exp);
}

RGBColor Blinn::f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const {
	RGBColor L;
	Vector3D h(wi + wo);
	h.normalize();
	float ndoth = sr.normal * h;

	if(ndoth > 0.0)
		L = ks * cs * pow(ndoth, exp);

	return(L); 
}

RGBColor Blinn::rho(const ShadeRec& sr, const Vector3D& wo) const{
	return(black);
}

RGBColor Blinn::sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const {

	
}