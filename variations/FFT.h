#pragma once

#include <vector>
#include <complex>

namespace VARIATIONS {
	
	std::vector <std::complex <double>> FFT_v1_double(const std::vector <double>& p);
	std::vector <std::complex <long double>> FFT_v1_long_double(const std::vector <long double>& p);
	
	std::vector <std::complex <double>> FFT_v2_double(const std::vector <double>& p);
	
} /// namespace VAL_IMPL
