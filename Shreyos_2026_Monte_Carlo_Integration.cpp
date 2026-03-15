/*
    Simulating PI with Monte Carlo Integration Method.
    
    Monte Carlo Simulation is a way to calculate complex problems where the
    problem candidate space is really large in such cases we can randomly
    select only a subset of candidates and try to solve our problem which
    will give a solution relatively quickly and closer to the actual solution
    compared to the approach if we had considered all the possible candidates.
    
    Outlining the algorithm we get,
    - We consider a unit circle surrounded with a square of length 2
    - We shot random darts/samples within the square
    - We note the number of samples that fall into the circle vs the square
    - We divide the number of samples fell in the circle with the total samples
*/

#include <iomanip>
#include <iostream>
#include <random>
#include <thread>

double getRandomSample(double min, double max) {
  static std::mt19937_64 generator{std::random_device{}()};
  static std::uniform_real_distribution<double> dist{min, max};

  return dist(generator);
}

int main(int argc, char *argv[]) {

  int count = 0;
  std::cout << "\nPlease enter the number of times to run the pi approximation "
               "code => ";
  std::cin >> count;
  if (count < 0) {
    std::cout
        << "\nInvalid input given please provide a valid positive integer!";
  }

  while (count--) {
    uint64_t samples, inCircle = 0;
    double pi = 0.0;

    std::cout << "\nPlease enter the number of samples to run => ";
    if (!(std::cin >> samples) || samples == 0) {
      std::cout << "Invalid input.\n";
      break;
    }

    for (uint64_t i = 0; i < samples; i++) {
      double x = getRandomSample(-1.0, 1.0);
      double y = getRandomSample(-1.0, 1.0);

      if ((x * x + y * y) <= 1) {
        inCircle++;
      }
    }

    pi = 4.0 * static_cast<double>(inCircle) / samples;
    std::cout << "\r" << std::string(100, ' ')
              << "\rThe approximate value of Pi is => " << std::setprecision(15)
              << pi << std::flush << "\n";
  }

  return 0;
}