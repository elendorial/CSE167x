#ifndef __PHONG__
#define __PHONG__

#include "Material.h"
#include "Lambertian.h"
#include "GlossySpecular.h"
#include "Blinn.h"

class Phong: public Material {
	public:

		Phong(void);

		Phong(const Phong& ph);

		virtual Material* clone(void) const;

		Phong& operator= (const Phong& rhs);

		~Phong();

		void set_ka(const float k);

		void set_kd(const float k);

		void set_cd(const RGBColor c);

		void set_cd(const float r, const float g, const float b);

		void set_cd(const float c);

		void set_ks(const float ks);

		void set_exp(const float exp);

		void set_cs(const RGBColor& c);

		void set_cs(const float r, const float g, const float b);

		void set_cs(const float c);

		void set_sampler(Sampler* sp, const float exp);

		void set_samples(const int num_samples, const float exp);

		virtual RGBColor shade(ShadeRec& sr);

	private:

		Lambertian* ambient_brdf;
		Lambertian* diffuse_brdf;
		Blinn* specular_brdf;
};

inline void Phong::set_ka(const float ka) {
	ambient_brdf->set_kd(ka);
}

inline void Phong::set_kd(const float kd) {
	diffuse_brdf->set_kd(kd);
}

inline void Phong::set_cd(const RGBColor c) {
	ambient_brdf->set_cd(c);
	diffuse_brdf->set_cd(c);
}

inline void Phong::set_cd(const float r, const float g, const float b) {
	ambient_brdf->set_cd(r, g, b);
	diffuse_brdf->set_cd(r, g, b);
}

inline void Phong::set_cd(const float c) {
	ambient_brdf->set_cd(c);
	diffuse_brdf->set_cd(c);
}

inline void Phong::set_ks(const float ks) {
	specular_brdf->set_ks(ks);
}

inline void Phong::set_exp(const float exp) {
	specular_brdf->set_exp(exp);
}

inline void Phong::set_cs(const RGBColor& c){
	specular_brdf->set_cs(c);
}

inline void Phong::set_cs(const float r, const float g, const float b){
	specular_brdf->set_cs(r,g,b);
}

inline void Phong::set_cs(const float c){
	specular_brdf->set_cs(c);
}

inline void Phong::set_sampler(Sampler* sp, const float exp){
	specular_brdf->set_sampler(sp, exp);
}

inline void Phong::set_samples(const int num_samples, const float exp){
	specular_brdf->set_samples(num_samples, exp);
}

#endif