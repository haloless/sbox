#include "sboxBoxArray.h"

#include <iostream>

BEGIN_SBOX_NS;


BoxArray::BoxArray()
{
}

BoxArray::~BoxArray()
{
}

Box BoxArray::calcBoundBox() const
{
	const size_t num_local_boxes = size();

	Box bound_box;
	if (num_local_boxes > 0) {
		IntVec imin = this->at(0).lo();
		IntVec imax = this->at(0).hi();

		for (int i = 1; i < num_local_boxes; i++) {
			for (int idim = 0; idim < SBOX_SPACEDIM; idim++) {
				imin[idim] = std::min(imin[idim], (*this)[i].lo()[idim]);
				imax[idim] = std::max(imax[idim], (*this)[i].hi()[idim]);
			}
		}

		bound_box = Box(imin, imax);
	}
	else {
		// set a invalid box
		bound_box.setInvalid();
	}

	return bound_box;
}


std::ostream& operator<<(std::ostream& os, const BoxArray &ba) {
	os << "BoxArray[" << ba.size() << "] {" << std::endl;
	for (const Box &b : ba) {
		os << b << std::endl;
	}
	os << "}";
	return os;
}


END_SBOX_NS;

