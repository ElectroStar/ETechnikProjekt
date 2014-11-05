/*
 * PositioningDataException.h
 *
 *  Created on: 05.11.2014
 *      Author: Sebastian Hollermann
 */

#ifndef POSITIONINGDATAEXCEPTION_H_
#define POSITIONINGDATAEXCEPTION_H_

#include <exception>

using namespace std;

struct PositioningDataException : public exception
{
  const char * what () const throw ()
  {
    return "Wrong PositioningDataFormat";
  }
};

#endif /* POSITIONINGDATAEXCEPTION_H_ */
