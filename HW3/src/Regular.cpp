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

#include "Regular.h"

Regular::Regular(void)
:   Sampler()
{}

Regular::Regular(const int num)
:   Sampler(num)
{
    generate_samples();
}

Regular::Regular(const Regular& u)
:   Sampler(u)
{
    generate_samples();
}

Regular& Regular::operator= (const Regular& rhs) {
    if(this == &rhs)
        return(*this);

    Sampler::operator=(rhs);

    return(*this);
}

Regular* Regular::clone(void) const {
    return (new Regular(*this));
}

Regular::~Regular(void) {}

void Regular::generate_samples(void) {
    int n = (int)sqrt((float)num_samples);

    for(int j = 0; j < num_sets; j++)
        for(int p = 0; p < n; p++)
            for(int q = 0; q < n; q++)
                samples.push_back(Point2D((q + 0.5) / n, (p + 0.5) / n));

}