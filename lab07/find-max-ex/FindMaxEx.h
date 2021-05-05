#pragma once
#include <vector>

template<typename T, typename Less>
bool FindMax(std::vector<T> const& arr, T& maxValue, Less const& less)
{
	auto iter = arr.begin();
	if (iter == arr.end())
	{
		return false;
	}

	const T* max = &*iter;
	while (++iter != arr.end())
	{
		if (less(*max, *iter))
		{
			max = &*iter;
		}
	}
	maxValue = *max;
	return true;
}
