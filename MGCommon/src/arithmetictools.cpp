/*
 *  arithmetictools.cpp -- floating point numbers comparison tools.
 *
*/

#include "arithmetictools.h"
#include <math.h>


bool fAreSame(float a, float b)
{
    bool bRet = (fabs(a - b) < EPSILON);
    return bRet;
}

bool fALessThanB(float a, float b)
{
    bool bRet = ((a < b) && (fabs(a - b) >= EPSILON));
    return bRet;
}

bool fAGreaterThanB(float a, float b)
{
    bool bRet = ((a > b) && (fabs(a - b) >= EPSILON));
    return bRet;
}
