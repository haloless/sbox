
#include "sboxParallel.h"
#include "sboxIntBox.h"


#if SBOX_USE_MPI

BEGIN_SBOX_NS;



void MpiComm::allReduceBoundBox(Box & b) const
{
	const int ndim = SBOX_SPACEDIM;

	// communicate bound box
	int sendbuf[ndim * 2];
	for (int d = 0; d < ndim; d++) {
		sendbuf[d] = b.lo(d);
		sendbuf[d + ndim] = -b.hi(d);
	}

	int recvbuf[SBOX_SPACEDIM * 2];
	MPI_Allreduce(sendbuf, recvbuf, _countof(sendbuf), MPI_INT, MPI_MIN, comm);

	for (int d = 0; d < SBOX_SPACEDIM; d++) {
		b.lo()[d] = recvbuf[d];
		b.hi()[d] = -recvbuf[d + SBOX_SPACEDIM];
	}
}

// 
// The NOTIFY-WAIT pair is used to implement sequential operations.
//
void MpiComm::notify(int dst) const {
	int msg = 0;
	MPI_Send(&msg, 1, MPI_INT, dst, 0, comm);
}

void MpiComm::wait(int src) const {
	int buf = 0;
	MPI_Recv(&buf, 1, MPI_INT, src, 0, comm, MPI_STATUS_IGNORE);
}

void MpiComm::notifyNext() const { 
	int myproc = rank();
	int nproc = size();
	if (myproc < nproc - 1) notify(myproc + 1);
}

void MpiComm::waitPrev() const { 
	int myproc = rank();
	//int nproc = size(); 
	if (myproc > 0) wait(myproc - 1);
}

void MpiComm::rootPrintf(const char fmt[], ...) const {
	if (rank() == 0) {
		va_list ap;
		va_start(ap, fmt);

		vprintf(fmt, ap);
		fflush(stdout);

		va_end(ap);
	}
}

void MpiComm::syncPrintf(const char fmt[], ...) const {

	int myproc = rank();
	int nproc = size();

	if (myproc > 0) {
		wait(myproc - 1);
	}

	va_list ap;
	va_start(ap, fmt);

	vprintf(fmt, ap);
	fflush(stdout);

	va_end(ap);

	if (myproc < nproc - 1) {
		notify(myproc + 1);
	}
}





END_SBOX_NS;


#endif


