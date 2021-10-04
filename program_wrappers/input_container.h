#pragma once

#include <vector>
#include <cassert>
#include <type_traits>

// template paramter: data type of input (i.e. int/double/etc.)
template <typename DATA_TYPE> class Input_batch {
	
public:
	
	Input_batch();
	Input_batch(const size_t _file_count, const char* _filespath, const char* _file_format = "in_");
	
	void read_input(const size_t file_count, const char* filespath, const char* file_format = "in_");
	
	inline size_t size() const {
		return m_input.size();
	}
	
	inline const std::vector <DATA_TYPE>& operator [] (const size_t index) const {
		assert(index >= 0 && index < this->size());
		return m_input[index];
	}
	
	inline std::vector <DATA_TYPE>& operator [] (const size_t index) {
		assert(index >= 0 && index < this->size());
		return m_input[index];
	}
	
private:
	
	size_t m_id;
	
	std::vector <std::vector <DATA_TYPE>> m_input;
	
};

class Input_container {
	
public:
	
	// push existing input batch
	template <typename DATA_TYPE> push_batch(const Input_batch <DATA_TYPE>& batch);
	// create, then push, new input batch with given parameters
	template <typename DATA_TYPE> push_batch(const size_t _file_count,
	const char* filespath, const char* file_format = "in_");
	
	template <typename DATA_TYPE>
	inline const std::vector <Input_batch <DATA_TYPE>>& get_batch(const size_t index) const {
		if (std::is_same <DATA_TYPE, int>::value) {
			assert(index >= 0 && index < m_ib_int.size());
			return m_ib_int[index];
		}
		if (std::is_same <DATA_TYPE, long long>::value) {
			assert(index >= 0 && index < m_ib_longlong.size());
			return m_ib_longlong[index];
		}
		if (std::is_same <DATA_TYPE, double>::value) {
			assert(index >= 0 && index < m_ib_double.size());
			return m_ib_double[index];
		}
		if (std::is_same <DATA_TYPE, long double>::value) {
			assert(index >= 0 && index < m_ib_longdouble.size());
			return m_ib_longdouble[index];
		}
		return { };
	}
	
	template <typename DATA_TYPE>
	inline std::vector <Input_batch <DATA_TYPE>>& get_batch(const size_t index) {
		if (std::is_same <DATA_TYPE, int>::value) {
			assert(index >= 0 && index < m_ib_int.size());
			return m_ib_int[index];
		}
		if (std::is_same <DATA_TYPE, long long>::value) {
			assert(index >= 0 && index < m_ib_longlong.size());
			return m_ib_longlong[index];
		}
		if (std::is_same <DATA_TYPE, double>::value) {
			assert(index >= 0 && index < m_ib_double.size());
			return m_ib_double[index];
		}
		if (std::is_same <DATA_TYPE, long double>::value) {
			assert(index >= 0 && index < m_ib_longdouble.size());
			return m_ib_longdouble[index];
		}
		return { };
	}
	
private:
	
	// container of input for each supported type
	std::vector <Input_batch <int>> m_ib_int;
	std::vector <Input_batch <long long>> m_ib_longlong;
	std::vector <Input_batch <double>> m_ib_double;
	std::vector <Input_batch <long double>> m_ib_longdouble;
	
};
