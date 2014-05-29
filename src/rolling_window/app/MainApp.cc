/*
 * MainApp.cc
 *
 *  Created on: May 22, 2014
 *      Author: rapidape
 */


#include "rolling_window/bo/RollingWindowBO.hh"

#include <ostream>
#include <iostream>


std::istream & operator >> (std::istream & lineStrStream_l, rolling_window::bo::RollingWindowBO::DatedValue & pair_p)
{
	char delimiter_l;
	lineStrStream_l >> pair_p.first
					>> delimiter_l
					>> pair_p.second;

	return lineStrStream_l;
}

int main(int argc_p, char ** argv_p)
{
	if( argc_p < 2)
	{
		std::cout << "Missing file name - Usage: " << argv_p[0] << " filename" << std::endl;
		return 1;
	}
	std::string filename_l( argv_p[1]);

	std::ifstream fileIStream_l( filename_l.c_str());
	if( ! fileIStream_l)
	{
		std::cout << "Give file (" << filename_l << ") could not be opened !" << std::endl;
		return 1;
	}

	rolling_window::bo::RollingWindowBO rollingWindow_l;
	if ( ! rollingWindow_l.openOutputFileStream())
	{
		std::cout << "Could not write result to file, abort." << std::endl;
		return 1;
	}

	std::string line_l;
	while( std::getline( fileIStream_l, line_l))
	{
		std::stringstream lineStrStream_l(line_l);
		rolling_window::bo::RollingWindowBO::DatedValue pair_l;

		lineStrStream_l >> pair_l;

		rollingWindow_l.addDatedValue( pair_l);
		rollingWindow_l.validateState();
		rollingWindow_l.displayCurrentState();
	}
}
