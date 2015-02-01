//============================================================================
// Datei	: LocateableObj.h
// Autor	: Eric Buschermoehle
// Version	: 1.0
//============================================================================
#ifndef LOCATEABLEOBJ_H_
#define LOCATEABLEOBJ_H_

#include <stdint.h>

class LocateableObj {

private:

	enum Color {
		RED = 0,
		GREEN = -1,
		BLACK = 1
	};

	enum Form {
		Rectangle = 0,
	};

	Color color;
	Form form;

	uint32_t sizeInCm;

public:

	LocateableObj();
	~LocateableObj();

};

#endif /* LOCATEABLEOBJ_H_ */
