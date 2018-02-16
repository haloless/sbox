#pragma once

#include "sbox.h"

#include <iosfwd>

BEGIN_SBOX_NS;


class RealBox
{
protected:
	double m_lo[SBOX_SPACEDIM];
	double m_hi[SBOX_SPACEDIM];

public:
	
	// default construct invalid box
	RealBox();
	
	// 
	RealBox(const double xlo[SBOX_SPACEDIM], const double xhi[SBOX_SPACEDIM]);
	
	RealBox(double xlo, double ylo, double zlo, double xhi, double yhi, double zhi);

	const double* lo() const { return m_lo; }
	const double* hi() const { return m_hi; }
	double* lo() { return m_lo; }
	double* hi() { return m_hi; }
	double lo(int dir) const { return m_lo[dir]; }
	double hi(int dir) const { return m_hi[dir]; }

	double len(int dir) const { return m_hi[dir] - m_lo[dir]; }
	
	double volume() const;

	void setLo(const double xlo[SBOX_SPACEDIM]);
	void setHi(const double xhi[SBOX_SPACEDIM]);

	bool ok() const;

};

std::ostream& operator<<(std::ostream &os, const RealBox &rbox);
//std::istream& operator>>(std::istream &is, RealBox &rbox);


END_SBOX_NS;



