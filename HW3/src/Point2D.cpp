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

#include "Point2D.h"

Point2D::Point2D(void)
:   x(0.0), y(0.0)
{}

Point2D::Point2D(const float x1, const float y1)
:   x(x1), y(y1)
{}

Point2D::Point2D(const Point2D& p)
:   x(p.x), y(p.y)
{}

Point2D& Point2D::operator= (const Point2D& rhs) {
    if(this == &rhs)
        return(*this);

    x = rhs.x;
    y = rhs.y;

    return(*this);
}