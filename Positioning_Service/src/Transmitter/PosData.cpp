//============================================================================
// Datei	: PosData.cpp
// Autor	: Sebastian Hollermann
// Version	: 1.0
//============================================================================

#include "PosData.h"
#include "PositioningDataException.h"
#include <regex.h>

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

	string pattern = "[0-9]{3}\\.[0-9]{2},[0-9]{3}\\.[0-9]{2},[0-9]{3}\\.[0-9]{2},[0-9]{3}\\.[0-9]{2},[A-Za-z0-9]{2},[0-9]{3}\\.[0-9]{2},[0-9]{3}\\.[0-9]{2},[0-9]{4},[0-9]{18}\r\n";

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

	_x = data.substr(1, 6);
	_y = data.substr(8, 6);
	_z = data.substr(15, 6);
	_error = data.substr(22, 6);
	_mr = data.substr(27, 2);
	_x2 = data.substr(30, 6);
	_y2 = data.substr(37, 6);
	_coef = data.substr(44, 4);
	_date = data.substr(49, 18);
}

/**
 * Konstruktor zum erzeugen eines Positionsdatensatzes aus einen Double Point
 * @param pos
 */
PosData::PosData(Point2d pos) {
	// z-Position wird auf 0 gesetzt
	_z = "000.00";
	char buffer[10];

	if(sprintf(buffer, "%06.2f", pos.x) != 6)
		throw PositioningDataException();
	_x = buffer;

	if(sprintf(buffer, "%06.2f", pos.y) != 6)
		throw PositioningDataException();
	_y = buffer;
}

PosData::operator string() const {
	string value = "$" + _x + "," + _y + "," + _z + "\r\n";
	return value;
}
