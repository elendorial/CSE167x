#ifndef __TRIANGLE__
#define __TRIANGLE__

#include "GeometricObject.h"

class Triangle: public GeometricObject {
    public:

        Triangle(void);

        Triangle(const Point3D& a, const Point3D& b, const Point3D& c);

        virtual Triangle* clone(void) const;

        Triangle(const Triangle& triangle);

        ~Triangle();

        Triangle& operator= (const Triangle& rhs);

        void compute_normal(void);

        virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const;

        virtual bool shadow_hit(const Ray& ray, float& tmin) const;

    private:

        Point3D v0, v1, v2;
        Normal normal;
};

#endif