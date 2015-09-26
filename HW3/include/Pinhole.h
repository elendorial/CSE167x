#ifndef __PINHOLE__
#define __PINHOLE__

#include "Point2D.h"
#include "Camera.h"

class World;

class Pinhole: public Camera {

    public:

        Pinhole();

        Pinhole(const Pinhole& ph);

        virtual Camera* clone(void) const;

        Pinhole& operator= (const Pinhole& rhs);

        virtual ~Pinhole();

        void set_fovy(const float fov);

        void set_view_distance(const float vpd);

        void set_zoom(const float zoom_factor);

        Vector3D get_direction(const Point2D& p) const;

        virtual void render_scene(World& w);

    private:

        float d;
        float zoom;
        float fovy;

};


inline void Pinhole::set_view_distance(float _d) {
    d = _d;
}

inline void Pinhole::set_fovy(float fov) {
    fovy = fov;
}

inline void Pinhole::set_zoom(float zoom_factor) {
    zoom = zoom_factor;
}

#endif


