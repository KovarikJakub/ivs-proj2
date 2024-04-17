// $Authors:     David Švancer <xsvancd00@stud.fit.vutbr.cz>
//               Vít Vaňatka    <xvanatv00@stud.fit.vutbr.cz>
//               Jakub Kovařík   <xkovarj00@stud.fit.vutbr.cz>
//============================================================================//
/**
 * @file math_lib.tests.cpp
 * @author David Švancer
 * @author Vít Vaňatka
 * @author Jakub Kovařík
 *
 * @brief Google test for math_lib.
 */
#include <gtest/gtest.h>
#include "math_lib.h"

#define MAX_ABS_ERROR 1e-10
#define EXPECT_DOUBLE_NEAR(val1,val2) EXPECT_NEAR(val1,val2,MAX_ABS_ERROR)

using namespace ::testing;

TEST(Addition, test_integers){
    
    EXPECT_DOUBLE_NEAR(Add(1,1),2);
    EXPECT_DOUBLE_NEAR(Add(1,1),2);
    EXPECT_DOUBLE_NEAR(Add(-2,1),-1);
    EXPECT_DOUBLE_NEAR(Add(1,-2),-1);
    EXPECT_DOUBLE_NEAR(Add(-1,-1),-2);
    EXPECT_DOUBLE_NEAR(Add(0,0),0);

}
TEST(Addition, test_decimal){

    EXPECT_DOUBLE_NEAR(Add(1.5,1.6),3.1);
    EXPECT_DOUBLE_NEAR(Add(-2.1,1.1),-1);
    EXPECT_DOUBLE_NEAR(Add(1.9,-2),-0.1);
    EXPECT_DOUBLE_NEAR(Add(-1.5,-1.27),-2.77);
    EXPECT_DOUBLE_NEAR(Add(0,0.001),0.001);

}
TEST(Addition, test_edge_cases){

    EXPECT_THROW(Add(DBL_MAX,1), std::out_of_range);
    EXPECT_THROW(Add(1.5,DBL_MAX),std::out_of_range);
    EXPECT_DOUBLE_NEAR(Add(DBL_MAX,0),DBL_MAX);

}
TEST(Subtraction, test_integers){

    EXPECT_DOUBLE_NEAR(Sub(1,1),0);
    EXPECT_DOUBLE_NEAR(Sub(-2,1),-3);
    EXPECT_DOUBLE_NEAR(Sub(1,-2),3);
    EXPECT_DOUBLE_NEAR(Sub(-1,-1),0);
    EXPECT_DOUBLE_NEAR(Sub(0,0),0);

}
TEST(Subtraction, test_decimal){

    EXPECT_DOUBLE_NEAR(Sub(1.5,1.6),-0.1);
    EXPECT_DOUBLE_NEAR(Sub(-2.1,1.1),-3.2);
    EXPECT_DOUBLE_NEAR(Sub(1.9,-2),3.9);
    EXPECT_DOUBLE_NEAR(Sub(-1.5,-1.27),-0.23);
    EXPECT_DOUBLE_NEAR(Sub(0,0.001),-0.001);
    
}
TEST(Subtraction, test_edge_cases){
    
    EXPECT_THROW(Sub(-DBL_MAX,1),std::out_of_range);
    EXPECT_THROW(Sub(-DBL_MAX,0.5),std::out_of_range);
    EXPECT_DOUBLE_NEAR(Sub(-DBL_MAX,0),-DBL_MAX);

}
TEST(Division, test_integers){

    EXPECT_DOUBLE_NEAR(Div(1,1),1);
    EXPECT_DOUBLE_NEAR(Div(8,2),4);
    EXPECT_DOUBLE_NEAR(Div(6,-3),-2);
    EXPECT_DOUBLE_NEAR(Div(-6,3),-2);
    EXPECT_DOUBLE_NEAR(Div(-10,-5),2);
    EXPECT_DOUBLE_NEAR(Div(0,1),0);

}
TEST(Division, test_decimal){
    
    EXPECT_DOUBLE_NEAR(Div(1.5,1.5),1);
    EXPECT_DOUBLE_NEAR(Div(5,2.5),2);
    EXPECT_DOUBLE_NEAR(Div(7,-3.5),-2);
    EXPECT_DOUBLE_NEAR(Div(-7,3.5),-2);
    EXPECT_DOUBLE_NEAR(Div(-9,-6),1.5);
    EXPECT_DOUBLE_NEAR(Div(0,-1.42),0);

}
TEST(Division, test_edge_cases_and_exceptions){

    EXPECT_THROW(Div(1,0),std::invalid_argument);
    EXPECT_THROW(Div(0.01,0),std::invalid_argument);
    EXPECT_THROW(Div(0,0),std::invalid_argument);

}
TEST(Multiplication, test_integers){

    EXPECT_DOUBLE_NEAR(Mul(1,1),1);
    EXPECT_DOUBLE_NEAR(Mul(8,2),16);
    EXPECT_DOUBLE_NEAR(Mul(6,-3),-18);
    EXPECT_DOUBLE_NEAR(Mul(-6,3),-18);
    EXPECT_DOUBLE_NEAR(Mul(-10,-5),50);
    EXPECT_DOUBLE_NEAR(Mul(0,1),0);
    EXPECT_DOUBLE_NEAR(Mul(1,0),0);
    EXPECT_DOUBLE_NEAR(Mul(0,0),0);

}
TEST(Multiplication, test_decimal){

    EXPECT_DOUBLE_NEAR(Mul(1.1,1),1.1);
    EXPECT_DOUBLE_NEAR(Mul(8,2.5),20);
    EXPECT_DOUBLE_NEAR(Mul(6,-3.5),-21);
    EXPECT_DOUBLE_NEAR(Mul(-6.5,3),-19.5);
    EXPECT_DOUBLE_NEAR(Mul(-0.5,-5),2.5);
    EXPECT_DOUBLE_NEAR(Mul(0,0.01),0);

}
TEST(Multiplication, test_edge_cases){

    EXPECT_THROW(Mul(DBL_MAX,2),std::out_of_range);
    EXPECT_THROW(Mul(-3.5,DBL_MAX),std::out_of_range);
    EXPECT_DOUBLE_NEAR(Mul(DBL_MAX,1),DBL_MAX);

}
TEST(Factorial, test_integers){

    EXPECT_EQ(Factorial(0),1);
    EXPECT_EQ(Factorial(1),1);
    EXPECT_EQ(Factorial(2),2);
    EXPECT_EQ(Factorial(3),6);
    EXPECT_EQ(Factorial(5),120);
    EXPECT_EQ(Factorial(9),362880);

}
TEST(Factorial, test_edge_cases){

    EXPECT_THROW(Factorial(21),std::out_of_range);
  
}
TEST(Root, test_integers){

    EXPECT_DOUBLE_NEAR(Root(4,1),4);
    EXPECT_DOUBLE_NEAR(Root(0,2),0);
    EXPECT_DOUBLE_NEAR(Root(1,2),1);
    EXPECT_DOUBLE_NEAR(Root(4,2),2);
    EXPECT_DOUBLE_NEAR(Root(9,2),3);
    EXPECT_DOUBLE_NEAR(Root(-8,3),-2);
    EXPECT_DOUBLE_NEAR(Root(-27,3),-3);
    EXPECT_DOUBLE_NEAR(Root(16,4),2);
    EXPECT_DOUBLE_NEAR(Root(256,8),2);

}
TEST(Root, test_decimal){

    EXPECT_DOUBLE_NEAR(Root(1.5,1),1.5);
    EXPECT_DOUBLE_NEAR(Root(2.25,2),1.5);
    EXPECT_DOUBLE_NEAR(Root(4.84,2),2.2);
    EXPECT_DOUBLE_NEAR(Root(75.69,2),8.7);

}
TEST(Root, test_exceptions){

    EXPECT_THROW(Root(4,0),std::invalid_argument);
    EXPECT_THROW(Root(-4,2),std::invalid_argument);
    EXPECT_THROW(Root(-4,-2),std::invalid_argument);
    
}
TEST(Exponentiation, test_integers){

    EXPECT_DOUBLE_NEAR(Pow(0,0),1);
    EXPECT_DOUBLE_NEAR(Pow(2,0),1);
    EXPECT_DOUBLE_NEAR(Pow(2,1),2);
    EXPECT_DOUBLE_NEAR(Pow(2,2),4);
    EXPECT_DOUBLE_NEAR(Pow(2,8),256);
    EXPECT_DOUBLE_NEAR(Pow(-4,2),16);
    EXPECT_DOUBLE_NEAR(Pow(-4,3),-64);

}
TEST(Exponentiation, test_decimal){

    EXPECT_DOUBLE_NEAR(Pow(2.8,0),1);
    EXPECT_DOUBLE_NEAR(Pow(2.8,1),2.8);
    EXPECT_DOUBLE_NEAR(Pow(2.5,2),6.25);
    EXPECT_DOUBLE_NEAR(Pow(-2.5,3),-15.625);
    EXPECT_DOUBLE_NEAR(Pow(-2.5,4),39.0625);
    
}
TEST(Exponentiation, test_edge_cases){

    EXPECT_THROW(Pow(DBL_MAX,2),std::out_of_range);
     
}
TEST(Absolute_value, test_all){

    EXPECT_DOUBLE_NEAR(Abs(1),1);
    EXPECT_DOUBLE_NEAR(Abs(-1),1);
    EXPECT_DOUBLE_NEAR(Abs(0),0);
    EXPECT_DOUBLE_NEAR(Abs(52.73),52.73);
    EXPECT_DOUBLE_NEAR(Abs(-1001.1001),1001.1001);

}