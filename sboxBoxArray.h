#pragma once


#include "sbox.h"
//#include "sboxParallel.h"
#include "sboxIndexType.h"
#include "sboxIntBox.h"

#include <iosfwd>


BEGIN_SBOX_NS;

struct IntersectResult
{
	int index;
	Box box;
};


class BoxArray : public Array<Box>
{
public:
	typedef std::shared_ptr<BoxArray> Ptr;

protected:

	IndexType m_type;

public:

	BoxArray();
	BoxArray(IndexType btype);

	~BoxArray();

	const IndexType& boxIndexType() const { return m_type; }




	Box calcBoundBox() const;

	////////////////////////////////////////
public:

	Array<IntersectResult> intersections(const Box &rhs) const;




};

std::ostream& operator<<(std::ostream& os, const BoxArray &ba);




END_SBOX_NS;

