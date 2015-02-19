//============================================================================
// Datei	: PosData.cpp
// Autor	: Sebastian Hollermann
// Version	: 1.0
//============================================================================

#include "PosData.h"
#include "PositioningDataException.h"
#include <regex.h>
#include <stdio.h>
#include <ctime>
#include <sys/time.h>
#include <stdlib.h>
#include <algorithm>

/**
 * Konstruktor
 */

void PosData::setDate(long date)
{
    _date = date;
}

void PosData::setCoef(double coef)
{
    _coef = coef;
}

void PosData::setY2(double y2)
{
    _y2 = y2;
}

void PosData::setX2(double x2)
{
    _x2 = x2;
}

void PosData::setMr(const string &mr)
{
    _mr = mr;
}

void PosData::setError(double error)
{
    _error = error;
}

void PosData::setZ(double z)
{
    _z = z;
}

void PosData::setY(double y)
{
    _y = y;
}

void PosData::setX(double x)
{
    _x = x;
}
PosData::PosData() {
    _x = 0;
    _y = 0;
    _z = 0;
    _error = 0;
    _mr = "xx";
    _x2 = 0;
    _y2 = 0;
    _coef = 0;
	timeval zeit;
	gettimeofday(&zeit, 0);
	_date = zeit.tv_sec * 1000 + zeit.tv_usec / 1000;
}

/**
 * Konstruktor zum Laden eines Positionsdatensatzes im String Format
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

	string pattern = "[0-9]{1,}\\.[0-9]{1,},[0-9]{1,}\\.[0-9]{1,},[0-9]{1,}\\.[0-9]{1,},[0-9]{1,}\\.[0-9]{1,},[A-Za-z0-9]{2},[0-9]{1,}\\.[0-9]{1,},[0-9]{1,}\\.[0-9]{1,},[0-9]{1,}\\.[0-9]{1,},[0-9]{1,}\r\n";

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
}

PosData::operator string() const {
	char buffer[512];
    std::setlocale(LC_NUMERIC, "en_US");
    sprintf(buffer, "$%f;%f;%f;%f;%s;%f;%f;%f;%ld\r\n", _x, _y, _z, _error, _mr.c_str(),
			_x2, _y2, _coef, _date);
	string value(buffer);
    std::replace( value.begin(), value.end(), ',', '.');
    std::replace( value.begin(), value.end(), ';', ',');

	return value;
}
