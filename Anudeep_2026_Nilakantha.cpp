/*
	This logic uses Nilakantha Formula to calculate Pi
	π=3+k∑(−1)k+1(2k)(2k+1)(2k+2)4​
*/

#include <iostream>
#include <iomanip>

int main()
{
	long long N;
	std::cout << "Enter number of terms for precision: ";
	std::cin >> N;
	
	long double pi = 3.0L;
	long double sign = 1.0L;
	
	for (long long k = 1; k <= N; ++k)
	{
		long double a = 2.0L * k;
		long double term = 4.0L / (a * (a + 1.0L) * (a + 2.0L));
		pi += sign * term;
		sign = -sign;
	}
	
	std::cout << std::setprecision(15);
	std::cout << "Pi = " << pi << std::endl;
	
	return 0;
}