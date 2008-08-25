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
    template<typename T>
    T& Min(T& a, T& b) {return a < b ? a : b;}


    /*!
    ** \brief Ensure that an expression was contained in a range of values
    **
    ** \param expr An expression
    ** \param min The lower bound limit allowed for the expression `v`
    ** \param max The upper bound limit allowed for the expression `v`
    ** \return The expression itself, or a bound limit
    */
    template<typename T>
    T& MinMax(T& expr, T& min, T& max) {return ((expr < min) ? min : ((expr > max) ? max : expr));}


    /*!
    ** \brief Ensure an expression is contained in a range of values
    **
    ** \param[in,out] expr The expression that must be checked and modified if needed
    ** \param min The lower bound limit allowed for the expression `v`
    ** \param max The upper bound limit allowed for the expression `v`
    ** \return Always `expr`
    */
    template<typename T>
    T& EnsureInRange(T& expr, const T& min, const T& max)
    {
        if (expr < min)
            expr = min;
        else
        {
            if (expr > max)
                expr = max;
        }
        return expr;
    }



} // namespace Math
} // namespace Yuni

#endif // __YUNI_MISC_MATH_H__
