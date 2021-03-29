#include <cmath>
#include <iterator>
#include "vector-proc.h"

bool IsMultipleOf(double multiple, long long factor);

bool ReadVector(std::istream & input, Vector & vector)
{
	typedef std::istream_iterator<double> istream_iterator;
	std::copy(istream_iterator(input), istream_iterator(), std::back_inserter(vector));
	return input.eof();
}

void ProcessVector(Vector & vector)
{
	double sum = 0.0;
	size_t count = 0;
	for (const double item: vector)
	{
		if (IsMultipleOf(item, 2))
		{
			sum += item;
			++count;
		}
	}

	const double avg = sum / count;
	for (double & item: vector)
	{
		if (IsMultipleOf(item, 3))
		{
			item *= avg;
		}
	}
}

bool WriteVector(std::ostream & output, Vector const& vector)
{
	std::copy(vector.begin(), vector.end(), std::ostream_iterator<double>(output, " "));
	return bool(output << '\n');
}

bool IsMultipleOf(double multiple, long long factor)
{
	if (modf(multiple, &multiple))
	{
		return false;
	}
	return (long long)multiple % factor == 0;
}
