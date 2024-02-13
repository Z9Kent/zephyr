//
// Create a type which holds a count & an array of values with a maximum size
//
// Primarily used for serialization.
//
// template <size_t N, typename count_t, typename value_t> struct valueArray;

#include <cstdint>
#include <cstring>

#pragma once

//namespace z9
//{

template <std::size_t N, typename COUNT_T = uint8_t, typename VALUE_T = uint8_t>
struct variableArray
{
	using T = VALUE_T;
	static const auto MAX = N;

	auto& size () const { return count; }
	constexpr const T* value() const     { return data; }
	const T* operator()() const { return data; }

	bool set(COUNT_T len, const T *value)
	{
		if (len > N)
			return false;           // TODO: error cases: should eventually throw

		auto bytes = len * sizeof(VALUE_T);
		std::memcpy(data, value, bytes);
		count = len;
		return true;
	}

private:
	VALUE_T data[N];
	COUNT_T count;
};

//}