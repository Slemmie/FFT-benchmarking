#pragma once

#include <vector>
#include <iostream>
#include <iomanip>
#include <string>
#include <complex>

namespace util {
	
	void print_time(std::string message, long long time);
	void print_time(std::string message, long long time, long long avg);
	void print_progress(int now, int total, const std::string& label = "");
	template <typename A> A get_avg(const std::vector <A>& v);
	
	void print_time(std::string message, long long time) {
		if ((int)message.size() > 80) {
			while ((int)message.size() < 100) {
				message += ' ';
			}
		}
		while ((int)message.size() < 80) {
			message += ' ';
		}
		double d_time = (double)time * 0.001;
		std::cerr << message << ": " << std::fixed << std::setprecision(3) << d_time << " ms" << std::endl;
	}
	
	void print_time(std::string message, long long time, long long avg) {
		if ((int)message.size() > 80) {
			while ((int)message.size() < 100) {
				message += ' ';
			}
		}
		while ((int)message.size() < 80) {
			message += ' ';
		}
		double d_time = (double)time * 0.001;
		double d_time_avg = (double)avg * 0.001;
		std::cerr << message << ": " << std::fixed << std::setprecision(3) << d_time << " ms (avg: " <<
		d_time_avg << " ms)" << std::endl;
	}
	
	void print_progress(int now, int total, const std::string& label) {
		std::cerr << "\r" << label << (label.empty() ? "" : ": ") << "[";
		double one = (double)total / 100.0;
		double pri = (double)now / one;
		for (int i = 0; i < 100; i++) {
			if (i < pri) {
				std::cerr << "#";
			} else {
				std::cerr << ".";
			}
		}
		std::cerr << "]" << std::flush;
		if (now == total) {
			std::cerr << std::endl;
		}
	}
	
	void print_progress(int now, int total, const std::string& label, const std::string& trail_msg) {
		std::cerr << "\r" << label << (label.empty() ? "" : ": ") << "[";
		double one = (double)total / 100.0;
		double pri = (double)now / one;
		for (int i = 0; i < 100; i++) {
			if (i < pri) {
				std::cerr << "#";
			} else {
				std::cerr << ".";
			}
		}
		std::cerr << "] " << trail_msg << std::flush;
		if (now == total) {
			std::cerr << std::endl;
		}
	}
	
	template <typename A> A get_avg(const std::vector <A>& v) {
		A sum = 0;
		for (const A& x : v) {
			sum += x;
		}
		return sum / A(v.size());
	}
	
	template <typename A> bool compare(A v1, A v2) {
		return v1 == v2;
	}
	
	template <> bool compare(std::complex <double> v1, std::complex <double> v2) {
		return fabs(v1.real() - v2.real()) < 1e-10 && fabs(v1.imag() - v2.imag()) <= 1e-10;
	}
	
	template <> bool compare(std::complex <long double> v1, std::complex <long double> v2) {
		return fabs(v1.real() - v2.real()) < 1e-15 && fabs(v1.imag() - v2.imag()) <= 1e-15;
	}
	
} /// namepsace util
