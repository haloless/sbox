#pragma once

#include "sbox.h"

#include <iosfwd>



BEGIN_SBOX_NS;




template<typename T>
class SDimVec
{
	T m_vec[SBOX_SPACEDIM];


};


class IntVec
{
	int m_vec[SBOX_SPACEDIM];

public:

	IntVec() {
		fill(0);
	}

	IntVec(int i, int j, int k) {
		m_vec[0] = i;
		m_vec[1] = j;
		m_vec[2] = k;
	}

	IntVec(std::initializer_list<int> l) {
		setVec(l.begin());
	}

	//IntVec(const IntVec &rhs) = default;

	//IntVec(IntVec &&) = delete;


	////////////////////////////////////////

	constexpr size_t size() const { return _countof(m_vec); }

	int* begin() { return m_vec; }
	int* end() { return m_vec + size(); }

	constexpr const int* cbegin() const { return m_vec; }
	constexpr const int* cend() const { return m_vec + size(); }


	void fill(int v) { std::fill(begin(), end(), v); }

	void setVec(const int *v) { std::copy(v, v + size(), m_vec); }

	int operator[](int i) const { return m_vec[i]; }
	int& operator[](int i) { return m_vec[i]; }

	void incr(int ng) {
		for (int i = 0; i < size(); i++) m_vec[i] += ng;
	}




public:

	static const IntVec& ZeroVec();
	static const IntVec& UnitVec();
	static const IntVec& BaseVec(int dir);

};

std::ostream& operator<<(std::ostream &os, const IntVec &v);








END_SBOX_NS;

