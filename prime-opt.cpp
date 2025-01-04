#include <iostream>
#include <cstdint>
#include <cassert>
#include <cmath>

// Slightly optimised prime number finder. Only check odd numbers above 2.


bool isPrime(int num)
{
    int s = sqrt(num);

    if (!(num % 2))
    {
	return false;
    }
	
    for(int i = 3; i <= s; i += 2)
    {
	if (!(num % i))
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
	for(int i = 2; i <= 2208; i++)
	{
	    if (isPrime(i))
	    {
		n++;
	    }
	}
    }
    std::cout << "Found " << n << " primes" << std::endl;
}
