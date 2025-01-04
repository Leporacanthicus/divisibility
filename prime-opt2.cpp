#include <iostream>
#include <cstdint>
#include <cassert>
#include <cmath>
#include <array>

// Slightly optimised prime number finder. Only check prime numbers from a list.


bool isPrime(int num)
{
    int s = sqrt(num);

    static std::array<int, 14> primes{ 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43 };
    for(auto d : primes)
    {
	if (d > s)
	{
	    return true;
	}
	if (!(num % d))
	{
	    return false;   // Not a prime.
	}
    }

    // It's a prime.
    return true;
}

int main()
{
    int n = 0;
    for (int j = 0; j < 100000; j++)
    {
	if (isPrime(2))
	{
	    n++;
	}
	for(int i = 3; i <= 2208; i+=2)
	{
	    if (isPrime(i))
	    {
		n++;
	    }
	}
    }
    std::cout << "Found " << n << " primes" << std::endl;
}
