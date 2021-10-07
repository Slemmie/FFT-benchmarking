#pragma once

#include <vector>
#include <cassert>
#include <type_traits>

// template paramter: data type of input (i.e. int/double/etc.)
template <typename DATA_TYPE> class Input_batch {
	
public:
	
	Input_batch() :
	m_id(m_sBATCH_ID_COUNT)
	{
		
	}
	
	Input_batch(const size_t _file_count, const char* _filespath, const char* _file_format = "in_") :
	m_id(m_sBATCH_ID_COUNT)
	{
		read_input(_file_count, _filepath, _file_format);
	}
	
	void read_input(const size_t file_count, const char* filespath, const char* file_format = "in_") {
		for (size_t i = 0; i < file_count; i++) {
			FILE* file = fopen(file_format + std::itoa(i), "rb");
			assert(file);
			fseek(file, 0, SEEK_END);
			m_input.push_back(std::vector <DATA_TYPE> (ftell(file)));
			rewind(file);
			fread(m_input.back().data(), sizeof(DATA_TYPE), m_input.back().size(), file);
			fclose(file);
		}
	}
	
	inline size_t size() const {
		return m_input.size();
	}
	
	inline size_t id() const {
		return m_id;
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
	
	// single counter for assigning IDs to input batches
	static size_t m_sBATCH_ID_COUNT = 0;
	
};

class Input_container {
	
public:
	
	Input_container() :
	m_size(0)
	{
		
	}
	
	// push existing input batch
	template <typename DATA_TYPE> void push_batch(const Input_batch <DATA_TYPE>& batch) {
		m_size++;
		if (std::is_same <DATA_TYPE, int>::value) {
			m_ib_int.push_back(batch);
		} else if (std::is_same <DATA_TYPE, long long>::value) {
			m_ib_longlong.push_back(batch);
		} else if (std::is_same <DATA_TYPE, double>::value) {
			m_ib_double.push_back(batch);
		} else if (std::is_same <DATA_TYPE, long double>::value) {
			m_ib_longdouble.push_back(batch);
		}
	}
	
	
	// create, then push, new input batch with given parameters
	template <typename DATA_TYPE> void push_batch(const size_t _file_count,
	const char* _filespath, const char* _file_format = "in_") {
		m_size++;
		if (std::is_same <DATA_TYPE, int>::value) {
			m_ib_int.push_back(Input_batch <int> (_file_count, _filespath, _file_format));
		} else if (std::is_same <DATA_TYPE, long long>::value) {
			m_ib_longlong.push_back(Input_batch <long long> (_file_count, _filespath, _file_format));
		} else if (std::is_same <DATA_TYPE, double>::value) {
			m_ib_double.push_back(Input_batch <double> (_file_count, _filespath, _file_format));
		} else if (std::is_same <DATA_TYPE, long double>::value) {
			m_ib_longdouble.push_back(Input_batch <long double> (_file_count, _filespath, _file_format));
		}
	}
	
	template <typename DATA_TYPE>
	inline const std::vector <Input_batch <DATA_TYPE>>& get_batch(const size_t index) const {
		if (std::is_same <DATA_TYPE, int>::value) {
			assert(index >= 0 && index < m_ib_int.size());
			return m_ib_int[index];
		} else if (std::is_same <DATA_TYPE, long long>::value) {
			assert(index >= 0 && index < m_ib_longlong.size());
			return m_ib_longlong[index];
		} else if (std::is_same <DATA_TYPE, double>::value) {
			assert(index >= 0 && index < m_ib_double.size());
			return m_ib_double[index];
		} else if (std::is_same <DATA_TYPE, long double>::value) {
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
		} else if (std::is_same <DATA_TYPE, long long>::value) {
			assert(index >= 0 && index < m_ib_longlong.size());
			return m_ib_longlong[index];
		} else if (std::is_same <DATA_TYPE, double>::value) {
			assert(index >= 0 && index < m_ib_double.size());
			return m_ib_double[index];
		} else if (std::is_same <DATA_TYPE, long double>::value) {
			assert(index >= 0 && index < m_ib_longdouble.size());
			return m_ib_longdouble[index];
		}
		return { };
	}
	
	inline size_t size() const {
		return m_size;
	}
	
private:
	
	size_t m_size;
	
	// container of input for each supported type
	std::vector <Input_batch <int>> m_ib_int;
	std::vector <Input_batch <long long>> m_ib_longlong;
	std::vector <Input_batch <double>> m_ib_double;
	std::vector <Input_batch <long double>> m_ib_longdouble;
	
};
