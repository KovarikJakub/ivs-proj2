#include <iostream>
#include <vector>
#include <limits>
#include "math_lib.h"

/**
 * @class DeviationDataStream
 * @brief Class to calculate the standard deviation of a stream of data.
 */
class DeviationDataStream
{
public:
    /**
     * @brief Constructor for DeviationDataStream.
     */
    DeviationDataStream() : n(0), mean(0), M2(0) {}  

     /**
     * @brief Add a data point to the stream ( using Welford's algorithm )
     * @param x The data point to be added.
     * Welford's algorithm: https://en.wikipedia.org/wiki/Algorithms_for_calculating_variance
     */
    inline void AddDataPoint(int x)
    {
        n++;
        double delta = Sub(x, mean);
        mean += Div(delta, n);
        double delta2 = Sub(x, mean);
        M2 += Mul(delta, delta2);
    }

    /**
     * @brief Calculate the standard deviation from data added to the stream.
     * @return The standard deviation.
     */
    inline double GetStandardDeviation()
    {
        return Root(M2 / n, 2);
    }

private:
    unsigned long n; ///< Number of data points.
    double mean;     ///< Accumulated mean of the data points.
    double M2;       ///< Accumulated sum of squared differences from the mean.
};

/**
 * @brief Main function to read input numbers from stdin and calculate standard deviation.
 * @return 0 if successful, 1 otherwise.
 */
int main()
{
    DeviationDataStream deviationDataStream;

    int inputNum;

    // read input numbers from stdin as a stream 
    // deviationDataStream accumulates the deviation as the numbers come
    while(std::cin >> inputNum)
    {
        deviationDataStream.AddDataPoint(inputNum);
    }

    // if end of the stdin file wasnt reached, consider it as an error in the input sequence
    if(!std::cin.eof())
    {
        std::cerr << "Error: Invalid input sequence!" << std::endl;
        return 1;
    }

    std::cout << deviationDataStream.GetStandardDeviation() << std::endl;

    return 0;
}