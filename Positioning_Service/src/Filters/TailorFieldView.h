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
	Point lowerLeft;
	Point upperRight;

public:
  /** Konstruktor
	*  	@param[in] _lowerLeft 	Position unten links
	*  	@param[in] _upperRight 	Position unten rechts
	*/
	TailorFieldView(const Point _lowerLeft, const Point _upperRight);
  
  /** Destruktor
	*/
	~TailorFieldView();
  
  /** Methode zum zuzuschneiden eines einer Mat
	*  	@param[in] _input 	Eingangsbild
	*  	@param[in] _output 	Ausgangsbild
	*/
	void filter(Mat &_input, Mat &_output) const;

  /** Setter fuer lowerLeft
	*  	@param[in] _lowerLeft 	Eingabe
	*/
	void setlowerLeft(const Point &_lowerLeft);
  
   /** Setter fuer upperRight
	*  	@param[in] _upperRight 	Eingabe
	*/
	void setupperRight(const Point &_upperRight);

};

#endif /* TAILORFIELDVIEW_H_ */
