#include <iostream>
#include <cstdint>
#include <cassert>
#include <cmath>

// Extremely naive prime number tester. Just divide by all numbers 2 and greater, up to square
// root of the orignal value.


bool isPrime(int num)
{
    int s = sqrt(num);

    for(int i = 2; i <= s; i++)
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
