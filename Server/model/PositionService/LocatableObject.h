//============================================================================
// Datei	: LocatableObject.h
// Autor	: Eric Buschermoehle
// Version	: 1.0
//============================================================================

#ifndef LOCATABLEOBJECT_H_
#define LOCATABLEOBJECT_H_

#include <stdint.h>

//Definition der moeglichen Formen
enum Form {
	TRIANGLE = 3,
	RECTANGLE = 4
};

/** Klasse zur Spezifikation erkennbarer Objekte.
 *  @author		Christian
 *  @date		11.02.2015
 */
class LocatableObject {

public:

	//Eigenschaften
	int colorMin;
	int colorMax;
	Form form;
    double sizeInCm;

public:

	/** Konstruktor.
	*/
	LocatableObject();
	
	/** Erweiterter Konstruktor.
	*  	@param[in] _form 		Form (s.o.)
	*  	@param[in] _colorMin 	Untere Farbkante (8-Bit)
	*	@param[in] _colorMax 	Obere Farbkante (8-Bit)
	*  	@param[in] _sizeInCm 	Groesse des realen Objekts
	*/
    LocatableObject(Form _form, int _colorMin, int _colorMax, double _sizeInCm);
	
	/** Destruktor.
	*/
	~LocatableObject();

};

#endif /* LOCATABLEOBJECT_H_ */
