#include <gtest/gtest.h>
#include "math_lib.h"

using namespace ::testing;

TEST(Addition, test1){

    EXPECT_EQ(Add(1,1),2);
    EXPECT_EQ(Add(-2,1),-1);
    EXPECT_EQ(Add(1,-2),-1);
    EXPECT_EQ(Add(-1,-1),-2);
    EXPECT_EQ(Add(0,0),0);
    
}
TEST(Addition, test2){

    EXPECT_EQ(Add(1.5,1.6),3.1);
    EXPECT_EQ(Add(-2.1,1.1),-1);
    EXPECT_EQ(Add(1.9,-2),-0.1);
    EXPECT_EQ(Add(-1.5,-1.27),-2.77);
    EXPECT_EQ(Add(0,0.001),0.001);

}
TEST(Addition, test3){

    EXPECT_THROW(Add(DBL_MAX,1),std::out_of_range);
    EXPECT_THROW(Add(1.5,DBL_MAX),std::out_of_range);

    EXPECT_EQ(Add(DBL_MAX,0),DBL_MAX);
   
}

TEST(Subtraction, test1){

    EXPECT_EQ(Sub(1,1),0);
    EXPECT_EQ(Sub(-2,1),-3);
    EXPECT_EQ(Sub(1,-2),3);
    EXPECT_EQ(Sub(-1,-1),0);
    EXPECT_EQ(Sub(0,0),0);

}
TEST(Subtraction, test2){

    EXPECT_EQ(Sub(1.5,1.6),-0.1);
    EXPECT_EQ(Sub(-2.1,1.1),-3.2);
    EXPECT_EQ(Sub(1.9,-2),2.9);
    EXPECT_EQ(Sub(-1.5,-1.27),-0.23);
    EXPECT_EQ(Sub(0,0.001),-0.001);

}
TEST(Subtraction, test3){

    EXPECT_THROW(Sub(DBL_MIN,1),std::out_of_range);
    EXPECT_THROW(Sub(DBL_MIN,0.5),std::out_of_range);

    EXPECT_EQ(Sub(DBL_MIN,0),DBL_MIN);
   
}

TEST(Division, test1){

    EXPECT_EQ(Div(1,1),1);
    EXPECT_EQ(Div(8,2),4);
    EXPECT_EQ(Div(6,-3),-2);
    EXPECT_EQ(Div(-6,3),-2);
    EXPECT_EQ(Div(-10,-5),2);
    EXPECT_EQ(Div(0,1),0);

}
TEST(Division, test2){

    EXPECT_EQ(Div(1.5,1.5),1);
    EXPECT_EQ(Div(5,2.5),2);
    EXPECT_EQ(Div(7,-3.5),-2);
    EXPECT_EQ(Div(-7,3.5),-2);
    EXPECT_EQ(Div(-9,-6),1.5);
    EXPECT_EQ(Div(0,-1.42),0);

}
TEST(Division, test3){

    EXPECT_THROW(Div(1,0),std::invalid_argument);
    EXPECT_THROW(Div(0.01,0),std::invalid_argument);
    EXPECT_THROW(Div(0,0),std::invalid_argument);
    EXPECT_THROW(Div(1,DBL_MAX),std::out_of_range);

}

TEST(Multiplication, test1){

    EXPECT_EQ(Mul(1,1),1);
    EXPECT_EQ(Mul(8,2),16);
    EXPECT_EQ(Mul(6,-3),-18);
    EXPECT_EQ(Mul(-6,3),-18);
    EXPECT_EQ(Mul(-10,-5),50);
    EXPECT_EQ(Mul(0,1),0);
    EXPECT_EQ(Mul(1,0),0);
    EXPECT_EQ(Mul(0,0),0);

}
TEST(Multiplication, test2){

    EXPECT_EQ(Mul(1.1,1),1.1);
    EXPECT_EQ(Mul(8,2.5),20);
    EXPECT_EQ(Mul(6,-3.5),-21);
    EXPECT_EQ(Mul(-6.5,3),-19.5);
    EXPECT_EQ(Mul(-0.5,-5),2.5);
    EXPECT_EQ(Mul(0,0.01),0);
  
}
TEST(Multiplication, test3){

    EXPECT_THROW(Mul(DBL_MAX,2),std::out_of_range);
    EXPECT_THROW(Mul(-3.5,DBL_MAX),std::out_of_range);

    EXPECT_EQ(Mul(DBL_MAX,1),DBL_MAX);

}

