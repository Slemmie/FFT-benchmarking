#include <variations/FFT.h>

namespace VARIATIONS {
	
	namespace here {
		double pi = std::acos(-1);
		int ctz(unsigned int x) {
			int r = 0;
			if (!(x & 0x0000FFFF)) {
				r += 16;
				x >>= 16;
			}
			if (!(x & 0x000000FF)) {
				r += 8;
				x >>= 8;
			}
			if (!(x & 0x0000000F)) {
				r += 4;
				x >>= 4;
			}
			if (!(x & 0x00000003)) {
				r += 2;
				x >>= 2;
			}
			return r + ((x & 1) ^ 1);
		}
		inline void initWN(std::complex <double>* arr, const unsigned int size) {
			for (unsigned int i = 0; i < size; i++) {
				double angle = pi / double(1 << i) * 2.0;
				arr[i] = std::complex <double> (std::cos(angle), std::sin(angle));
			}
		}
	}
	
	std::vector <std::complex <double>> FFT_v1_double(const std::vector <double>& p) {
		int size = p.size();
		if (size <= 1) {
			return std::vector <std::complex <double>> (p.begin(), p.end());
		}
		std::vector <std::vector <double>> q(2, std::vector <double> (size / 2));
		for (int i = 0; i < size / 2; i++) {
			q[0][i] = p[i * 2];
			q[1][i] = p[i * 2 + 1];
		}
		auto q0 = FFT_v1_double(q[0]);
		auto q1 = FFT_v1_double(q[1]);
		double angle = here::pi / (double)size * 2.0;
		std::complex <double> w(1), wn(std::cos(angle), std::sin(angle));
		std::vector <std::complex <double>> result(size);
		for (int i = 0; i < size / 2; i++) {
			std::complex <double> now = w * q1[i];
			result[i] = now + q0[i];
			result[i + size / 2] = -now + q0[i];
			w *= wn;
		}
		return result;
	}
	
	std::vector <std::complex <long double>> FFT_v1_long_double(const std::vector <long double>& p) {
		int size = p.size();
		if (size <= 1) {
			return std::vector <std::complex <long double>> (p.begin(), p.end());
		}
		std::vector <std::vector <long double>> q(2, std::vector <long double> (size / 2));
		for (int i = 0; i < size / 2; i++) {
			q[0][i] = p[i * 2];
			q[1][i] = p[i * 2 + 1];
		}
		auto q0 = FFT_v1_long_double(q[0]);
		auto q1 = FFT_v1_long_double(q[1]);
		long double angle = here::pi / (long double)size * 2.0;
		std::complex <long double> w(1), wn(std::cos(angle), std::sin(angle));
		std::vector <std::complex <long double>> result(size);
		for (int i = 0; i < size / 2; i++) {
			std::complex <long double> now = w * q1[i];
			result[i] = now + q0[i];
			result[i + size / 2] = -now + q0[i];
			w *= wn;
		}
		return result;
	}
	
	std::vector <std::complex <double>> FFT_v2_double(const std::vector <double>& p) {
		int size = p.size();
		if (size <= 1) {
			return std::vector <std::complex <double>> (p.begin(), p.end());
		}
		std::vector <std::vector <double>> q(2, std::vector <double> (size / 2));
		for (int i = 0; i < size / 2; i++) {
			q[0][i] = p[i * 2];
			q[1][i] = p[i * 2 + 1];
		}
		auto q0 = FFT_v1_double(q[0]);
		auto q1 = FFT_v1_double(q[1]);
		static bool is_init = false;
		static std::complex <double> WN[21];
		if (!is_init) {
			here::initWN(WN, 21);
			is_init = true;
		}
		std::complex <double> w(1), wn = WN[here::ctz(size)];
		std::vector <std::complex <double>> result(size);
		for (int i = 0; i < size / 2; i++) {
			std::complex <double> now = w * q1[i];
			result[i] = now + q0[i];
			result[i + size / 2] = -now + q0[i];
			w *= wn;
		}
		return result;
	}
	
} /// namespace VAL_IMPL
