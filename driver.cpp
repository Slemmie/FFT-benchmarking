#include <validator_implementation/FFT.h>
#include <variations/FFT.h>

#include <timer/timer.h>
#include <util/util.h>

#include <vector>
#include <iostream>
#include <string>
#include <complex>

constexpr size_t NUM_INPUTS = 10;
std::vector <std::vector <double>> input_double(NUM_INPUTS);
std::vector <std::vector <long double>> input_long_double(NUM_INPUTS);

std::vector <std::vector <std::complex <double>>> output_double_correct(NUM_INPUTS);
std::vector <std::vector <std::complex <long double>>> output_long_double_correct(NUM_INPUTS);

std::vector <std::vector <std::complex <double>>> output_double_variation1(NUM_INPUTS);
std::vector <std::vector <std::complex <long double>>> output_long_double_variation1(NUM_INPUTS);

void read_input();

template <typename A>
void validate(const std::string& what,
const std::vector <std::vector <A>>& output,
const std::vector <std::vector <A>>& validation);

namespace run {
	void validator_implementation_FFT_double();
	void validator_implementation_FFT_long_double();
	void variation_1_FFT_double();
	void variation_1_FFT_long_double();
}

struct Summary_Item {
	std::string name;
	long long time, avg;
	Summary_Item(const std::string& _name, long long _time, long long _avg) :
	name(_name), time(_time), avg(_avg) { }
	Summary_Item(const std::string& _name, long long _time) :
	name(_name), time(_time), avg(-1) { }
};

std::vector <Summary_Item> summary_items;

int main() {
	
	read_input();
	
	run::validator_implementation_FFT_double();
	run::validator_implementation_FFT_long_double();
	run::variation_1_FFT_double();
	validate("variation1/FFT (double)", output_double_variation1, output_double_correct);
	run::variation_1_FFT_long_double();
	validate("variation1/FFT (long double)", output_long_double_variation1, output_long_double_correct);
	
	std::cerr << "* summary *" << std::endl;
	for (Summary_Item& item : summary_items) {
		if (item.avg == -1) {
			util::print_time(item.name, item.time);
		} else {
			util::print_time(item.name, item.time, item.avg);
		}
	}
	
}

void read_input() {
	Timer timer;
	char* BUF = new char[int(1e9) + 5];
	util::print_progress(0, NUM_INPUTS, "progress");
	for (size_t i = 0; i < NUM_INPUTS; i++) {
		std::string file_name = "./input/in_";
		file_name += std::to_string(i);
		FILE* file = fopen(file_name.c_str(), "r");
		if (!file) {
			std::cerr << "\nerror opening file '" << file_name << "'" << std::endl;
			exit(1);
		}
		if (!fgets(BUF, int(1e9) + 5, file)) {
			std::cerr << "\nerror reading from file '" << file_name << "'" << std::endl;
			exit(1);
		}
		std::string s;
		for (int j = 0; BUF[j] != '\n' && BUF[j] != '\0'; j++) {
			if (BUF[j] == ' ') {
				input_long_double[i].push_back(std::stold(s));
				input_double[i].push_back(std::stod(s));
				s.clear();
			} else {
				s += BUF[j];
			}
		}
		if (!s.empty()) {
			input_long_double[i].push_back(std::stold(s));
			input_double[i].push_back(std::stod(s));
		}
		fclose(file);
		util::print_progress(i + 1, NUM_INPUTS, "progress");
	}
	delete[] (BUF);
	auto time_end = timer.split();
	util::print_time("reading input", time_end);
	summary_items.push_back(
	Summary_Item("reading input", time_end));
}

template <typename A>
void validate(const std::string& what,
const std::vector <std::vector <A>>& output,
const std::vector <std::vector <A>>& validation) {
	Timer timer;
	std::string success = "[successful]";
	timer.pause();
	util::print_progress(0, NUM_INPUTS, "progress");
	timer.resume();
	long long count_bad = 0;
	for (size_t i = 0; i < NUM_INPUTS; i++) {
		if (output[i].size() != validation[i].size()) {
			std::cout << "[validation failed (" << what << ")] test" << i << ": bad size (" <<
			output[i].size() << "/" << validation[i].size() << ")" << std::endl;
			success = "[unsuccessful]";
		} else {
			bool this_bad = false;
			for (size_t j = 0; j < output[i].size(); j++) {
				if (!util::compare(output[i][j], validation[i][j])) {
					if (!this_bad) {
						std::cout << "[validation failed (" << what << ")] test" << i << ", index " << j <<
						": " << output[i][j] << " | correct: " << validation[i][j] << std::endl;
						success = "[unsuccessful]";
					}
					this_bad = true;
					count_bad++;
					timer.pause();
					util::print_progress(i + 1, NUM_INPUTS, "progress",
					"(" + std::to_string(count_bad) + " wrong values");
					timer.resume();
				}
			}
		}
		timer.pause();
		if (count_bad) {
			util::print_progress(i + 1, NUM_INPUTS, "progress",
			"(" + std::to_string(count_bad) + " wrong values");
		} else {
			util::print_progress(i + 1, NUM_INPUTS, "progress");
		}
		timer.resume();
	}
	auto time_end = timer.split();
	util::print_time("validating output (" + what + ") " + success, time_end);
	summary_items.push_back(
	Summary_Item("validating output (" + what + ") " + success, time_end));
}

