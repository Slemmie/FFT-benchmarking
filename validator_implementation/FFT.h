#pragma once

#include <vector>
#include <complex>

namespace VAL_IMPL {
	
	std::vector <std::complex <double>> FFT_double(const std::vector <std::complex <double>>& p);
	
	std::vector <std::complex <long double>> FFT_long_double(const std::vector <std::complex <long double>>& p);
	
} /// namespace VAL_IMPL
