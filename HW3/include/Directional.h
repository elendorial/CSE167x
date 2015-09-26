#ifndef __DIRECTIONAL__
#define __DIRECTIONAL__

#include "Light.h"
#include "Vector3D.h"
#include "RGBColor.h"
#include "World.h"
#include "ShadeRec.h"

class Directional: public Light {
    public:

        Directional(void);

        Directional(const Directional& dl);

        virtual Light* clone(void) const;

        Directional& operator= (const Directional& rhs);

        virtual ~Directional();

        void scale_radiance(const float b);

        void set_color(const float c);

        void set_color(const RGBColor& c);

        void set_color(const float r, const float g, const float b);

        void set_direction(Vector3D d);

        void set_direction(float dx, float dy, float dz);

        void set_shadows(bool flag);

        virtual Vector3D get_direction(ShadeRec& sr);

        virtual bool in_shadow(const Ray& ray, const ShadeRec& sr) const;

        virtual bool casts_shadows() const;

        virtual RGBColor L(ShadeRec& sr);

    private:

        float ls;
        RGBColor color;
        Vector3D dir;
        bool shadows;

};

inline void Directional::set_shadows(bool flag) {
    shadows = flag;
}

inline void Directional::scale_radiance(const float b) {
    ls = b;
}

inline void Directional::set_color(const float c) {
    color.r = c; color.g = c; color.b = c;
}

inline void Directional::set_color(const RGBColor& c) {
    color = c;
}

inline void Directional::set_color(const float r, const float g, const float b) {
    color.r = r; color.g = g; color.b = b;
}

inline void Directional::set_direction(Vector3D d) {
    dir = d;
    dir.normalize();
}

inline void Directional::set_direction(float dx, float dy, float dz) {
    dir.x = dx; dir.y = dy; dir.z = dz;
}

#endif