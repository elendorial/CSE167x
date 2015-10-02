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


#ifndef __MATHS__
#define __MATHS__
#include <cstdlib>

inline double max(double x0, double x1);

inline double max(double x0, double x1)
{
    return ((x0 > x1) ? x0 : x1);
}

inline float rand_float(void);

inline float rand_float(void) {
    return ((float)rand() / (float)RAND_MAX);
}

inline int rand_int(void);

inline int rand_int(void) {
    return (rand());
}

inline float rand_float(int l, float h);

inline float rand_float(int l, float h) {
    return (rand_float() * (h - l) + l);
}

inline int rand_int(int l, int h);

inline int
rand_int(int l, int h) {
    return ((int) (rand_float(0, h - l + 1) + l));
}

#endif