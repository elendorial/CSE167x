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

#ifndef __RGB_COLOR__
#define __RGB_COLOR__

class RGBColor
{
    public:

        float r, g, b;

    public:

        RGBColor(void);
        RGBColor(float c);
        RGBColor(float _r, float _g, float _b);
        RGBColor(const RGBColor& c);

        ~RGBColor(void);

        RGBColor& operator= (const RGBColor& rhs);

        RGBColor operator+ (const RGBColor& c) const;

        RGBColor& operator += (const RGBColor& c);

        RGBColor operator* (const float a) const;

        RGBColor& operator*= (const float a);

        RGBColor operator/ (const float a) const;

        RGBColor& operator/= (const float a);

        RGBColor operator* (const RGBColor& c) const;

        bool operator== (const RGBColor& c) const;

        RGBColor powc(float p) const;

        float average(void) const;

};

inline RGBColor RGBColor::operator+ (const RGBColor& c) const {
    return (RGBColor(r + c.r, g + c.g, b + c.b));
}

inline RGBColor& RGBColor::operator+= (const RGBColor& c) {
    r += c.r; g += c.g; b += c.b;
    return (*this);
}

inline RGBColor RGBColor::operator* (const float a) const {
    return (RGBColor(r * a, g * a, b * a));
}

inline RGBColor& RGBColor::operator*= (const float a) {
    r *= a; g *= a; b *= a;
    return (*this);
}

inline RGBColor RGBColor::operator/ (const float a) const {
    return (RGBColor(r / a, g / a, b / a));
}

inline RGBColor& RGBColor::operator/= (const float a)
{
    r /= a; g /= a; b /= a;
    return (*this);
}

inline RGBColor RGBColor::operator* (const RGBColor& c) const {
    return (RGBColor(r * c.r, g * c.g, b * c.b));
}

inline bool RGBColor::operator== (const RGBColor& c) const {
    return (r == c.r && g == c.g && b == c.b);
}

inline float RGBColor::average(void) const {
    return (0.333333333333 * (r + b + g));
}

RGBColor operator* (const float a, const RGBColor& c);

inline RGBColor operator* (const float a, const RGBColor& c) {
    return (RGBColor(a * c.r, a * c.g, a * c.b));
}

#endif