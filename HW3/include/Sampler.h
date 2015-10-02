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

#ifndef __SAMPLER__
#define __SAMPLER__

#include <vector>
#include <math.h>
#include "Point2D.h"
#include "Point3D.h"
#include "Maths.h"

class Sampler {

    public:

        Sampler(void);
        Sampler (const int num);
        Sampler (const int num, const int num_sets);
        Sampler (const Sampler& s);

        Sampler & operator= (const Sampler& rhs);

        virtual Sampler* clone(void) const = 0;

        virtual ~Sampler(void);

        void set_num_sets(const int np);

        virtual void generate_samples(void) = 0;

        int get_num_samples(void);

        void shuffle_x_coordinates(void);

        void shuffle_y_coordinates(void);

        void setup_shuffled_indices(void);

        void map_samples_to_unit_disk(void);

        void map_samples_to_hemisphere(const float p);

        void map_samples_to_sphere(void);

        Point2D sample_unit_square(void);

        Point2D sample_unit_disk(void);

        Point3D sample_hemisphere(void);

        Point3D sample_sphere(void);

        Point2D sample_one_set(void);

    protected:

        int num_samples;
        int num_sets;
        std::vector<Point2D> samples;
        std::vector<int> shuffled_indices;
        std::vector<Point2D> disk_samples;
        std::vector<Point3D> hemisphere_samples;
        std::vector<Point3D> sphere_samples;
        unsigned long count;
        int jump;

};

#endif