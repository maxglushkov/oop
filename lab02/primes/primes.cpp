#include <vector>
#include "primes.h"
using std::set;

constexpr int MIN_PRIME = 2;

set<int> GeneratePrimeNumbersSet(int upperBound)
{
	set<int> primes;
	if (upperBound < MIN_PRIME) return primes;

	std::vector<bool> isPrime;
	isPrime.resize(upperBound + 1, true);

	for (int factor = MIN_PRIME;; ++factor)
	{
		if (!isPrime[factor]) continue;

		int divisible = factor * factor;
		if (divisible > upperBound) break;

		do isPrime[divisible] = false;
		while ((divisible += factor) <= upperBound);
	}

	for (int number = MIN_PRIME; number <= upperBound; ++number)
	{
		if (isPrime[number]) primes.insert(primes.end(), number);
	}
	return primes;
}
