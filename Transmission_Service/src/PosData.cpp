//============================================================================
// Datei	: PosData.cpp
// Autor	: Sebastian Hollermann
// Version	: 1.0
//============================================================================

#include "PosData.h"
#include "PositioningDataException.h"
#include <regex.h>
#include <sstream>
#include <cstdio>
#include <cstdlib>

/**
 * Konsturktor zum laden eines Positionsdatensatzes in String Format
 * @param data
 */
PosData::PosData(string data) {
	// Daten liegen im Format $XXX.XX,YYY.YY,ZZZ.ZZ,FFF.FF,MR,XXX.XX,YYY.YY,KOEF,YYYYMMDDHHmmSSffff<CR><LF> vor
	if(data.length() < 1)
		throw PositioningDataException();

	// Dollarzeichen pruefen, ka ihrgentwie geht das nicht mit POSIX REGEX
	if(data[0] != '$')
		throw PositioningDataException();

	// Formatueberpruefung mit REGEX
	regex_t reg;

	string pattern = "[-+]?[0-9]{1,}\\.[0-9]{1,},[-+]?[0-9]{1,}\\.[0-9]{1,},[-+]?[0-9]{1,}\\.[0-9]{1,},[-+]?[0-9]{1,}\\.[0-9]{1,},[A-Za-z0-9]{2},[-+]?[0-9]{1,}\\.[0-9]{1,},[-+]?[0-9]{1,}\\.[0-9]{1,},[-+]?[0-9]{1,}\\.[0-9]{1,},[-+]?[0-9]{1,}\r\n";

	regmatch_t matches[1];

	regcomp(&reg,pattern.c_str(),REG_EXTENDED|REG_ICASE);

	if (regexec(&reg,data.c_str(),1,matches,0)==0) {
		if(matches[0].rm_so != 1)
			throw PositioningDataException();
	} else {
		throw PositioningDataException();
	}
	// Speicher von der REGEX-Pruefung wieder freigeben
	regfree(&reg);

	/*stringstream convert(data);
	char komma;
	komma << convert;
	_x << convert;
	komma << convert;
	_y << convert;
	komma << convert;
	_z << convert;
	komma << convert;
	_error << convert;
	komma << convert;
	_mr << convert;
	komma << convert;
	_x2 << convert;
	komma << convert;
	_y2 << convert;
	komma << convert;
	_coef << convert;
	komma << convert;
	_date << convert;
	*/

	size_t startIndex = 1;
	size_t searchIndex = data.find("$");
	if(searchIndex == string::npos)
		throw PositioningDataException();

	size_t i = 1;
	for(i = 1; i <= 9; i++) {
		if(i < 9)
			searchIndex = data.find(",", startIndex);
		else
			searchIndex = data.find("\r\n", startIndex);

		if(searchIndex == string::npos)
			break;

		switch(i) {
			case 1:
				_x = atof(data.substr(startIndex, searchIndex-startIndex).c_str());
				break;
			case 2:
				_y = atof(data.substr(startIndex, searchIndex-startIndex).c_str());
				break;
			case 3:
				_z = atof(data.substr(startIndex, searchIndex-startIndex).c_str());
				break;
			case 4:
				_error = atof(data.substr(startIndex, searchIndex-startIndex).c_str());
				break;
			case 5:
				_mr = data.substr(startIndex, searchIndex-startIndex);
				break;
			case 6:
				_x2 = atof(data.substr(startIndex, searchIndex-startIndex).c_str());
				break;
			case 7:
				_y2 = atof(data.substr(startIndex, searchIndex-startIndex).c_str());
				break;
			case 8:
				_coef = atof(data.substr(startIndex, searchIndex-startIndex).c_str());
				break;
			case 9:
				_date = atol(data.substr(startIndex, searchIndex-startIndex).c_str());
		}

		startIndex = searchIndex+1;
	}

	/*
	_x = atof(data.substr(1, 6).c_str());
	_y = data.substr(8, 6);
	_z = data.substr(15, 6);
	_error = data.substr(22, 6);
	_mr = data.substr(27, 2);
	_x2 = data.substr(30, 6);
	_y2 = data.substr(37, 6);
	_coef = data.substr(44, 4);
	_date = data.substr(49, 18);
	*/
}

PosData::operator string() const {
	//ostringstream ostream;
	char buffer[512];
	int n;
	n = sprintf(buffer, "$%f,%f,%f,%f,%s,%f,%f,%f,%ld\r\n", _x, _y, _z, _error, _mr.c_str(),
			_x2, _y2, _coef, _date);
	//ostream << "$" << _x << "," << _y << "," << _z << "," << _error << "," << _mr
	//		<< "," << _x2 << "," << _y2 << "," << _coef << "," << _date << "\r\n";
	//string value = ostream.str();
	string value(buffer);

	return value;
}
