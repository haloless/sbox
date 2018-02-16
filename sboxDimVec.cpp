#include "sboxDimVec.h"

#include <iostream>

BEGIN_SBOX_NS;


const IntVec& IntVec::ZeroVec()
{
	static IntVec instance(0, 0, 0);
	return instance;
}

const IntVec& IntVec::UnitVec()
{
	static IntVec instance(1, 1, 1);
	return instance;
}

const IntVec & IntVec::BaseVec(int dir)
{
	static IntVec instance[SBOX_SPACEDIM] = {
		IntVec(1, 0, 0),
		IntVec(0, 1, 0),
		IntVec(0, 0, 1),
	};

	return instance[dir];
}




std::ostream& operator<<(std::ostream &os, const IntVec &v) {
	os << "IntVec{";
	for (int i = 0; i < v.size(); i++) {
		os << v[i] << ",";
	}
	os << "}";
	return os;
}



END_SBOX_NS;

