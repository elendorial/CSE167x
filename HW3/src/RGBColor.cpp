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

#include <math.h>

#include "RGBColor.h"

RGBColor::RGBColor(void)
: r(0.0), g(0.0), b(0.0)
{}

RGBColor::RGBColor(float c)
: r(c), g(c), b(c)
{}

RGBColor::RGBColor(float _r, float _g, float _b)
: r(_r), g(_g), b(_b)
{}

RGBColor::RGBColor(const RGBColor& c)
: r(c.r), g(c.g), b(c.b)
{}

RGBColor::~RGBColor(void)
{}

RGBColor& RGBColor::operator= (const RGBColor& rhs){
    if (this == &rhs)
        return (*this);

    r = rhs.r; g = rhs.g; b = rhs.b;

    return (*this);
}

RGBColor RGBColor::powc(float p) const {
    return(RGBColor(pow(r, p), pow(g, p), pow(b, p)));
}