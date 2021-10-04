#include <timer/timer.h>
#include <util/util.h>

#include <iostream>
#include <random>
#include <string>

constexpr int TOTAL = 10;
constexpr int LEN = 1 << 20;
//constexpr int LEN = 1 << 5;

std::random_device device;
std::mt19937 gen(device());
std::uniform_real_distribution <double> dis_r(-1e9, 1e9);
std::uniform_int_distribution <int> dis_i((int)1e9, (int)1e9);

int main() {
	
	Timer timer;
	timer.pause();
	util::print_progress(0, TOTAL, "progress");
	timer.resume();
	for (int i = 0; i < TOTAL; i++) {
		std::string file_name = "./input/";
		file_name += "in_" + std::to_string(i);
		FILE* file = fopen(file_name.c_str(), "w");
		if (!file) {
			std::cerr << "error opening file '" << file_name << "'" << std::endl;
			return 1;
		}
		for (int j = 0; j < LEN; j++) {
			fprintf(file, "%f", dis_r(gen));
			if (j + 1 == LEN) {
				fprintf(file, "\n");
			} else {
				fprintf(file, " ");
			}
		}
		fclose(file);
		timer.pause();
		util::print_progress(i + 1, TOTAL, "progress");
		timer.resume();
	}
	auto time_end = timer.split();
	util::print_time("generating output", time_end);
	
}
