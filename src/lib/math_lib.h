// $Authors:     David Švancer <xsvancd00@stud.fit.vutbr.cz>
//               Vít Vaňatka    <xvanatv00@stud.fit.vutbr.cz>
//               Jakub Kovařík   <xkovarj00@stud.fit.vutbr.cz>
//============================================================================//
/**
 * @file math_lib.h
 * @author David Švancer
 * @author Vít Vaňatka
 * @author Jakub Kovařík
 *
 * @brief Definition of mathematic library.
 */

#ifndef MATH_LIB_H
#define MATH_LIB_H


/**
* @brief Function for the mathematical sum of two numbers.
* @param[in] x	The first value for the mathematical sum.
* @param[in] y	The second value for the mathematical sum.
* @return Returns the value after performing the mathematical addition.
* @exception If add fails, it throws exception.
*/
double Add(double x, double y);

/**
* @brief Function for the mathematical subtraction of two numbers.
* @param[in] x	The first value for the mathematical subtraction.
* @param[in] y	The second value for the mathematical subtraction.
* @return Returns the value after performing the mathematical subtraction.
* @exception If subtraction fails, it throws exception.
*/
double Sub(double x, double y);

/**
* @brief Function for the mathematical division.
* @param[in] x	The first value is mathematical divident.
* @param[in] y	The second value is mathematical divisor.
* @return Returns the value after performing the mathematical division.
* @exception If division fails, it throws exception.
*/
double Div(double x, double y);

/**
* @brief Function for the mathematical multiplication.
* @param[in] x	The first value for mathematical multiplication.
* @param[in] y	The second value for mathematical multiplication.
* @return Returns the value after performing the mathematical multiplication.
* @exception If multiplication fails, it throws exception.
*/
double Mul(double x, double y);

/**
* @brief Function to calculate the factorial of the number.
* @param[in] x	The value from which the factorial is calculated.
* @return Returns the value after calculating the factorial from the specified number.
* @exception If factorial fails, it throws exception.
*/
unsigned long long Factorial(unsigned int x);

/**
* @brief Function to calculate the root.
* @param[in] x	The number to be squared.
* @param[in] y	Y-root from a number.
* @return Returns the value after performing the mathematical root.
* @exception If root fails, it throws exception.
*/
double Root(double x, unsigned int y);

/**
* @brief Function for the mathematical powers.
* @param[in] x	The first number is base.
* @param[in] y	The second value is exponent.
* @return Returns the value after performing the mathematical powers.
* @exception If pow fails, it throws exception.
*/
double Pow(double x, unsigned int y);

/**
* @brief Function for calculating absolute value.
* @param[in] x	The value from which the absolute value will be calculated.
* @return Returns absolute value.
*/
double Abs(double x);

#endif