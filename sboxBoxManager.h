#pragma once

#include "sbox.h"
#include "sboxParallel.h"
#include "sboxIntBox.h"
//#include "sboxBoxArray.h"

#if SBOX_USE_MPI

BEGIN_SBOX_NS;


class BoxManager
{
public:
	typedef std::shared_ptr<BoxManager> Ptr;

	// 
	struct Entry
	{
		IntVec imin, imax;

		int proc, id;

		int nghost;

		int position;

		BoxManager *owner;
	};

protected:

	MpiComm m_comm;

	int m_is_assembled;

	// 
	Array<Entry> m_entries;

	//
	Box m_bound_box;

	int m_nghost;


	//
	Array<int> m_procs_sort;
	Array<int> m_ids_sort;

	Array<int> m_my_ids;
	Array<Entry*> m_my_entries;


	// next unique id
	int m_next_id;

public:

	BoxManager(MpiComm comm, const Box &bound_box, int num_entry_guess = 32);


	////////////////////////////////////////////////////////////
public:

	void addEntry(const Box &box, int proc_id, int box_id);



	////////////////////////////////////////////////////////////
public:

	static Ptr New(const MpiComm &comm, const Box &bound_box);

};



END_SBOX_NS;

#endif


