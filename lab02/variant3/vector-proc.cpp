#include <cmath>
#include <iterator>
#include "vector-proc.h"

constexpr int AVERAGING_FACTOR = 2;
constexpr int MULTIPLYING_FACTOR = 3;

bool IsMultipleOf(double multiple, int factor);

bool ReadVector(std::istream & input, DoubleVector & vector)
{
	typedef std::istream_iterator<double> istream_iterator;
	std::copy(istream_iterator(input), istream_iterator(), std::back_inserter(vector));
	return input.eof();
}

void ProcessVector(DoubleVector & vector)
{
	double sum = 0.0;
	size_t count = 0;
	for (const double item: vector)
	{
		if (IsMultipleOf(item, AVERAGING_FACTOR))
		{
			sum += item;
			++count;
		}
	}

	if (!count)
	{
		return;
	}
	const double avg = sum / count;
	for (double & item: vector)
	{
		if (IsMultipleOf(item, MULTIPLYING_FACTOR))
		{
			item *= avg;
		}
	}
}

bool WriteVector(std::ostream & output, DoubleVector const& vector)
{
	std::copy(vector.begin(), vector.end(), std::ostream_iterator<double>(output, " "));
	return bool(output << '\n');
}

bool IsMultipleOf(double multiple, int factor)
{
	if (modf(multiple, &multiple))
	{
		return false;
	}
	return int(multiple) % factor == 0;
}
