#pragma once

#include <program_wrappers/program.h>
#include <program_wrappers/input_container.h>

#include <util/util.h>

#include <string>
#include <vector>
#include <cassert>

// first template paramter: data type of input (i.e. int/double/etc.)
// second template parameter: data type of return values (must be floating point types such as double)
template <typename DATA_TYPE, typename RETURN_DATA_TYPE> class Program_pool {
	
public:
	
	Program_pool() :
	m_id(m_sPOOL_ID_COUNT++)
	{
		
	}
	
	// max_batch is number of batches, starting from 0, to run with
	// runs each individual input through all programs before advancing
	void run_tests(const Input_container& input_container, const size_t max_batch = 1) {
		assert(max_batch <= input_container.size());
		m_recent_outputs.clear();
		m_recent_outputs.resize(std::min(input_container.size(), max_batch), 
		std::vector <RETURN_DATA_TYPE> (size()));
		std::string to_log = "program pool #" + std::to_string(id()) + ":\n";
		to_log += "batch (ID " + std::to_string(input_container.id()) + ")\n";
		for (size_t i = 0; i < std::min(input_container.size(), max_batch); i++) {
			static long long current_time;
			to_log += "  input #" + std::to_string(i) + "/" +
			std::to_string(input_container.size()) + "\n";
			for (size_t j = 0; j < size(); j++) {
				m_recent_outputs.[j] = m_programs[j].execute(input_container[i], current_time);
				to_log += "    #" + std::to_string(j) + ": " + util::time_format(current_time) << "\n";
			}
		}
		util::push_log(to_log);
	}
	
	inline void push_program(const Program <DATA_TYPE, RETURN_DATA_TYPE>& program) {
		m_programs.push_back(program);
	}
	
	inline void clear_programs() {
		m_programs.clear();
	}
	
	inline size_t size() const {
		return m_programs.size();
	}
	
	inline size_t id() const {
		return m_id;
	}
	
	inline const Program <DATA_TYPE, RETURN_DATA_TYPE>& operator [] (const size_t index) const {
		assert(index >= 0 && index < m_programs.size());
		return m_programs[index];
	}
	
	inline Program <DATA_TYPE, RETURN_DATA_TYPE>& operator [] (const size_t index) {
		assert(index >= 0 && index < m_programs.size());
		return m_programs[index];
	}
	
private:
	
	size_t m_id;
	
	std::vector <Program <DATA_TYPE, RETURN_DATA_TYPE>> m_programs;
	// holds outputs from previous call to run_tests()
	std::vector <std::vector <RETURN_DATA_TYPE>> m_recent_outputs;
	
	// single counter for assigning IDs to program pools
	static size_t m_sPOOL_ID_COUNT = 0;
	
};
