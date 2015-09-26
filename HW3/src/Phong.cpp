#include "Phong.h"

Phong::Phong()
:   Material()
{ambient.r = 0.2; ambient.g = 0.2; ambient.b = 0.2;
diffuse.r = 0; diffuse.g = 0; diffuse.b = 0;
emission.r = 0; emission.g = 0; emission.b = 0;
specular.r = 0; specular.g = 0; specular.b = 0;
shininess = 0;}

Phong::Phong(const Phong& m)
:   Material(m)
{
    ambient = m.ambient;
    diffuse = m.diffuse;
    emission = m.emission;
    shininess = m.shininess;
    specular = m.specular;
}

Material* Phong::clone(void) const {
    return(new Phong(*this));
}

Phong& Phong::operator= (const Phong& rhs) {
    if (this == &rhs)
        return(*this);

    Material::operator=(rhs);

    ambient = rhs.ambient;
    diffuse = rhs.diffuse;
    emission = rhs.emission;
    shininess = rhs.shininess;
    specular = rhs.specular;

    return(*this);
}

Phong::~Phong() {}


RGBColor Phong::shade(ShadeRec& sr) {
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

        if(sr.w.lights[j]->casts_shadows())
        {
            Ray shadowRay(sr.hit_point, wi);
            in_shadow = sr.w.lights[j]->in_shadow(shadowRay, sr);
        }

        if(!in_shadow)
        {
            L += diffuse * sr.w.lights[j]->L(sr) * max(0.0, ndotwi) + specular * sr.w.lights[j]->L(sr) * pow(max(ndoth, 0.0), shininess);
        }


    }

    return(L);

}