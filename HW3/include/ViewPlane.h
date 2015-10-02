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

#ifndef __VIEW_PLANE__
#define __VIEW_PLANE__
#include "MultiJittered.h"
#include "Regular.h"


class ViewPlane {

    public:

        int hres;
        int vres;
        float s;
        int num_samples;
        int max_depth;
        Sampler* sampler_ptr;

        float gamma;
        float inv_gamma;
        bool show_out_of_gamut;


    public:

        ViewPlane();

        ViewPlane(const ViewPlane& vp);

        ViewPlane& operator= (const ViewPlane& rhs);

        ~ViewPlane();

        void set_hres(const int h_res);

        void set_vres(const int v_res);

        void set_pixel_size(const float size);

        void set_gamma(const float g);

        void set_gamut_display(const bool show);

        void set_samples(const int n);

        void set_sampler(Sampler* sp);

        void set_max_depth(int d);

};

inline void ViewPlane::set_max_depth(int d) {
    max_depth = d;
}

inline void ViewPlane::set_hres(const int h_res) {
    hres = h_res;
}

inline void ViewPlane::set_vres(const int v_res) {
    vres = v_res;
}

inline void ViewPlane::set_pixel_size(const float size) {
    s = size;
}

inline void ViewPlane::set_gamma(const float g) {
    gamma = g;
    inv_gamma = 1.0 / gamma;
}

inline void ViewPlane::set_gamut_display(const bool show) {
    show_out_of_gamut = show;
}

inline void ViewPlane::set_samples(const int n) {
    num_samples = n;

    if(sampler_ptr) {
        delete sampler_ptr;
        sampler_ptr = NULL;
    }

    if (num_samples > 1)
        sampler_ptr = new MultiJittered(num_samples);
    else
        sampler_ptr = new Regular(1);
}

inline void ViewPlane::set_sampler(Sampler* sp) {
    if(sampler_ptr) {
        delete sampler_ptr;
        sampler_ptr = NULL;
    }

    num_samples = sp -> get_num_samples();
    sampler_ptr = sp;
}

#endif