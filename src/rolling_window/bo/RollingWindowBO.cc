/*
 * RollingWindowBO.cc
 *
 *  Created on: May 23, 2014
 *      Author: rapidape
 */


#include "RollingWindowBO.hh"

namespace rolling_window { namespace bo
{

RollingWindowBO::RollingWindowBO(uint8_t windowSize_p) :
	windowSize_m( windowSize_p),
	minValue_m(-1.0),
	nbMinValue_m(0),
	maxValue_m(-1.0),
	nbMaxValue_m(0),
	total_m(0.0)
{}

RollingWindowBO::~RollingWindowBO() {}

void RollingWindowBO::updateMinMaxBuffers( double value_p)
{
	if ( minValue_m == -1.0 || value_p <= minValue_m)
	{
		if ( value_p < minValue_m)
		{
			nbMinValue_m = 0;
		}

		minValue_m = value_p;
		++nbMinValue_m;
	}

	if ( maxValue_m == -1.0 || value_p >= maxValue_m)
	{
		if ( value_p > maxValue_m)
		{
			nbMaxValue_m = 0;
		}

		maxValue_m = value_p;
		++nbMaxValue_m;
	}
}

void RollingWindowBO::addDatedValue( DatedValue const & pair_p)
{
	// Add value and update rolling window buffers ( min, max and total)
	// buffer status would not be corrupted be insertions
	updateMinMaxBuffers( pair_p.second);

	// Update the rolling window total
	total_m += pair_p.second;

	values_m.push_back( pair_p);
}

void RollingWindowBO::validateState()
{
	// Delete old values and ensure MIN / MAX buffer integrity
	// when invalidated set MIN / MAX buffer to -1.0
	while ( values_m.front().first < values_m.back().first - windowSize_m)
	{
		// Update the rolling window total
		total_m -= values_m.front().second;

		// Here we can invalidate either MIN / MAX buffers
		// Case 1: removing the last minimum
		if ( minValue_m != -1.0 || values_m.front().second == minValue_m)
		{
			--nbMinValue_m;

			if ( nbMinValue_m == 0)
			{
				minValue_m = -1.0;
			}
		}

		// Case 2: removing the last maximum
		if ( maxValue_m != -1.0 || values_m.front().second == maxValue_m)
		{
			--nbMaxValue_m;

			if ( nbMaxValue_m == 0)
			{
				maxValue_m = -1.0;
			}
		}

		// Finally we can pop the old value out
		values_m.pop_front();
	}


	// If MIN / MAX buffer were not invalidated, we are done
	if ( minValue_m != -1.0 && maxValue_m != -1.0)
	{
		return;
	}

	// Else reset them
	for ( DatedValueList::const_reverse_iterator valueCRIter_l = values_m.rbegin();
		  valueCRIter_l != values_m.rend();
		  ++valueCRIter_l)
	{
		updateMinMaxBuffers( valueCRIter_l->second);
	}
}

bool RollingWindowBO::openOutputFileStream()
{
	outputfile_m.open("output.txt");
	if ( ! outputfile_m.is_open())
	{
		return false;
	}

	outputfile_m << "Time\tValue\tN_O\tRoll_Sum\tMin_Value\tMax_Value" << std::endl
				 << "---------------------------------------------------" << std::endl;

	return true;
}

void RollingWindowBO::displayCurrentState()
{
	// Dump rolling window current state
	outputfile_m <<  values_m.back().first << "\t"
				 << values_m.back().second << "\t"
				 << values_m.size() << "\t"
				 << total_m << "\t"
				 << minValue_m << "\t"
				 << maxValue_m << std::endl;
}


}  // namespace bo
}  // namespace rolling_window

