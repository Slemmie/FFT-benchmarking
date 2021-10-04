#pragma once

#include <functional>

// first template paramter: data type of input (i.e. int/double/etc.)
// second template parameter: data type of return values (must be floating point types such as double)
template <typename DATA_TYPE, typename RETURN_DATA_TYPE> class Program {
	
public:
	
	Program(const std::function <std::vector <std::complex <RETURN_DATA_TYPE>>
	(const std::vector <DATA_TYPE>&)>& _function);
	
	std::vector <std::complex <RETURN_DATA_TYPE>>
	execute(const std::vector <DATA_TYPE>& input, long long& execution_time);
	
private:
	
	std::function <std::vector <std::complex <RETURN_DATA_TYPE>>
	(const std::vector <DATA_TYPE>&)> m_function;
	
};
