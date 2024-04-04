#include "math_lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <cfloat>
#include <stdexcept>
#include <cmath>
#include <cerrno>


double Add(double x, double y)
{ 
    const bool underflow = (x < 0 && std::abs(y) >= DBL_MAX - std::abs(x));
    const bool overflow  = (x > 0 && y >= DBL_MAX - std::abs(x));
    if ((y != 0) && (underflow || overflow))
    {
        throw std::out_of_range("Overflow occurred");
    }

    return x + y;
}
double Sub(double x, double y)
{
    if (x < (-DBL_MAX + std::abs(y)))                      
    {
        throw std::out_of_range("Underflow occurred");
    }

    return Add(x, -y); 
}
double Div(double x, double y)
{
    double result = x / y;
    if(y == 0)
    {
        throw std::invalid_argument("Error: Divider can not be zero value!");
    }
    else if(x == -DBL_MAX && y == -1)
    {
        throw std::out_of_range("Error: Overflow occurred!");
    }
    else if(std::isinf(result) || std::isnan(result))
    {
        throw std::out_of_range("Error: Overflow occurred!");
    }
 
    return result;
    
}
double Mul(double x, double y)
{
    if(std::abs(x) > (DBL_MAX / std::abs(y)))
    {
        throw std::out_of_range("Error: Overflow occurred!");
    }

    return (x * y);
    
}
unsigned long long Factorial(unsigned int x)
{
    if(x >= 21)
    {
        throw std::out_of_range("Error: Factorial of a number larger than 21 exceeds unsigned long long range");
    }

    unsigned long long result = 1;
    for(int i = 1; i <= x; ++i)
    {
        result *= i;
    }
    return result;
}

double Root(double x, unsigned int y)
{
    if(y == 0)
    {
        throw std::invalid_argument("Error: Root can not be zero!");
    }
    if(((y % 2) == 0) && (x < 0))
    {
        throw std::invalid_argument("Error: An even root can not root a negative number!");
    }

    return std::pow(std::abs(x), 1.0 / y) * (x < 0 ? -1 : 1);
    
}

double Pow(double x, unsigned int y)
{
    double result = std::pow(x, y);

    if (result == HUGE_VAL || result == -HUGE_VAL) 
    {
        throw std::out_of_range("Error: Overflow occurred!");
    } 
    
    return result;
}

double Abs(double x)
{
    return std::abs(x);
}

