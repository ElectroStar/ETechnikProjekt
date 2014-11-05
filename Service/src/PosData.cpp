/*
 * PosData.cpp
 *
 *  Created on: 05.11.2014
 *      Author: Sebastian Hollermann
 */

#include "PosData.h"
#include "PositioningDataException.h"
#include <regex>

PosData::PosData(string data) {
	// Daten liegen im Format $XXX.XX,YYY.YY,ZZZ.ZZ<CR><LF> vor
	regex expression("$\d{3}.");




}

PosData::~PosData() {
}

