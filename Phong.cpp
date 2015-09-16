#include "Phong.h"

Phong::Phong()
:	Material(),
	ambient_brdf(new Lambertian),
	diffuse_brdf(new Lambertian),
	specular_brdf(new GlossySpecular)
{ambient.r = 0.2; ambient.g = 0.2; ambient.b = 0.2;
diffuse.r = 0; diffuse.g = 0; diffuse.b = 0;
emission.r = 0; emission.g = 0; emission.b = 0;
specular.r = 0; specular.g = 0; specular.b = 0;
shininess = 0;}

Phong::Phong(const Phong& m)
:	Material(m)
{
	if(m.ambient_brdf)
		ambient_brdf = m.ambient_brdf->clone();
	else ambient_brdf = NULL;

	if(m.diffuse_brdf)
		diffuse_brdf = m.diffuse_brdf->clone();
	else diffuse_brdf = NULL;

	if(m.specular_brdf)
		specular_brdf = m.specular_brdf->clone();
	else specular_brdf = NULL;
}

Material* Phong::clone(void) const {
	return(new Phong(*this));
}

Phong& Phong::operator= (const Phong& rhs) {
	if (this == &rhs)
		return(*this);

	Material::operator=(rhs);

	if(ambient_brdf) {
		delete ambient_brdf;
		ambient_brdf = NULL;
	}

	if(diffuse_brdf) {
		delete diffuse_brdf;
		diffuse_brdf = NULL;
	}

	if(specular_brdf) {
		delete specular_brdf;
		specular_brdf = NULL;
	}

	if(rhs.ambient_brdf)
		ambient_brdf = rhs.ambient_brdf->clone();

	if(rhs.diffuse_brdf)
		diffuse_brdf = rhs.diffuse_brdf->clone();

	if(rhs.specular_brdf)
		specular_brdf = rhs.specular_brdf->clone();

	return(*this);
}

Phong::~Phong() {
	if(ambient_brdf) {
		delete ambient_brdf;
		ambient_brdf = NULL;
	}

	if(diffuse_brdf) {
		delete diffuse_brdf;
		diffuse_brdf = NULL;
	}

	if(specular_brdf) {
		delete specular_brdf;
		specular_brdf = NULL;
	}
}

RGBColor Phong::shade(ShadeRec& sr) {
	Vector3D wo = -sr.ray.d;
	RGBColor L = ambient_brdf->rho(sr,wo) * sr.w.ambient_ptr->L(sr);
	int numLights = sr.w.lights.size();

	for(int j = 0; j < numLights; j++) {
		Vector3D wi = sr.w.lights[j]->get_direction(sr);
		float ndotwi = sr.normal * wi;

		if(ndotwi > 0.0) {
			bool in_shadow = false;

			if(sr.w.lights[j]->casts_shadows()) {
				Ray shadowRay(sr.hit_point, wi);
				in_shadow = sr.w.lights[j]->in_shadow(shadowRay, sr);
			}

			if(!in_shadow)
				L += diffuse_brdf->f(sr,wo,wi) * sr.w.lights[j]->L(sr) * ndotwi +
				specular_brdf->f(sr,wo,wi) * sr.w.lights[j]->L(sr) * ndotwi;
			}

	}

	return(L);
}

RGBColor Phong::shade(ShadeRec& sr, int depth) {
	Vector3D wo = -sr.ray.d;
	RGBColor L = ambient + emission;

	int numLights = sr.w.lights.size();

	for(int j = 0; j < numLights; j++) {
		Vector3D wi = sr.w.lights[j]->get_direction(sr);
		Vector3D h(wi + wo);
		h.normalize();
		float ndotwi = sr.normal * wi;
		float ndoth = sr.normal * h;

		bool in_shadow = false;

		if(sr.w.lights[j]->casts_shadows()) {
			Ray shadowRay(sr.hit_point, wi);
			in_shadow = sr.w.lights[j]->in_shadow(shadowRay, sr);
		}

		if(!in_shadow) {
			if(ndotwi > 0.0)
				L += diffuse * sr.w.lights[j]->L(sr) * ndotwi;

			if(ndoth > 0.0)
				L += specular * sr.w.lights[j]->L(sr) * pow(ndoth, shininess);
		}

	}

	return(L);

}