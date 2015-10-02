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

#include "Matrix.h"

Matrix::Matrix(void)
{
    for(int x = 0; x < 4; x++)
        for(int y = 0; y < 4; y++) {
            if(x == y)
                m[x][y] = 1.0;
            else
                m[x][y] = 0.0;
        }
}

Matrix::Matrix(const Matrix& mat) {
    for(int x = 0; x < 4; x++)
        for(int y = 0; y < 4; y++)
            m[x][y] = mat.m[x][y];
}

Matrix::~Matrix(void) {}

Matrix& Matrix::operator= (const Matrix& rhs) {
    if(this == &rhs)
        return (*this);

    for(int x = 0; x < 4; x++)
        for(int y = 0; y < 4; y++)
            m[x][y] = rhs.m[x][y];

    return (*this);
}

Matrix Matrix::operator* (const Matrix& mat) const {
    Matrix product;

    for(int y = 0; y < 4; y++)
        for(int x = 0; x < 4; x++) {
            double sum = 0.0;

            for(int j = 0; j < 4; j++)
                sum += m[x][j] * mat.m[j][y];

            product.m[x][y] = sum;
        }

    return (product);
}

Matrix Matrix::operator/ (const double d) {
    for(int x = 0; x < 4; x++)
        for(int y = 0; y < 4; y++)
            m[x][y] = m[x][y] / d;

    return (*this);
}

void Matrix::set_identity(void) {
    for(int x = 0; x < 4; x++)
        for(int y = 0; y < 4; y++) {
            if(x == y)
                m[x][y] = 1.0;
            else
                m[x][y] = 0.0;
        }
}