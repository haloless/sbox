#pragma once

#include "sbox.h"
#include "sboxParallel.h"
#include "sboxIntBox.h"
#include "sboxBoxArray.h"
#include "sboxBoxManager.h"

#include <iostream>

BEGIN_SBOX_NS;







class Periodicity
{

};


//
// Structured, cell-centered grid
//
class StructGrid
{
public:
	typedef std::shared_ptr<StructGrid> Ptr;


//protected:

	MpiComm m_comm;

	const int m_dim; // grid dimension

	BoxArray::Ptr m_boxes;

	Array<int> m_ids; // global ids of boxes

	IntVec m_max_dist; // 

	Box m_bound_box;

	int m_size_local;
	int m_size_global;

	//int m_periodic[SBOX_SPACEDIM];
	//int m_pshifts[SBOX_SPACEDIM];
	IntVec m_periodic;
	IntVec m_pshifts;
	int m_num_periods;


	//
	int m_size_local_with_ghost;
	int m_num_ghost;

	// TODO box manager
	BoxManager::Ptr m_boxman;

public:

	StructGrid(MpiComm comm)
		: m_comm(comm), m_dim(SBOX_SPACEDIM)
	{
		// 
		m_boxes = std::make_shared<BoxArray>();

		// ???
		m_max_dist.fill(8);

		// 
		m_size_local = 0;
		m_size_global = 0;
		
		// periodicity
		m_periodic.fill(0);
		m_num_periods = 1;
		m_pshifts.fill(0);

		// ghost, default with one ghost layer
		m_size_local_with_ghost = 0;
		m_num_ghost = 1;
	}

	virtual ~StructGrid()
	{
		// nothing
	}

	// disable copy
	StructGrid(const StructGrid&) = delete;
	StructGrid(const StructGrid&&) = delete;
	StructGrid& operator=(const StructGrid&) = delete;


	////////////////////////////////////////////////////////////
	const BoxArray& boxes() const { return *m_boxes; }



	////////////////////////////////////////////////////////////

	void setExtent(const IntVec &ilo, const IntVec &ihi) {
		Box box(ilo, ihi);
		m_boxes->appendBox(box);
	}


	void assemble() {
		
		MpiComm comm = m_comm;
		const int nproc = comm.size();
		const int myproc = comm.rank();

		const BoxArray& local_boxes = *m_boxes;
		const size_t num_local_boxes = local_boxes.size();

		//
		// reset local ids
		//
		m_ids.resize(num_local_boxes);
		for (int i = 0; i < num_local_boxes; i++) {
			m_ids[i] = i;
		}

		//
		// TODO periodic
		//

		//
		// calc local size with ghost
		//
		int size = 0;
		int ghost_size = 0;

		for (int i = 0; i < num_local_boxes; i++) {
			// valid box
			const Box &box = local_boxes[i];
			size += box.volume();

			// ghost box
			Box ghostbox = box;
			ghostbox.growBy(m_num_ghost);
			ghost_size += ghostbox.volume();
		}

		m_size_local = size;
		m_size_local_with_ghost = ghost_size;

		//
		// init box manager
		//
		int global_size = 0;
		if (!m_boxman) {
			// reduce global size (no ghost)
			MPI_Allreduce(&size, &global_size, 1, MPI_INT, MPI_SUM, comm);
			m_size_global = global_size;

			// bound box
			Box bound_box = local_boxes.calcBoundBox();

			// communicate bound box
			comm.allReduceBoundBox(bound_box);

			// save global bound box
			m_bound_box = bound_box;

			// create box manager
			m_boxman = std::make_shared<BoxManager>(comm, bound_box);

			// populate the manager
			// local boxes + gather neighbor info.
			for (int i = 0; i < num_local_boxes; i++) {
				// the local box
				const Box &box = local_boxes[i];
				// add entry
				m_boxman->addEntry(box, myproc, i);

				// TODO`
			}

		}
		else {
			fprintf(stderr, "How get here?\n");
			MPI_Abort(m_comm, 1);
		}

	}
	



};




END_SBOX_NS;


