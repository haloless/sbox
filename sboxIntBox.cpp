#include "sboxIntBox.h"
#include "sboxParallel.h"


BEGIN_SBOX_NS;

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




END_SBOX_NS;
