#include <iostream>
#include <vector>
#include <limits>
#include <cmath>

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
        double delta = x - mean;
        mean += delta / n;
        double delta2 = x - mean;
        M2 += delta * delta2;
    }

    /**
     * @brief Calculate the standard deviation from data added to the stream.
     * @return The standard deviation.
     */
    inline double GetStandardDeviation()
    {
        return std::sqrt(M2 / n);
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

    if(!std::cin.eof())
    {
        std::cerr << "Error: Invalid input sequence!" << std::endl;
        return 1;
    }

    std::cout << deviationDataStream.GetStandardDeviation() << std::endl;

    return 0;
}