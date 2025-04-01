// Pi_Monte_Carlo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <random>
#include <future>
#include <iomanip>
#include <thread>
#include <vector>
#include <numeric>
#include <chrono>
#include <Windows.h>

/**
     Consider a square of 2 units in length a side whose center is placed at origin. Consider
     a quarter circle of 1 unit radius, again whose center is from the origin. Try to find a random 
     point in the first quadrant from (0.0, 1.0) and sample the same and count how many are hitting
     inside the circle out of total points.
*/

inline bool missCircle(double x, double y)
{
    return x * x + y * y > 1;
}

int main()
{
    do
    {
        size_t samples(0);
        size_t numThreads(0);
        std::atomic<size_t> pendingJobCount(0);

        std::cout << "Please provide number of samples to run Monte Carlo Simulation to calculate PI: " << std::endl;
        std::cin >> samples;

        std::cout << "Please provide number of threads to use: " << std::endl;
        std::cin >> numThreads;

        if (numThreads > std::thread::hardware_concurrency() || numThreads < 0)
        {
            numThreads = std::thread::hardware_concurrency();
        }

        std::vector<size_t> hitPoints(numThreads, 0);

        auto monte_carlo = [&hitPoints, &pendingJobCount](double i, double max, size_t index)
        {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution dist(0.0, 1.0);

            double x(0.0);
            double y(0.0);

            while (i < max)
            {
                x = dist(gen);
                y = dist(gen);

                if (!missCircle(x, y))
                    ++hitPoints[index];

                ++i;
            }
            --pendingJobCount;
        };

        double stepSize = samples / numThreads;
        double remainingStep = samples % numThreads;

        auto start = std::chrono::high_resolution_clock::now();

        std::vector<std::thread> threadPool;
        for (size_t i = 0; i < numThreads; i++)
        {
            double min = stepSize * i;
            double max = stepSize * (i + 1) - 1 + (i == numThreads - 1 ? remainingStep : 0);
            threadPool.push_back(std::thread(monte_carlo, min, max, i));
            ++pendingJobCount;
        }

        while (pendingJobCount != 0)
        {
        }

        for (auto& task : threadPool)
        {
            task.join();
        }

        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double, std::milli> duration = end - start;
        std::cout << "Time taken by function: " << duration.count() << " ms" << std::endl;

        size_t totalHitPoints = std::accumulate(hitPoints.begin(), hitPoints.end(), 0);

        long double PI = 4.0 * totalHitPoints / samples;
        std::cout << "PI = ";
        std::cout << std::setprecision(30) << PI << std::endl;

        int input;
        std::cout << "Enter -1 to exit: " << std::endl;
        std::cin >> input;

        if (input == -1)
            break;
    } while (true);

    return 0;
}
