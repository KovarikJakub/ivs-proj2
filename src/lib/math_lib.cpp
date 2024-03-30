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
    /*
    if((x > DBL_MAX) || (y > DBL_MAX) || ((x-y) < DBL_MIN) || (x < DBL_MIN) || (y < DBL_MIN))
    {
        throw std::out_of_range("Error: Value is out of 'DBL LIMIT'!");
    } else
    {
        return (x - y);
    }
   

    const bool underflow = (x < 0 && std::abs(y) >= DBL_MAX + std::abs(x));
    const bool overflow  = (x > 0 && y >= DBL_MAX + std::abs(x));
    if ((y != 0) && (underflow || overflow))
    {
        throw std::out_of_range("Overflow occurred");
    }

    return x - y;

    */

}
double Div(double x, double y)
{
    if((std::abs(x) > DBL_MAX) || (std::abs(y) > DBL_MAX))
    {
        throw std::out_of_range("Error: Value is out of 'DBL LIMIT'!");
    } else if(y == 0)
    {
        throw std::invalid_argument("Error: Divider can not be zero value!");
    }else
    {
        return (x / y);
    }
}
double Mul(double x, double y)
{
    if((std::abs(x) > DBL_MAX) || (std::abs(y) > DBL_MAX) || (abs(x) * abs(y) > DBL_MAX))
    {
        throw std::out_of_range("Error: Value is out of 'DBL LIMIT'!");
    } else
    {
        return (x * y);
    }
}
unsigned long long  Factorial(unsigned int x)
{
    unsigned long long result;

    if (x < 0 || x != std::round(x)) {
        throw std::invalid_argument("Error: The root value must be integer greater than 0!");
    }

    if (x == 0 || x == 1) 
    {
        return 1;
    } else 
    {
        result = x * Factorial(x - 1);
        if (result / x != Factorial(x - 1)) 
        {
            throw std::out_of_range("Error: Factorial result exceeds representable range!");
        }
        return result;
    }
}


double Root(double x, unsigned int y)
{
    if(std::abs(x) > DBL_MAX)
    {
        throw std::out_of_range("Error: Value is out of 'DBL LIMIT'!");
    }else if(y <= 1 || (y != std::round(y)))
    {
        throw std::invalid_argument("Error: The root value must be integer greater than 0!");
    }else
    {
        if(((y % 2) == 0) && (x < 0))
        {
            throw std::invalid_argument("Error: An even square root can not square a negative number!");
        }else 
        {
            return std::pow(x, 1/y);
        }
    }
}

double Pow(double x, unsigned int y)
{
    double result;
    if(std::abs(x) > DBL_MAX)
    {
        throw std::out_of_range("Error: Value is out of 'DBL LIMIT'!");
    }else if(y < 0)
    {
        throw std::invalid_argument("Error: exponent can not be negative number!");
    }else if(((result = std::pow(x, y)), errno != 0) || (std::isinf(pow(x,y))))
    {
        errno = 0;
        throw std::out_of_range("Error: Overflow!");
    }else
    {
        return std::pow(x,y);
    }
}
double Abs(double x)
{
    if(abs(x) > DBL_MAX)
    {
        throw std::out_of_range("Error: Value is out of 'DBL LIMIT', Overflow occurred!");
    }else
    {
        return std::abs(x);
    }
}

