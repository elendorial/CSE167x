#ifndef __GLOSSY_SPECULAR__
#define __GLOSSY_SPECULAR__

#include "BRDF.h"

class GlossySpecular: public BRDF {
	public:

		GlossySpecular(void);

		GlossySpecular(const GlossySpecular& gl);

		GlossySpecular& operator= (const GlossySpecular& rhs);

		virtual ~GlossySpecular(void);

		virtual GlossySpecular* clone(void) const;

		virtual RGBColor f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const;

		virtual RGBColor sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const;

		virtual RGBColor rho(const ShadeRec& sr, const Vector3D& wo) const;

		void set_ks(const float ks);

		void set_exp(const float exp);

		void set_cs(const RGBColor& c);

		void set_cs(const float r, const float g, const float b);

		void set_cs(const float c);

		void set_sampler(Sampler* sp, const float exp);

		void set_samples(const int num_samples, const float exp);

		void set_normal(const Normal& n);

	private:

		float ks;
		RGBColor cs;
		float exp;
		Sampler* sampler;
};

inline void GlossySpecular::set_ks(const float k) {
	ks = k;
}

inline void GlossySpecular::set_exp(const float e) {
	exp = e;
}

inline void GlossySpecular::set_cs(const RGBColor& c) {
	cs = c;
}

inline void GlossySpecular::set_cs(const float r, const float g, const float b) {
	cs.r = r; cs.g = g; cs.b = b;
}

inline void GlossySpecular::set_cs(const float c) {
	cs.r = c; cs.g = c; cs.b = c;
}

#endif