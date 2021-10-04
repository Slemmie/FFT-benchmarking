#pragam once

#include <program_wrappers/program.h>
#include <program_wrappers/input_container.h>

#include <vector>
#include <cassert>

// first template paramter: data type of input (i.e. int/double/etc.)
// second template parameter: data type of return values (must be floating point types such as double)
template <typename DATA_TYPE, typename RETURN_DATA_TYPE> class Program_pool {
	
public:
	
	// max_batch is number of batches, starting from 0, to run with
	// runs each individual input through all programs before advancing
	void run_tests(const Input_container& input_container, const size_t max_batch = 1);
	
	inline void push_program(const Program <DATA_TYPE, RETURN_DATA_TYPE>& program) {
		m_programs.push_back(program);
	}
	
	inline void clear_programs() {
		m_programs.clear();
	}
	
	inline size_t size() const {
		return m_programs.size();
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
	
	std::vector <Program <DATA_TYPE, RETURN_DATA_TYPE>> m_programs;
	
};
