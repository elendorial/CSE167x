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

#include "ViewPlane.h"

ViewPlane::ViewPlane(void)
:   hres(400),
    vres(400),
    s(1.0),
    num_samples(1),
    gamma(1.0),
    inv_gamma(1.0),
    show_out_of_gamut(false),
    max_depth(1),
    sampler_ptr(NULL)
{}

ViewPlane::ViewPlane(const ViewPlane& vp)
:   hres(vp.hres),
    vres(vp.vres),
    s(vp.s),
    num_samples(vp.num_samples),
    gamma(vp.gamma),
    inv_gamma(vp.inv_gamma),
    show_out_of_gamut(vp.show_out_of_gamut),
    max_depth(vp.max_depth),
    sampler_ptr(vp.sampler_ptr->clone())
{}

ViewPlane& ViewPlane::operator= (const ViewPlane& rhs) {
    if(this == &rhs)
        return(*this);

    hres = rhs.hres;
    vres = rhs.vres;
    s = rhs.s;
    num_samples = rhs.num_samples;
    gamma = rhs.gamma;
    inv_gamma = rhs.inv_gamma;
    show_out_of_gamut = rhs.show_out_of_gamut;
    max_depth = rhs.max_depth;
    sampler_ptr = rhs.sampler_ptr;

    return(*this);
}

ViewPlane::~ViewPlane(void)
{
    if(sampler_ptr) {
        delete sampler_ptr;
        sampler_ptr = NULL;
    }
}