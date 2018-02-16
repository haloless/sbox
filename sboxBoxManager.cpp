#include "sboxBoxManager.h"

#if SBOX_USE_MPI

BEGIN_SBOX_NS;

BoxManager::BoxManager(MpiComm comm, const Box & bound_box, int num_entry_guess)
	: m_comm(comm), m_bound_box(bound_box)
{
	// not assembled yet
	m_is_assembled = 0;

	m_entries.reserve(num_entry_guess);

	// 
	m_nghost = 0;


	// 
	m_next_id = 0;

	// TODO
}

void BoxManager::addEntry(const Box & box, int proc_id, int box_id)
{
	if (m_is_assembled) {
		fprintf(stderr, "Already assembled\n");
		m_comm.abort(1);
	}

	if (box.volume() > 0) {
		const int myproc = m_comm.rank();

		// add new entry
		m_entries.push_back(Entry());

		BoxManager::Entry &ent = m_entries.back();
		{
			ent.imin = box.lo();
			ent.imax = box.hi();
			ent.proc = proc_id;

			if (box_id >= 0) {
				ent.id = box_id;
			}
			else {
				ent.id = m_next_id;
				m_next_id += 1;
			}

			ent.nghost = m_nghost;

			ent.position = m_entries.size() - 1;

			ent.owner = this;
		}

		// add ids
		m_procs_sort.push_back(ent.proc);
		m_ids_sort.push_back(ent.id);

		// 
		if (proc_id == myproc) {
			m_my_ids.push_back(ent.id);
			m_my_entries.push_back(&ent);
		}

	} // valid box
}



END_SBOX_NS;

#endif



