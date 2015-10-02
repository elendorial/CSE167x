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
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

This file incorporates work covered by the following copyright and permission notice:

Copyright (C) Kevin Suffern 2000-2007.
This C++ code is for non-commercial purposes only.
This C++ code is licensed under the GNU General Public License Version 2.
See the file COPYING.txt for the full license. */

#include "Constants.h"
#include "Point3D.h"
#include "Vector3D.h"
#include "Pinhole.h"
#include "World.h"
#include <math.h>
#include <iostream>

Pinhole::Pinhole(void)
:   Camera(),
    d(500),
    zoom(1.0)
{}

Pinhole::Pinhole(const Pinhole& c)
:   Camera(c),
    d(c.d),
    zoom(c.zoom)
{}

Camera* Pinhole::clone(void) const {
    return (new Pinhole(*this));
}

Pinhole& Pinhole::operator= (const Pinhole& rhs) {
    if(this == &rhs)
        return(*this);

    Camera::operator= (rhs);

    d = rhs.d;
    zoom = rhs.zoom;

    return(*this);
}

Pinhole::~Pinhole(void) {}

Vector3D Pinhole::get_direction(const Point2D& p) const {
    Vector3D dir = p.x * u + p.y * v - d * w;
    dir.normalize();

    return(dir);
}

void Pinhole::render_scene(World& w) {

    RGBColor L;
    ViewPlane vp(w.vp);
    FreeImage_Initialise();
    FIBITMAP* bitmap = FreeImage_Allocate(vp.hres, vp.vres, 24);
    RGBQUAD color;
    Ray ray;
    int depth = 0;
    Point2D pp;
    Point2D sp;

    vp.s /= zoom;
    ray.o = eye;

    for(int r = 0; r < vp.vres; r++)
        for(int c = 0; c < vp.hres; c++) {
            L = black;

            for(int j = 0; j < vp.num_samples; j++) {
                sp = vp.sampler_ptr -> sample_unit_square();
                pp.x = vp.s * (c - 0.5 * vp.hres + sp.x);
                pp.y = vp.s * (r - 0.5 * vp.vres + sp.y);
                ray.d = get_direction(pp);
                L += w.tracer_ptr -> trace_ray(ray, depth);
            }
            L /= vp.num_samples;
            L *= exposure_time;
            w.display_pixel(r, c, L);
            color.rgbRed = (int)(L.r*255);
            color.rgbGreen = (int)(L.g*255);
            color.rgbBlue = (int)(L.b*255);
            FreeImage_SetPixelColor(bitmap, c, r, &color);
        }
    if (FreeImage_Save(FIF_PNG, bitmap, "test.png", 0))
        std::cout << "Image Successfully Saved!" << std::endl;

    FreeImage_DeInitialise();
}