TEST(Factorial, test1){

    EXPECT_EQ(Factorial(0),1);
    EXPECT_EQ(Factorial(1),1);
    EXPECT_EQ(Factorial(2),2);
    EXPECT_EQ(Factorial(3),6);
    EXPECT_EQ(Factorial(5),120);
    EXPECT_EQ(Factorial(9),362880);

}
TEST(Factorial, test2){

    EXPECT_THROW(Factorial(-1),std::invalid_argument);
    EXPECT_THROW(Factorial(2.5),std::invalid_argument);
    EXPECT_THROW(Factorial(21),std::out_of_range);
  
}

TEST(Root, test1){

    EXPECT_EQ(Root(4,1),4);
    EXPECT_EQ(Root(0,2),0);
    EXPECT_EQ(Root(1,2),1);
    EXPECT_EQ(Root(4,2),2);
    EXPECT_EQ(Root(9,2),3);
    EXPECT_EQ(Root(8,3),2);
    EXPECT_EQ(Root(27,3),3);
    EXPECT_EQ(Root(16,4),2);
    EXPECT_EQ(Root(256,8),2);

}
TEST(Root, test2){

    EXPECT_EQ(Root(1.5,1),1.5);
    EXPECT_EQ(Root(2.25,2),1.5);
    EXPECT_EQ(Root(4.84,2),2.2);
    EXPECT_EQ(Root(75.69,2),8.7);

}
TEST(Root, test3){

    EXPECT_THROW(Root(4,0),std::invalid_argument);
    EXPECT_THROW(Root(-4,2),std::invalid_argument);
    EXPECT_THROW(Root(4,2.5),std::invalid_argument);
    EXPECT_THROW(Root(4,-2),std::invalid_argument);
    EXPECT_THROW(Root(-4.2,-2),std::invalid_argument);
  
}


TEST(Exponentiation, test1){

    EXPECT_EQ(Pow(0,0),1);
    EXPECT_EQ(Pow(2,0),1);
    EXPECT_EQ(Pow(2,1),2);
    EXPECT_EQ(Pow(2,2),4);
    EXPECT_EQ(Pow(2,8),256);
    EXPECT_EQ(Pow(-4,2),16);
    EXPECT_EQ(Pow(-4,3),-64);

}
TEST(Exponentiation, test2){

    EXPECT_EQ(Pow(2.8,0),1);
    EXPECT_EQ(Pow(2.8,1),2.8);
    EXPECT_EQ(Pow(2.5,2),6.25);
    EXPECT_EQ(Pow(-2.5,3),-15.625);
    EXPECT_EQ(Pow(-2.5,4),39.0625);
    
}
TEST(Exponentiation, test3){

    EXPECT_THROW(Pow(2,-1),std::invalid_argument);
    EXPECT_THROW(Pow(2,3.5),std::invalid_argument);
    EXPECT_THROW(Pow(2,-2.5),std::invalid_argument);
    EXPECT_THROW(Pow(DBL_MAX,2),std::out_of_range);
     
}

TEST(Absolute_value, test1){

    EXPECT_EQ(Abs(1),1);
    EXPECT_EQ(Abs(-1),1);
    EXPECT_EQ(Abs(0),0);
    EXPECT_EQ(Abs(52.73),52.73);
    EXPECT_EQ(Abs(-1001.1001),1001.1001);

}