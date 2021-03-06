#pragma once

#define BEGIN_SBOX_NS namespace sbox {
#define END_SBOX_NS }

#include <vector>

#include <memory>
#include <algorithm>


//
#define SBOX_SPACEDIM 3


////////////////////////////////////////////////////////////////////////////////
BEGIN_SBOX_NS;
////////////////////////////////////////////////////////////////////////////////


const int SpaceDim = SBOX_SPACEDIM;


template<typename T>
using Array = std::vector<T>;



////////////////////////////////////////////////////////////////////////////////
END_SBOX_NS;
////////////////////////////////////////////////////////////////////////////////


