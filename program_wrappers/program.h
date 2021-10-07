#pragma once

#include <timer/timer.h>

#include <functional>
#include <complex>
#include <cassert>

// first template paramter: data type of input (i.e. int/double/etc.)
// second template parameter: data type of return values (must be floating point types such as double)
template <typename DATA_TYPE, typename RETURN_DATA_TYPE> class Program {
	
public:
	
	Program(const std::function <std::vector <std::complex <RETURN_DATA_TYPE>>
	(const std::vector <DATA_TYPE>&)>& _function) {
		static_assert(
		std::is_same <RETURN_DATA_TYPE, float>::value ||
		std::is_same <RETURN_DATA_TYPE, double>::value ||
		std::is_same <RETURN_DATA_TYPE, long double>::value);
	}
	
	std::vector <std::complex <RETURN_DATA_TYPE>>
	execute(const std::vector <DATA_TYPE>& input, long long& execution_time) {
		Timer timer;
		std::vector <std::complex <RETURN_DATA_TYPE>> result = m_function(input);
		execution_time = timer.split();
		return result;
	}
	
private:
	
	std::function <std::vector <std::complex <RETURN_DATA_TYPE>>
	(const std::vector <DATA_TYPE>&)> m_function;
	
};
