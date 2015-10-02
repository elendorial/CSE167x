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

#include "MultiJittered.h"

MultiJittered::MultiJittered(void)
:   Sampler()
{}

MultiJittered::MultiJittered(const int num_samples)
:   Sampler(num_samples) {
    generate_samples();
}

MultiJittered::MultiJittered(const int num_samples, const int m)
:   Sampler(num_samples, m) {
    generate_samples();
}

MultiJittered::MultiJittered(const MultiJittered& mjs)
:   Sampler(mjs)
{
    generate_samples();
}

MultiJittered& MultiJittered::operator= (const MultiJittered& rhs) {
    if(this == &rhs)
        return(*this);

    Sampler::operator=(rhs);

    return(*this);
}

MultiJittered* MultiJittered::clone(void) const {
    return (new MultiJittered(*this));
}


MultiJittered::~MultiJittered(void) {}

void MultiJittered::generate_samples(void) {

    int n  = (int)sqrt((float)num_samples);
    float subcell_width = 1.0 / ((float)num_samples);

    Point2D fill_point;
    for(int j = 0; j < num_samples * num_sets; j++)
        samples.push_back(fill_point);

    for(int p = 0; p < num_sets; p++)
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++) {
                samples[i * n + j + p * num_samples].x = (i * n + j) * subcell_width + rand_float(0, subcell_width);
                samples[i * n + j + p * num_samples].y = (j * n + i) * subcell_width + rand_float(0, subcell_width);
            }

    for(int p = 0; p < num_sets; p ++)
        for(int i = 0; i < n; i ++)
            for(int j = 0; j < n; j ++) {
                int k = rand_int(j, n-1);
                float t = samples[i * n + j + p * num_samples].x;
                samples[i * n + j + p * num_samples].x = samples[i * n + k + p * num_samples].x;
                samples[i * n + k + p * num_samples].x = t;
            }

    for(int p = 0; p < num_sets; p ++)
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j ++) {
                int k = rand_int(j, n-1);
                float t = samples[j * n + i + p * num_samples].y;
                samples[j * n + i + p * num_samples].y = samples[k * n + i + p * num_samples].y;
                samples[k * n + i + p * num_samples].y = t;
            }
}