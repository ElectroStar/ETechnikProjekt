//============================================================================
// Datei	: converter.h
// Autor	: Eric Buschermoehle
// Version	: 1.0
//============================================================================

#ifndef CONVERTER_H
#define CONVERTER_H

#include <QImage>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

/** Klasse zum Umwandeln einer OpenCV Mat in QImage.
 *  @author		Eric
 *  @date		12.02.2015
 */
class Converter {
public:

    /** Konstruktor.
    */
    Converter();

    /** Destruktor.
    */
    ~Converter();

    /** Methode zur Konvertierung.
    *  	@param[in] _src 	OpenCV Mat
    * 	@param[in] _result	QT QImage
    */
    static void convertMatToQImage(Mat &_src, QImage &_result);
};

#endif // CONVERTER_H
