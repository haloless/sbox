#pragma once

#include "sbox.h"
#include "sboxDimVec.h"

#include <iosfwd>

BEGIN_SBOX_NS;



struct IndexType
{
protected:
	int m_type;

public:
	enum Position {
		Cell = 0,
		Node = 1,
	};

	// default
	IndexType() : m_type(0) {}

	explicit IndexType(const IntVec &vec) {
		m_type = encode(
			vec[0] ? 1 : 0, 
			vec[1] ? 1 : 0, 
			vec[2] ? 1 : 0);
	}

	IndexType(Position i, Position j, Position k)
		: m_type(encode(i, j, k))
	{}

	bool ok() const { return 0 <= m_type && m_type < (1 << SBOX_SPACEDIM); }

	bool operator==(const IndexType &rhs) const { return m_type == rhs.m_type; }
	bool operator!=(const IndexType &rhs) const { return m_type != rhs.m_type; }

	// cast to int
	operator int() const { return m_type; }

	bool test(int dir) const { return (m_type & mask(dir)) != 0; }

	int operator[](int dir) const { return type(dir); }

	Position type(int dir) const {
		return static_cast<Position>((m_type & mask(dir)) >> dir);
	}

	void set(int dir) { m_type |= mask(dir); }
	void unset(int dir) { m_type &= ~mask(dir); }

	void setType(int dir, Position t);

public:

	static IndexType CellType();
	static IndexType NodeType();
	static IndexType FaceType(int dir);
	static IndexType UmacType();
	static IndexType VmacType();
	static IndexType WmacType();



	inline static int encode(int i, int j, int k) {
		return (i | (j << 1) | (k << 2));
	}

	inline static int mask(int dir) {
		return 1 << dir;
	}
};


std::ostream& operator<<(std::ostream &os, const IndexType &idxtype);

END_SBOX_NS;


