/*
 *  arithmetictools.h -- floating point numbers comparison tools.
 *
 *  Copyright (C) 2010  Efstathios Chatzikyriakidis (contact@efxa.org)
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/* header defining the interface of the library. */
#ifndef ARITHMETICTOOLS_H
#define ARITHMETICTOOLS_H


/// greatest difference for considering the float equal
#define EPSILON 0.00001f

/** Returns true if the float number a is equal to b.
    Their difference must not be greater than EPSILON.
*/
bool fAreSame(float a, float b);

/** Returns true if the float number a less than b
    Their difference must not be greater than EPSILON.
*/
bool fALessThanB(float a, float b);

/** Returns true if the float number a is greater than b
    Their difference must not be greater than EPSILON.
*/
bool fAGreaterThanB(float a, float b);

#endif // ARITHMETICTOOLS_H
