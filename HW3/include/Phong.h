#ifndef __PHONG__
#define __PHONG__

#include "Material.h"

class Phong: public Material {
    public:

        Phong(void);

        Phong(const Phong& ph);

        virtual Material* clone(void) const;

        Phong& operator= (const Phong& rhs);

        ~Phong();

        virtual RGBColor shade(ShadeRec& sr);

        void set_ambient(const float r, const float g, const float b);

        void set_diffuse(const float r, const float g, const float b);

        void set_emission(const float r, const float g, const float b);

        void set_specular(const float r, const float g, const float b);

        void set_shininess(const float s);

        RGBColor specular;

    private:

        RGBColor ambient;
        RGBColor diffuse;
        RGBColor emission;

        float shininess;
};

inline void Phong::set_specular(const float r, const float g, const float b){
    specular.r = r;
    specular.g = g;
    specular.b = b;
}

inline void Phong::set_ambient(const float r, const float g, const float b) {
    ambient.r = r;
    ambient.g = g;
    ambient.b = b;
}

inline void Phong::set_diffuse(const float r, const float g, const float b) {
    diffuse.r = r;
    diffuse.g = g;
    diffuse.b = b;
}

inline void Phong::set_emission(const float r, const float g, const float b) {
    emission.r = r;
    emission.g = g;
    emission.b = b;
}

inline void Phong::set_shininess(const float s){
    shininess = s;
}


#endif