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

#ifndef __POINT_2D__
#define __POINT_2D__

class Point2D {

    public:

        float x, y;

    public:

        Point2D(void);
        Point2D(const float arg);
        Point2D(const float x1, const float y1);
        Point2D(const Point2D& p);
        ~Point2D(void) {}

        Point2D& operator= (const Point2D& rhs);

        Point2D operator* (const float a);
};


inline Point2D Point2D::operator* (const float a) {
    return(Point2D(a * x, a * y));
}

#endif