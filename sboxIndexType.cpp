#include "sboxIndexType.h"

#include <iostream>

BEGIN_SBOX_NS;


void IndexType::setType(int dir, Position t)
{
	if (t == Cell) {
		unset(dir);
	}
	else {
		set(dir);
	}
}

IndexType IndexType::CellType()
{
	static IndexType inst(Cell, Cell, Cell);
	return inst;
}

IndexType IndexType::NodeType()
{
	static IndexType inst(Node, Node, Node);
	return inst;
}

IndexType IndexType::FaceType(int dir)
{
	IndexType it; 
	it.set(dir);
	return it;
}

IndexType IndexType::UmacType()
{
	static IndexType inst(Node, Cell, Cell);
	return inst;
}

IndexType IndexType::VmacType()
{
	static IndexType inst(Cell, Node, Cell);
	return inst;
}

IndexType IndexType::WmacType()
{
	static IndexType inst(Cell, Cell, Node);
	return inst;
}





std::ostream & operator<<(std::ostream & os, const IndexType & idxtype)
{
	os << "IndexType{";
	for (int dir = 0; dir < SBOX_SPACEDIM; dir++) {
		os << idxtype[dir] << ",";
	}
	os << "}";
	return os;
}



END_SBOX_NS;

