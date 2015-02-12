//============================================================================
// Datei	: TailorFieldView.h
// Autor	: Eric Buschermoehle
// Version: 1.0
//============================================================================

#ifndef TAILORFIELDVIEW_H_
#define TAILORFIELDVIEW_H_

#include "opencv2/core/core.hpp"

#include "ImageFilter.h"

/** Klasse um Bilder zuzuschneiden.
 *  @author		Eric Buschermoehle
 *  @date		31.07.2014
 */
class TailorFieldView : ImageFilter {

private:
	Point first;
	Point second;

public:
  /** Konstruktor
	*  	@param[in] _first		Erster Punkt
	*  	@param[in] _second		Zweiter Punkt
	*/
	TailorFieldView(const Point _first, const Point _second);
  
  /** Destruktor
	*/
	~TailorFieldView();
  
  /** Methode zum Zuschneiden einer Mat
	*  	@param[in] _input 	Eingangsbild
	*  	@param[in] _output 	Ausgangsbild
	*/
	void filter(Mat &_input, Mat &_output) const;

  /** Setter fuer lowerLeft
	*  	@param[in] _first 	Eingabe
	*/
	void setlowerLeft(const Point _first);
  
   /** Setter fuer upperRight
	*  	@param[in] _second 	Eingabe
	*/
	void setupperRight(const Point _second);

};

#endif /* TAILORFIELDVIEW_H_ */
