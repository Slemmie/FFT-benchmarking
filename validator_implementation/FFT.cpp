#include <validator_implementation/FFT.h>

namespace VAL_IMPL {
	
	namespace here {
		double pi = std::acos(-1);
	}
	
	std::vector <std::complex <double>> FFT_double(const std::vector <std::complex <double>>& p) {
		int size = p.size();
		if (size <= 1) {
			return p;
		}
		std::vector <std::vector <std::complex <double>>> q(2, std::vector <std::complex <double>> (size / 2));
		for (int i = 0; i < size / 2; i++) {
			q[0][i] = p[i * 2];
			q[1][i] = p[i * 2 + 1];
		}
		q[0] = FFT_double(q[0]);
		q[1] = FFT_double(q[1]);
		double angle = here::pi / (double)size * 2.0;
		std::complex <double> w(1), wn(std::cos(angle), std::sin(angle));
		std::vector <std::complex <double>> result(size);
		for (int i = 0; i < size / 2; i++) {
			std::complex <double> now = w * q[1][i];
			result[i] = q[0][i] + now;
			result[i + size / 2] = q[0][i] - now;
			w *= wn;
		}
		return result;
	}
	
	std::vector <std::complex <long double>> FFT_long_double(const std::vector <std::complex <long double>>& p) {
		int size = p.size();
		if (size <= 1) {
			return p;
		}
		std::vector <std::vector <std::complex <long double>>> q(2, std::vector <std::complex <long double>> (size / 2));
		for (int i = 0; i < size / 2; i++) {
			q[0][i] = p[i * 2];
			q[1][i] = p[i * 2 + 1];
		}
		q[0] = FFT_long_double(q[0]);
		q[1] = FFT_long_double(q[1]);
		long double angle = here::pi / (long double)size * 2.0;
		std::complex <long double> w(1), wn(std::cos(angle), std::sin(angle));
		std::vector <std::complex <long double>> result(size);
		for (int i = 0; i < size / 2; i++) {
			std::complex <long double> now = w * q[1][i];
			result[i] = q[0][i] + now;
			result[i + size / 2] = q[0][i] - now;
			w *= wn;
		}
		return result;
	}
	
} /// namespace VAL_IMPL
