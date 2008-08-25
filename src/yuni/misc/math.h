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

    /*!
    ** \brief Get the expression considered as the greater
    **
    ** \param a The first expression
    ** \param b The second expression
    ** \return The expression considered as the grater
    */
    template<typename T>
    T& Max(T& a, T& b) {return a < b ? b : a;}

    /*!
    ** \brief Get the expression considered as the smaller
    **
    ** \param a The first expression
    ** \param b The second expression
    ** \return The expression considered as the smaller
    */
    T& Min(T& a, T& b) {return a < b ? a : b;}


    /*!
    ** \brief Ensure that an expression was contained in a range of values
    **
    ** \param v An expression
    ** \param min The lower bound limit allowed for the expression `v`
    ** \param min The upper bound limit allowed for the expression `v`
    ** \return The expression itself, or a bound limit
    */
    T& MinMax(T& v, T& min, T& max) {return ((v < min) ? min : ((v > max) ? max : v));}


} // namespace Math
} // namespace Yuni

#endif // __YUNI_MISC_MATH_H__
