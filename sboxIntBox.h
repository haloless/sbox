#pragma once

#include "sbox.h"

#include <iostream>


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



};

inline std::ostream& operator<<(std::ostream &os, const IntVec &v) {
	os << "IntVec{";
	for (int i = 0; i < v.size(); i++) {
		os << v[i] << ",";
	}
	os << "}";
	return os;
}



struct IndexType
{
protected:
	int m_type;

public:
	enum {
		CELL = 0,
		NODE = 1,
	};

	// default
	IndexType() : m_type(0) {}


};

class Box
{
	// TODO MPI

protected:
	IntVec m_lo;
	IntVec m_hi;

public:

	// 
	Box() {}

	//
	Box(const IntVec &lo, const IntVec &hi)
		: m_lo(lo), m_hi(hi)
	{}

	//
	//Box(const Box &rhs) = default;


	const IntVec& lo() const { return m_lo; }
	const IntVec& hi() const { return m_hi; }

	IntVec& lo() { return m_lo; }
	IntVec& hi() { return m_hi; }

	int lo(int idim) const { return m_lo[idim]; }
	int hi(int idim) const { return m_hi[idim]; }

	constexpr int dimension() const { return SBOX_SPACEDIM; }

	int length(int idim) const { return m_hi[idim] - m_lo[idim] + 1; }

	int volume() const {
		int vol = 1;
		for (int idim = 0; idim < dimension(); idim++) {
			vol *= length(idim);
		}
		return vol;
	}

	// grow in all directions by NG
	void growBy(int ng) {
		m_lo.incr(-ng);
		m_hi.incr(ng);
	}

	// set to a invalid one
	void setInvalid() {
		m_lo.fill(99999);
		m_hi.fill(-99999);
	}


	////////////////////////////////////////////////////////////
public:



};

inline std::ostream& operator<<(std::ostream &os, const Box &b) {
	os << "Box {" << "lo=" << b.lo() << ", hi=" << b.hi() << "}";
	return os;
}


END_SBOX_NS;


