#include <iostream>
#include <cstdint>
#include <cassert>
#include <cmath>

// Showing how "divisibility" could be used to determine if something is a prime.
// The code currently works for numbers that are less than 43^2 (2209). 

using byte = uint8_t;

constexpr int maxDigits = 4;

// Note digits are stores left to right, so the value 247 would be stored as 7, 4, 2.
// \c a is the array of digits for the number \c orig
// \c orig is the stored original value.
// \c size contains the number of digits.
class Digits
{
public:
    Digits(int num);
   
    const byte& operator[](int x) const { assert(x < size); return a[x]; }
    byte& operator[](int x) { assert(x < maxDigits); return a[x]; }
    int Size() const { return size; }
    int Orig() const { return orig; }
private:
    byte a[maxDigits];
    int orig;
    int size;
};


Digits::Digits(int num)
{
    orig = num;
    int i = 0; 
    while(num > 0)
    {
	byte d = num % 10;
	num /= 10;
	assert(i < maxDigits);
	a[i] = d;
	i++;
    }
    size = i;
}

template<typename T, size_t size>
constexpr size_t ArrSize(T(&)[size])
{
    return size;
}

template<int N> 
bool divisible(const Digits& d);

template<>
bool divisible<2>(const Digits& d)
{
    // A number is divisible by 2 if it's even. So reteurn "not odd" (lowest bit == 1 -> odd number)
    return (!(d[0] & 1));
}

template<>
bool divisible<3>(const Digits& d)
{
    // A number is divis
    int sum = 0;
    for (int i = 0; i < d.Size(); i++)
    {
	sum += d[i];
    }
    return (sum % 3 == 0);
}

template<>
bool divisible<5>(const Digits& d)
{
    // Number is divisible by 5 if last digit is 0 or 5.
    return (d[0] == 5) || (d[0] == 0);
}

template<>
bool divisible<7>(const Digits& d)
{
    // 10x + y is divisible by 7 if and only if x − 2y is divisible by 7. We repeat
    // those steps until small enough number.
    int x = d.Orig() / 10;
    int y = d[0];
    int z = abs(x - 2 * y);
    if (z >= 100)
    {
	Digits dd(z);
	return divisible<7>(dd);
    }

    switch (z)
    {
    case 0:
    case 7:
    case 14:
    case 21:
    case 28:
    case 35:
    case 42:
    case 49:
    case 56:
    case 63:
    case 70:
    case 77:
    case 84:
    case 91:
    case 98:
	return true;
    }
    return false;
}

template<>
bool divisible<11>(const Digits& d)
{
    int mul = 1;
    int sum = 0;
    for (int i = 0; i < d.Size(); i++)
    {
	sum += mul * d[i];
	mul = -mul;
    }
    return (sum % 11) == 0;
}

template<>
bool divisible<13>(const Digits& d)
{
    int muls[] = { 1, 10, 9, 12, 3, 4 };
    size_t nmuls = ArrSize(muls);
    int sum = 0;
    for (int i = 0; i < d.Size(); i++)
    {
	sum += muls[i % nmuls] * d[i];
    }
    return (sum % 13) == 0;
}

template<>
bool divisible<17>(const Digits& d)
{
    int x = 2 * d[0];
    int y = 3 * (d.Orig()/10);
    int z = x + y;
    return (z % 17) == 0;
}

template<>
bool divisible<19>(const Digits& d)
{
    int x = 2 * d[0];
    int y = d.Orig()/10;
    int z = x + y;
    return (z % 19) == 0;
}

template<>
bool divisible<23>(const Digits& d)
{
    int x = 3 * (d[0] + d[1]*10);
    int y = d.Orig()/100;
    int z = x + y;
    return (z % 23) == 0;
}

template<>
bool divisible<29>(const Digits& d)
{
    int x = 9 * (d[0] + d[1]*10);
    int y = d.Orig()/100;
    int z = x + y;
    return (z % 29) == 0;
}

template<>
bool divisible<31>(const Digits& d)
{
    int x = 3 * d[0];
    int y = d.Orig()/10;
    int z = abs(y - x);
    if (z >= 100)
    {
	return divisible<31>(Digits(z));
    }
    switch(z)
    {
    case 0:
    case 31:
    case 62:
    case 93:
	return true;
    }
    return false;
}

template<>
bool divisible<37>(const Digits& d)
{
    int x = 11 * d[0];
    int y = d.Orig()/10;
    int z = abs(y - x);
    if (z >= 100)
    {
	return divisible<37>(Digits(z));
    }
    switch(z)
    {
    case 0:
    case 37:
    case 74:
	return true;
    }
    return false;
}

template<>
bool divisible<41>(const Digits& d)
{
    int x = 4 * d[0];
    int y = d.Orig()/10;
    int z = abs(y - x);
    if (z >= 100)
    {
	return divisible<41>(Digits(z));
    }
    switch(z)
    {
    case 0:
    case 41:
    case 82:
	return true;
    }
    return false;
}

template<>
bool divisible<43>(const Digits& d)
{
    int x = 13 * d[0];
    int y = d.Orig()/10;
    int z = abs(y + x);
    if (z >= 100)
    {
	return divisible<43>(Digits(z));
    }
    switch(z)
    {
    case 0:
    case 43:
    case 86:
	return true;
    }
    return false;
}

bool isPrime(int num)
{
    Digits digits(num);

    int s = sqrt(num);

    if (s >= 2)
    {
	if (divisible<2>(digits))
	{
	    return false;
	}
    }
    if (s >= 3)
    {
	if (divisible<3>(digits))
	{
	    return false;
	}
    }
    if (s >= 5)
    {
	if (divisible<5>(digits))
	{
	    return false;
	}
    }
    if (s >= 7)
    {
	if (divisible<7>(digits))
	{
	    return false;
	}
    }
    if (s >= 11)
    {
	if (divisible<11>(digits))
	{
	    return false;
	}
    }
    if (s >= 13)
    {
	if (divisible<13>(digits))
	{
	    return false;
	}
    }
    if (s >= 17)
    {
	if (divisible<17>(digits))
	{
	    return false;
	}
    }
    if (s >= 19)
    {
	if (divisible<19>(digits))
	{
	    return false;
	}
    }
    if (s >= 23)
    {
	if (divisible<23>(digits))
	{
	    return false;
	}
    }
    if (s >= 29)
    {
	if (divisible<29>(digits))
	{
	    return false;
	}
    }
    if (s >= 31)
    {
	if (divisible<31>(digits))
	{
	    return false;
	}
    }
    if (s >= 37)
    {
	if (divisible<37>(digits))
	{
	    return false;
	}
    }
    if (s >= 41)
    {
	if (divisible<41>(digits))
	{
	    return false;
	}
    }
    if (s >= 43)
    {
	if (divisible<43>(digits))
	{
	    return false;
	}
    }
    return true;
}

int main()
{
    int n = 0;
    for(int j = 0; j < 100000; j++)
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
