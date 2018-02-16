#pragma once

#include "sbox.h"

#include <iosfwd>

BEGIN_SBOX_NS;


class RealBox
{
protected:
	double xlo[SBOX_SPACEDIM];
	double xhi[SBOX_SPACEDIM];


};

std::ostream& operator<<(std::ostream &os, const RealBox &rbox);
std::istream& operator>>(std::istream &is, RealBox &rbox);


END_SBOX_NS;



