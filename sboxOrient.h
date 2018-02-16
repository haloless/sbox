#pragma once

#include "sbox.h"

BEGIN_SBOX_NS;


class Orientation
{
protected:
	int m_val;

public:
	enum Side {
		Low = 0, 
		High,
	};

	Orientation() : m_val(-1) {}

	Orientation(int dir, Side side) 
		: m_val(encode(dir,side))
	{}


	// cast to int
	operator int() const { return m_val; }

	int dir() const { return m_val % SBOX_SPACEDIM; }
	int side() const { return m_val / SBOX_SPACEDIM; }

	bool isLo() const { return m_val < SBOX_SPACEDIM; }
	bool isHi() const { return m_val >= SBOX_SPACEDIM; }

public:

	inline static int encode(int dir, Side side) {
		return dir + SBOX_SPACEDIM*side;
	}

};






END_SBOX_NS;


