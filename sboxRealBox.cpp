#include "sboxRealBox.h"

#include <iostream>

BEGIN_SBOX_NS;


RealBox::RealBox()
{
	std::fill(m_lo, m_lo + SBOX_SPACEDIM, +1);
	std::fill(m_hi, m_hi + SBOX_SPACEDIM, -1);
}

RealBox::RealBox(const double xlo[SBOX_SPACEDIM], const double xhi[SBOX_SPACEDIM])
{
	setLo(xlo);
	setHi(xhi);
}

RealBox::RealBox(double xlo, double ylo, double zlo, double xhi, double yhi, double zhi)
{
	m_lo[0] = xlo;
	m_lo[1] = ylo;
	m_lo[2] = zlo;
	m_hi[0] = xhi;
	m_hi[1] = yhi;
	m_hi[2] = zhi;

}

double RealBox::volume() const
{
	double vol = 1;
	for (int i = 0; i < SBOX_SPACEDIM; i++) {
		vol *= len(i);
	}
	return vol;
}

void RealBox::setLo(const double xlo[SBOX_SPACEDIM])
{
	std::copy(xlo, xlo + SBOX_SPACEDIM, m_lo);
}

void RealBox::setHi(const double xhi[SBOX_SPACEDIM])
{
	std::copy(xhi, xhi + SBOX_SPACEDIM, m_hi);
}

bool RealBox::ok() const
{
	return len(0) > 0 && len(1) > 0 && len(2) > 0;
}



std::ostream & operator<<(std::ostream & os, const RealBox & rbox)
{
	os << "RealBox{lo=(";
	for (int dir = 0; dir < SBOX_SPACEDIM; dir++) {
		os << rbox.lo(dir) << ",";
	}
	os << "),hi=(";
	for (int dir = 0; dir < SBOX_SPACEDIM; dir++) {
		os << rbox.hi(dir) << ",";
	}
	os << ")}";

	return os;
}


END_SBOX_NS;

