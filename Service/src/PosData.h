/*
 * PosData.h
 *
 *  Created on: 05.11.2014
 *      Author: Sebastian Hollermann
 */

#ifndef POSDATA_H_
#define POSDATA_H_

#include <string>

using namespace std;

class PosData {
private:
	string _x;
	string _y;
	string _z;
public:
	PosData(string data);
	virtual ~PosData();
	string getX() { return _x; }
	string getY() { return _y; }
	string getZ() { return _z; }
	operator string() const;
};

#endif /* POSDATA_H_ */
