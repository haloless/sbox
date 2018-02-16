#pragma once

#include "sbox.h"
#include "sboxDimVec.h"
#include "sboxOrient.h"

#include <iosfwd>


BEGIN_SBOX_NS;




class Box
{
	// TODO MPI

protected:
	IntVec m_lo;
	IntVec m_hi;

public:

	// default construct invalid 
	Box();

	//
	Box(const IntVec &lo, const IntVec &hi)
		: m_lo(lo), m_hi(hi)
	{}



	const IntVec& lo() const { return m_lo; }
	const IntVec& hi() const { return m_hi; }

	IntVec& lo() { return m_lo; }
	IntVec& hi() { return m_hi; }

	int lo(int idim) const { return m_lo[idim]; }
	int hi(int idim) const { return m_hi[idim]; }

	constexpr int dimension() const { return SBOX_SPACEDIM; }

	int length(int idim) const { return m_hi[idim] - m_lo[idim] + 1; }

	int volume() const;

	int operator[](Orientation face) const;

	bool isSameSize(const Box &rhs) const;


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

	static const Box& UnitBox();


};

std::ostream& operator<<(std::ostream &os, const Box &b);


END_SBOX_NS;


