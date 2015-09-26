#include "Directional.h"

Directional::Directional(void)
:   Light(),
    ls(1.0),
    color(1.0),
    dir(0, 1, 0),
    shadows(false)
{}

Directional::Directional(const Directional& dl)
:   Light(dl),
    ls(dl.ls),
    color(dl.color),
    dir(dl.dir),
    shadows(dl.shadows)
{}

Light* Directional::clone(void) const {
    return(new Directional(*this));
}

Directional& Directional::operator= (const Directional& rhs) {
    if(this == &rhs)
        return(*this);

    Light::operator=(rhs);

    ls = rhs.ls;
    color = rhs.color;
    dir = rhs.dir;
    shadows = rhs.shadows;

    return(*this);
}

Directional::~Directional() {}

Vector3D Directional::get_direction(ShadeRec& sr) {
    return (dir);
}

RGBColor Directional::L(ShadeRec& s) {
    return(ls * color);
}

bool Directional::in_shadow(const Ray& ray, const ShadeRec& sr) const {
    float t;
    int num_objects = sr.w.objects.size();

    for(int j = 0; j < num_objects; j++)
        if(sr.w.objects[j]->shadow_hit(ray,t))
            return(true);
    return(false);
}

bool Directional::casts_shadows() const{
    return(shadows);
}