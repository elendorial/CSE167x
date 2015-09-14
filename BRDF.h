#ifndef __BRDF__
#define __BRDF__

#include <math.h>

#include "RGBColor.h"
#include "Vector3D.h"
#include "ShadeRec.h"
#include "Sampler.h"

class BRDF {
	public:

		BRDF(void);

		BRDF(const BRDF& object);

		virtual BRDF* clone(void) const = 0;

		BRDF& operator= (const BRDF& rhs);

		virtual ~BRDF(void);

		void set_sampler(Sampler* sPtr);

		virtual RGBColor f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const;

		virtual RGBColor sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi) const;

		virtual RGBColor sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const;

		virtual RGBColor rho(const ShadeRec& sr, const Vector3D& wo) const;

	protected:

		Sampler* sampler_ptr;

		
};

#endif