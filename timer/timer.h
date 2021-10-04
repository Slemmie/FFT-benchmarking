#pragma once

#include <chrono>
#include <iostream>
#include <vector>

class Timer {
	
public:
	
	Timer() :
	m_pause_add(0)
	{
		m_start = std::chrono::high_resolution_clock::now();
	}
	
	inline long long split() {
		std::chrono::time_point <std::chrono::high_resolution_clock> now =
		std::chrono::high_resolution_clock::now();
		
		long long duration =
		std::chrono::time_point_cast <std::chrono::microseconds> (now).time_since_epoch().count() -
		std::chrono::time_point_cast <std::chrono::microseconds> (m_start).time_since_epoch().count();
		
		duration -= m_pause_add;
		
		m_splits.push_back(duration);
		
		return duration;
	}
	
	inline void pause() {
		m_pause_moment = std::chrono::high_resolution_clock::now();
	}
	
	inline void resume() {
		std::chrono::time_point <std::chrono::high_resolution_clock> now =
		std::chrono::high_resolution_clock::now();
		
		m_pause_add +=
		std::chrono::time_point_cast <std::chrono::microseconds> (now).time_since_epoch().count() -
		std::chrono::time_point_cast <std::chrono::microseconds> (m_pause_moment).time_since_epoch().count();
	}
	
	inline std::ostream& operator << (std::ostream& stream) {
		long long put = split();
		stream << put;
		return stream;
	}
	
	inline long long operator [] (const size_t ind) const {
		return m_splits[ind];
	}
	
	inline size_t size() const {
		return m_splits.size();
	}
	
	inline long long prev_split() const {
		return m_splits.back();
	}
	
private:
	
	std::chrono::time_point <std::chrono::high_resolution_clock> m_start;
	long long m_pause_add;
	std::chrono::time_point <std::chrono::high_resolution_clock> m_pause_moment;
	
	std::vector <long long> m_splits;
	
};
