#include "range_tracker.h"
#include <iostream>
#include <cassert>

using namespace std;

int main()
{
	range_tracker t;
	
	assert(t.insert(5,10));
	assert(t.insert(11, 20));
	assert(t.insert(20, 30));
	
	assert(!t.insert(29));
	
	assert(t.insert(35, 40));
	assert(t.insert(31, 33));
	assert(t.insert(1,3));
	
	assert(!t.insert(1));
	assert(!t.insert(2));
	assert(!t.insert(3));
	
	assert(t.insert(1,4));
	
	assert(t.insert(34));
	
	t.print();
}

