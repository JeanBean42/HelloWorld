#include <iostream>
#include <cassert>
#include "range_tracker.h"

using namespace std;

bool range_tracker::insert(uint64_t seq)
{
	return insert(seq, seq);
}

bool range_tracker::insert(uint64_t seqStart, uint64_t seqEnd)
{
	if (_seqRange.empty()) {
		_seqRange.emplace(range::value_type(seqStart, seqEnd));
		return true;
	}
	
	// Find the first matching block
	auto lwr = _seqRange.lower_bound(seqStart);
	
	//
	// The first edge case is it at the end?
	//
	
	if(lwr == _seqRange.end()) {
		lwr--;
		
		// Is it within range of the end, if so extend
		if(seqStart <= (lwr->second + 1)) {
			if(lwr->second >= seqEnd)
				return false;
			
			lwr->second = seqEnd;
			return true;
		}
		
		// Its a new independent block
		_seqRange.emplace_hint(_seqRange.end(), range::value_type(seqStart, seqEnd));
		return true;
	}
	
	//
	// Is it at:
	//
	//   1) the front
	//   2) an exact match
	//   3) somewhere in the middle
	//
	
	if(lwr->first == seqStart) {
		if(lwr->second >= seqEnd)
			return false;
		
		lwr->second = seqEnd;
	}
	else if((lwr == _seqRange.begin())) {
		lwr = _seqRange.emplace_hint(lwr, range::value_type(seqStart, seqEnd));
	}
	else {
		auto prior = std::prev(lwr);
		
		// Check the element before to see if this is an extension
		if(seqStart <= (prior->second + 1)) {
			if(prior->second >= seqEnd)
				return false;
			
			prior->second = seqEnd;
			lwr = prior;
		} else {
			lwr = _seqRange.emplace_hint(lwr, range::value_type(seqStart, seqEnd));
		}
	}
	
	auto next = std::next(lwr);
	
	//
	// Having inserted or adjusted and existing range, now check the follow on ranges to
	// check if they roll-up into one another.
	//
	
	while(next != _seqRange.end() && (next->first <= (lwr->second + 1))) {
		lwr->second = std::max(lwr->second, next->second);
		next = _seqRange.erase(next);
	}
	
	return true;
}

bool range_tracker::check()
{
	uint64_t previous = 0;
	
	for(auto it : _seqRange) {
		if(previous != 0) {
			if(previous > it.first )
				return false;
		}
		
		if( it.first > it.second )
			return false;
		
		previous = it.second;
	}
	
	return true;
}

void range_tracker::print()
{
	cout << "Number of blocks:" << _seqRange.size() << endl;
	
	for(auto it : _seqRange) {
		cout << '[' << it.first << ':' << it.second << ']' << endl;
	}
}


bool range_tracker::remove(uint64_t seqStart, uint64_t seqEnd)
{
	if (_seqRange.empty()) {
		return false;
	}
	
	// Find the first matching block
	auto lwr = _seqRange.lower_bound(seqStart);
	
	//
	// The first edge case is it at the end?
	//
	
	if(lwr == _seqRange.end())
	{
		lwr--;
		
		// Is it within range of the end, if so extend
		if(seqStart > lwr->second)
			return false;
		
		lwr->second = seqStart - 1;
		
		assert(lwr->first >= lwr->second);
		
		return true;
	}
	
	if(lwr->first == seqStart) {
		if(lwr->second <= seqEnd) {
			lwr = _seqRange.erase(lwr);
		}
		else {
		
		}
	}
	else if {lwr != _seqRange.begin())
		lwr--;
	}
	
	while((lwr != _seqRange.end()) && (seqEnd >= lwr->first))
	{
	
	}
	
	
}