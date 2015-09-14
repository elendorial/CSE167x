#ifndef __MATTE__
#define __MATTE__

#include "Material.h"
#include "Lambertian.h"

class Matte: public Material {
	public:

		Matte(void);

		Matte(const Matte& m);

		virtual Material* clone(void) const;

		Matte& operator= (const Matte& rhs);

		~Matte();

		void set_ka(const float k);

		void set_kd(const float k);

		void set_cd(const RGBColor c);

		void set_cd(const float r, const float g, const float b);

		void set_cd(const float c);

		virtual RGBColor shade(ShadeRec& sr);

	private:

		Lambertian* ambient_brdf;
		Lambertian* diffuse_brdf;
};

inline void Matte::set_ka(const float ka) {
	ambient_brdf->set_kd(ka);
}

inline void Matte::set_kd(const float kd) {
	diffuse_brdf->set_kd(kd);
}

inline void Matte::set_cd(const RGBColor c) {
	ambient_brdf->set_cd(c);
	diffuse_brdf->set_cd(c);
}

inline void Matte::set_cd(const float r, const float g, const float b) {
	ambient_brdf->set_cd(r, g, b);
	diffuse_brdf->set_cd(r, g, b);
}

inline void Matte::set_cd(const float c) {
	ambient_brdf->set_cd(c);
	diffuse_brdf->set_cd(c);
}

#endif