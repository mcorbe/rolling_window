/*
 * RollingWindowBO.hh
 *
 *  Created on: May 23, 2014
 *      Author: rapidape
 */

#ifndef ROLLINGWINDOWBO_HH_
#define ROLLINGWINDOWBO_HH_


#include <deque>
#include <fstream>
#include <sstream>
#include <stdint.h>


namespace rolling_window { namespace bo
{

// Rolling window implemented using a deque and 2 MIN / MAX buffers
class RollingWindowBO
{
public:
	typedef std::pair<uint32_t,double> DatedValue;
	typedef std::deque<DatedValue> DatedValueList;


	RollingWindowBO(uint8_t windowSize_p = 60);
	~RollingWindowBO();

	void addDatedValue( DatedValue const & pair_p);

	void validateState();

	bool openOutputFileStream();

	void displayCurrentState();

private:
	void updateMinMaxBuffers( double value_p);



	uint8_t windowSize_m;  // The rolling window size

	double minValue_m;     // The MIN buffer - WARN: can be invalidated when old records are pop out, needs reset
	uint8_t nbMinValue_m;  // MIN buffer counter to handle multiple occurrences

	double maxValue_m;     // The MAX buffer - WARN: can be invalidated when old records are pop out, needs reset
	uint8_t nbMaxValue_m;  // MAX buffer counter to handle multiple occurrences

	double total_m;        // Total buffer, always correct

	DatedValueList values_m;   // The actual std::deque

	std::ofstream outputfile_m;   // An output file write to log the results

};

}  // namespace bo
}  // namespace rolling_window


#endif /* ROLLINGWINDOWBO_HH_ */
