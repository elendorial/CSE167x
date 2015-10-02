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

#ifndef __CONSTANTS__
#define __CONSTANTS__

#include <stdlib.h>
#include "RGBColor.h"


const double    PI          = 3.1415926535897932384;
const double    TWO_PI      = 6.2831853071795864769;
const double    PI_ON_180   = 0.0174532925199432957;
const double    invPI       = 0.3183098861837906715;
const double    invTWO_PI   = 0.1591549430918953358;

const double    kEpsilon    = 0.0001;
const double    kHugeValue  = 1.0E10;

const RGBColor  black(0.0);
const RGBColor  white(1.0);
const RGBColor  red(1.0, 0.0, 0.0);

const float     invRAND_MAX = 1.0 / (float)RAND_MAX;

#endif
