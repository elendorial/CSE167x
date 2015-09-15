#ifndef __BLINN__
#define __BLINN__

#include "BRDF.h"

class Blinn: public BRDF {
	public:

		Blinn(void);

		Blinn(const Blinn& bl);

		Blinn& operator= (const Blinn& rhs);

		virtual ~Blinn();

		virtual Blinn* clone(void) const;

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

inline void Blinn::set_ks(const float k) {
	ks = k;
}

inline void Blinn::set_exp(const float e) {
	exp = e;
}

inline void Blinn::set_cs(const RGBColor& c) {
	cs = c;
}

inline void Blinn::set_cs(const float r, const float g, const float b) {
	cs.r = r; cs.g = g; cs.b = b;
}

inline void Blinn::set_cs(const float c) {
	cs.r = c; cs.g = c; cs.b = c;
}

#endif

