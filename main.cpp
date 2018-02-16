

#include <iostream>

#include "sbox.h"
#include "sboxRealBox.h"
#include "sboxIndexType.h"
#include "sboxIntBox.h"
#include "sboxParallel.h"
#include "sboxStructGrid.h"


#if 0

int main(int argc, char *argv[]) {

	MPI_Init(&argc, &argv);

	sbox::MpiComm comm(MPI_COMM_WORLD);

	int nproc = comm.size();
	int myproc = comm.rank();

	{
		comm.rootPrintf("nProc %d\n", nproc);
		comm.barrier();
		comm.syncPrintf("Proc %d/%d\n", myproc, nproc);
		comm.barrier();
	}

	sbox::StructGrid sgrid(comm);
	if (myproc == 0) {
		sgrid.setExtent({ -3,1 }, { -1,2 });
	}
	else if (myproc == 1) {
		sgrid.setExtent({ 0,1 }, { 2,4 });
	}

	sgrid.assemble();

	comm.syncCall([&]() {
		std::cout << "Proc " << myproc << std::endl;
		std::cout << sgrid.boxes() << std::endl;
		std::cout << sgrid.m_bound_box << std::endl;
		std::cout << sgrid.m_size_local << std::endl;
		std::cout << sgrid.m_size_local_with_ghost << std::endl;
		std::cout << sgrid.m_size_global << std::endl;

	});



	MPI_Finalize();

	return 0;
}

#endif



int main(int argc, char *argv[]) {

	{
		std::cout << sbox::RealBox::RealBox() << std::endl;

		std::cout << sbox::Box::UnitBox() << std::endl;

		std::cout << sbox::IndexType::FaceType(1) << std::endl;
	}


	return 0;
}