namespace run {
	
	void validator_implementation_FFT_double() {
		std::vector <long long> times(NUM_INPUTS);
		Timer timer;
		
		timer.pause();
		util::print_progress(0, NUM_INPUTS, "progress");
		timer.resume();
		for (size_t i = 0; i < NUM_INPUTS; i++) {
			Timer local_timer;
			output_double_correct[i] = VAL_IMPL::FFT_double(
			std::vector <std::complex <double>> (input_double[i].begin(), input_double[i].end()));
			times[i] = local_timer.split();
			timer.pause();
			util::print_progress(i + 1, NUM_INPUTS, "progress");
			timer.resume();
		}
		
		auto time_end = timer.split();
		util::print_time("validator_implementation/FFT (FFT_double)", time_end, util::get_avg(times));
		for (size_t i = 0; i < NUM_INPUTS; i++) {
			util::print_time("    [input " + std::to_string(i) + "]", times[i]);
		}
		summary_items.push_back(
		Summary_Item("validator_implementation/FFT (FFT_double)", time_end, util::get_avg(times)));
	}
	
	void validator_implementation_FFT_long_double() {
		std::vector <long long> times(NUM_INPUTS);
		Timer timer;
		
		timer.pause();
		util::print_progress(0, NUM_INPUTS, "progress");
		timer.resume();
		for (size_t i = 0; i < NUM_INPUTS; i++) {
			Timer local_timer;
			output_long_double_correct[i] = VAL_IMPL::FFT_long_double(
			std::vector <std::complex <long double>> (input_long_double[i].begin(), input_long_double[i].end()));
			times[i] = local_timer.split();
			timer.pause();
			util::print_progress(i + 1, NUM_INPUTS, "progress");
			timer.resume();
		}
		
		auto time_end = timer.split();
		util::print_time("validator_implementation/FFT (FFT_long_double)", time_end, util::get_avg(times));
		for (size_t i = 0; i < NUM_INPUTS; i++) {
			util::print_time("    [input " + std::to_string(i) + "]", times[i]);
		}
		summary_items.push_back(
		Summary_Item("validator_implementation/FFT (FFT_long_double)", time_end, util::get_avg(times)));
	}
	
	void variation_1_FFT_double() {
		std::vector <long long> times(NUM_INPUTS);
		Timer timer;
		
		timer.pause();
		util::print_progress(0, NUM_INPUTS, "progress");
		timer.resume();
		for (size_t i = 0; i < NUM_INPUTS; i++) {
			Timer local_timer;
			output_double_variation1[i] = VARIATIONS::FFT_v1_double(input_double[i]);
			times[i] = local_timer.split();
			timer.pause();
			util::print_progress(i + 1, NUM_INPUTS, "progress");
			timer.resume();
		}
		
		auto time_end = timer.split();
		util::print_time("variations/FFT (FFT_v1_double)", time_end, util::get_avg(times));
		for (size_t i = 0; i < NUM_INPUTS; i++) {
			util::print_time("    [input " + std::to_string(i) + "]", times[i]);
		}
		summary_items.push_back(
		Summary_Item("variations/FFT (FFT_v1_double)", time_end, util::get_avg(times)));
	}
	
	void variation_1_FFT_long_double() {
		std::vector <long long> times(NUM_INPUTS);
		Timer timer;
		
		timer.pause();
		util::print_progress(0, NUM_INPUTS, "progress");
		timer.resume();
		for (size_t i = 0; i < NUM_INPUTS; i++) {
			Timer local_timer;
			output_long_double_variation1[i] = VARIATIONS::FFT_v1_long_double(input_long_double[i]);
			times[i] = local_timer.split();
			timer.pause();
			util::print_progress(i + 1, NUM_INPUTS, "progress");
			timer.resume();
		}
		
		auto time_end = timer.split();
		util::print_time("variations/FFT (FFT_v1_long_double)", time_end, util::get_avg(times));
		for (size_t i = 0; i < NUM_INPUTS; i++) {
			util::print_time("    [input " + std::to_string(i) + "]", times[i]);
		}
		summary_items.push_back(
		Summary_Item("variations/FFT (FFT_v1_long_double)", time_end, util::get_avg(times)));
	}
	
} /// namespace run
