#ifndef __YUNI_MISC_MATH_H__
# define __YUNI_MISC_MATH_H__

# include <stdlib.h>
# include <math.h>


namespace Yuni
{
namespace Math
{

    /*!
    ** \brief Get the integer absolute value
    */
    int Abs(const int a) {return abs(a);}
    float Abs(const float a) {return fabsf(a);}
    double Abs(const double a) {return fabs(a);}


} // namespace Math
} // namespace Yuni

#endif // __YUNI_MISC_MATH_H__
