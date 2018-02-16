#include "sboxIntBox.h"
#include "sboxParallel.h"

#include <iostream>

BEGIN_SBOX_NS;

Box::Box()
	: m_lo(IntVec::UnitVec())
	, m_hi(IntVec::ZeroVec())
{
}




////////////////////////////////////////////////////////////////////////////////

int Box::volume() const {
	int vol = 1;
	for (int idim = 0; idim < dimension(); idim++) {
		vol *= length(idim);
	}
	return vol;
}

int Box::operator[](Orientation face) const
{
	int dir = face.dir();
	return face.isLo() ? m_lo[dir] : m_hi[dir];
}

bool Box::isSameSize(const Box & rhs) const
{
	return length(0) == rhs.length(0)
		&& length(1) == rhs.length(1)
		&& length(2) == rhs.length(2);
}


////////////////////////////////////////////////////////////////////////////////


const Box & Box::UnitBox()
{
	static const Box inst(IntVec::ZeroVec(), IntVec::UnitVec());
	return inst;
}



//void Box::reduceAllMaxBox()
//{
//	// communicate bound box
//	int sendbuf[SBOX_SPACEDIM * 2];
//	for (int d = 0; d < SBOX_SPACEDIM; d++) {
//		sendbuf[d] = bound_box.lo()[d];
//		sendbuf[d + SBOX_SPACEDIM] = -bound_box.hi()[d];
//	}
//
//	int recvbuf[SBOX_SPACEDIM * 2];
//	MPI_Allreduce(sendbuf, recvbuf, _countof(sendbuf), MPI_INT, MPI_MIN, m_comm);
//
//	for (int d = 0; d < SBOX_SPACEDIM; d++) {
//		bound_box.lo()[d] = recvbuf[d];
//		bound_box.hi()[d] = -recvbuf[d + SBOX_SPACEDIM];
//	}
//}


std::ostream& operator<<(std::ostream &os, const Box &b) {
	os << "Box {" << "lo=" << b.lo() << ", hi=" << b.hi() << "}";
	return os;
}


END_SBOX_NS;

