#pragma once

#include <kamek.h>
#include <nw4r/ut/utList.h>

// Shamelessly copied from https://github.com/riidefi/mkw/blob/master/source/egg/core/eggDisposer.hpp

namespace EGG {

// Declaration for next structure
class Heap;

class Disposer {
	public:
		void* vtable; // Will be removed when virtual funcs are defined
  		Heap* mContainHeap;
  		nw4r::ut::Link mLink;
};

} // namespace EGG
