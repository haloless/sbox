#pragma once

#include "sbox.h"

#include <cstdarg>


#if SBOX_USE_MPI

#include <mpi.h>


BEGIN_SBOX_NS;

//
// fwd decl.
//
class Box;


class MpiSession
{
	MPI_Comm comm_world;
	int world_size;
	int world_rank;

public:

};

////////////////////////////////////////////////////////////////////////////////

class MpiComm
{
	MPI_Comm comm;

public:

	MpiComm() : comm(MPI_COMM_WORLD) {}

	MpiComm(MPI_Comm c) : comm(c) {}

	// conversion
	operator MPI_Comm () const { return comm; }

	//
	int size() const { int size; MPI_Comm_size(comm, &size); return size; }

	//
	int rank() const { int rank; MPI_Comm_rank(comm, &rank); return rank; }

	// 
	bool isRoot() const { return rank() == 0; }


	int abort(int code) { return MPI_Abort(comm, code); }

	////////////////////////////////////////////////////////////
public:

	//
	void barrier() const { MPI_Barrier(comm); }


	////////////////////////////////////////////////////////////
public:

	void send(const void *buf, int count, MPI_Datatype datatype, int dest, int tag) const {
		MPI_Send(buf, count, MPI_INT, dest, tag, comm);
	}

	//void recv() const {
	//	MPI_Recv(buf, count, datatype, source, tag, comm, &status);
	//}


	////////////////////////////////////////////////////////////
public:

	// All_Reduce to obtain bound box on all procs
	void allReduceBoundBox(Box &b) const;


	////////////////////////////////////////////////////////////
public:

	// 
	// The NOTIFY-WAIT pair is used to implement sequential operations.
	//
	void notify(int dst) const;

	void wait(int src) const;

	void notifyNext() const;
	void waitPrev() const;

	void rootPrintf(const char fmt[], ...) const;

	void syncPrintf(const char fmt[], ...) const;


	template<typename F> 
	void syncCall(F func) const {
		int myproc = rank();
		int nproc = size();

		if (myproc > 0) { wait(myproc - 1); }

		func(); // callback

		if (myproc < nproc - 1) {
			notify(myproc + 1);
		}
	}

};






////////////////////////////////////////////////////////////////////////////////


END_SBOX_NS;


#endif

