#include "GlossySpecular.h"
#include "MultiJittered.h"
#include "Constants.h"

GlossySpecular::GlossySpecular(void)
:	ks(0.0),
	cs(1.0),
	exp(1.0),
	sampler(NULL)
{}

GlossySpecular::GlossySpecular(const GlossySpecular& gl)
:	ks(gl.ks),
	cs(gl.cs),
	exp(gl.exp),
	sampler(gl.sampler)
{}

GlossySpecular& GlossySpecular::operator= (const GlossySpecular& rhs) {
	if(this == &rhs)
		return(*this);

	BRDF::operator=(rhs);

	ks = rhs.ks;
	cs = rhs.cs;
	exp = rhs.exp;
	sampler = rhs.sampler;
}

GlossySpecular::~GlossySpecular(void) {
	if(sampler){
		delete sampler;
		sampler = NULL;
	}
}

GlossySpecular* GlossySpecular::clone(void) const {
	return (new GlossySpecular(*this));
}

void GlossySpecular::set_sampler(Sampler* sp, const float exp) {
	sampler_ptr = sp;
	sampler_ptr->map_samples_to_hemisphere(exp);
}

void GlossySpecular::set_samples(const int num_samples, const float exp) {
	sampler_ptr = new MultiJittered(num_samples);
	sampler_ptr->map_samples_to_hemisphere(exp);
}

RGBColor GlossySpecular::f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const {
	RGBColor L;
	float ndotwi = sr.normal * wi;
	Vector3D r(-wi + 2.0 * sr.normal * ndotwi);
	float rdotwo = r * wo;

	if(rdotwo > 0.0)
		L = ks * cs * pow(rdotwo, exp);

	return(L); 
}

RGBColor GlossySpecular::rho(const ShadeRec& sr, const Vector3D& wo) const{
	return(black);
}

RGBColor GlossySpecular::sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const {

	
}