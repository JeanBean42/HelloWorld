#pragma once

#include <map>
#include <cstdint>

using range = std::map<uint64_t, uint64_t>;

class range_tracker
{
public:
	
	bool insert(uint64_t seq);
	bool insert(uint64_t seqStart, uint64_t seqEnd);
	
	//bool remove(uint64_t seq);
	bool remove(uint64_t seqStart, uint64_t seqEnd);
	//bool remove_up_to(uint64_t seqNo);
	
	bool check();
	void print();
	
protected:
	
	range _seqRange;
};

