//============================================================================
// Datei	: CropFieldView.h
// Autor	: Eric Buschermoehle
// Version	: 1.0
//============================================================================

#ifndef CROPFIELDVIEW_H_
#define CROPFIELDVIEW_H_

#include "opencv2/core/core.hpp"

#include "ImageFilter.h"

/** Klasse um Bilder zuzuschneiden.
 *  @author		Eric Buschermoehle
 *  @date		11.02.2015
 */
class CropFieldView : ImageFilter {

private:

	Point first;
	Point second;

public:

    CropFieldView();

  /** Konstruktor
	*  	@param[in] _first		Erster Punkt
	*  	@param[in] _second		Zweiter Punkt
	*/
	CropFieldView(const Point _first, const Point _second);
  
  /** Destruktor
	*/
	~CropFieldView();
  
  /** Methode zum Zuschneiden einer Matrix
	*  	@param[in] _input 	Eingangsbild
	*  	@param[in] _output 	Ausgangsbild
	*/
	void filter(Mat &_input, Mat &_output) const;

    //coding guidelines
    Point getFirst() const;
    void setFirst(const Point &value);


    Point getSecond() const;
    void setSecond(const Point &value);
};

#endif /* CROPFIELDVIEW_H_ */
