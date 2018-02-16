#pragma once


#include "sbox.h"
//#include "sboxParallel.h"
#include "sboxIntBox.h"

#include <iosfwd>


BEGIN_SBOX_NS;


class BoxArray : public Array<Box>
{
public:
	typedef std::shared_ptr<BoxArray> Ptr;

protected:

	//Array<Box> m_boxes;

public:

	BoxArray();
	~BoxArray();

	//const Array<Box> boxes() const { return m_boxes; }

	//size_t size() const { return m_boxes.size(); }


	//auto begin() -> decltype(m_boxes.begin()) { return m_boxes.begin(); }
	//auto end() -> decltype(m_boxes.end()) { return m_boxes.end(); }
	//auto begin() const -> decltype(m_boxes.begin()) { return m_boxes.begin(); }
	//auto end() const-> decltype(m_boxes.end()) { return m_boxes.end(); }

	//const Box& operator[](int i) const { return m_boxes[i]; }
	//Box& operator[](int i) { return m_boxes[i]; }

	void appendBox(const Box &b) { push_back(b); }

	Box calcBoundBox() const;

};

std::ostream& operator<<(std::ostream& os, const BoxArray &ba);




END_SBOX_NS;

