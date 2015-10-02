/*Copyright (C) 2015  Viktor Daropoulos

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.*/

#include "Sphere.h"
#include "math.h"

const double Sphere::kEpsilon = 0.001;

Sphere::Sphere(void)
:   GeometricObject(),
    center(0.0),
    radius(1.0)
{}

Sphere::Sphere(Point3D c, double r)
:   GeometricObject(),
    center(c),
    radius(r)
{}

Sphere* Sphere::clone(void) const {
    return (new Sphere(*this));
}

Sphere::Sphere(const Sphere& sphere)
:   GeometricObject(sphere),
    center(sphere.center),
    radius(sphere.radius)
{}

Sphere& Sphere::operator= (const Sphere& rhs)
{
    if(this == &rhs)
        return(*this);

    GeometricObject::operator= (rhs);

    center = rhs.center;
    radius = rhs.radius;

    return(*this);
}

Sphere::~Sphere(void)
{}

bool Sphere::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
    double t;
    Vector3D temp = ray.o - center;
    double a = ray.d * ray.d;
    double b = 2.0 * temp * ray.d;
    double c = temp * temp - radius * radius;
    double disc = b * b - 4.0 * a * c;

    if(disc < 0.0)
        return(false);
    else {
        double e = sqrt(disc);
        double denom = 2.0 * a;
        t = (-b - e) / denom;

        if(t > kEpsilon) {
            tmin = t;
            sr.normal = (temp + t * ray.d) / radius;
            sr.local_hit_point = ray.o + t * ray.d;
            return (true);
        }

        t = (-b + e) / denom;

        if(t > kEpsilon) {
            tmin = t;
            sr.normal = (temp + t * ray.d) / radius;
            sr.local_hit_point = ray.o + t * ray.d;
            return(true);
        }
    }

    return (false);


}

bool Sphere::shadow_hit(const Ray& ray, float& tmin) const {

    double t;
    Vector3D temp = ray.o - center;
    double a = ray.d * ray.d;
    double b = 2.0 * temp * ray.d;
    double c = temp * temp - radius * radius;
    double disc = b * b - 4.0 * a * c;

    if(disc < 0.0)
        return(false);
    else {
        double e = sqrt(disc);
        double denom = 2.0 * a;
        t = (-b - e) / denom;

        if(t > kEpsilon) {
            tmin = t;
            return (true);
        }

        t = (-b + e) / denom;

        if(t > kEpsilon) {
            tmin = t;
            return(true);
        }
    }

    return (false);

}

