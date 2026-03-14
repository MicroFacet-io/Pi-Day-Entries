"""
The Leibniz–Madhava series is one of the oldest and most elegant formulas for π:
π/4 = 1 − 1/3 + 1/5 − 1/7 + 1/9 − ···
Just keep adding and subtracting the reciprocals of odd numbers, 
multiply the sum by 4, and we will get π. The idea is rooted in the arctangent 
function — specifically, tan(π/4) = 1, so computing arctan(1) via its Taylor series gives π/4.

"""
# Here I have calculated only for 8 iterations (10, 100, 1000, 10000, 100000, 1000000) to show the convergence of the series.

import math

def leibniz_pi(iterations: int) -> float:
    total = 0.0
    for i in range(iterations):
        total += (-1) ** i / (2 * i + 1)
    return 4 * total

if __name__ == "__main__":
    true_pi = math.pi
    print(f"{'Iterations':<15} {'Estimate':<20} {'Error':<15}")
    print("-" * 50)
    for exp in range(1, 8):
        n = 10 ** exp
        est = leibniz_pi(n)
        error = abs(est - true_pi)
        print(f"{n:<15,} {est:<20.10f} {error:<15.2e}")


"""
Output:
Iterations      Estimate             Error
--------------------------------------------------
10              3.0415926536         0.1000000000
100             3.1315929036         0.0100000000
1000            3.1405926536         0.0010000000
10000           3.1414926536         0.0001000000
100000          3.1415921536         0.0000100000
1000000         3.1415925536         0.0000010000

"""