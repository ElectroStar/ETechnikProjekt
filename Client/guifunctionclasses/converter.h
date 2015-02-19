#ifndef CONVERTER_H
#define CONVERTER_H


#include <QImage>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

class Converter {
public:
    Converter();
    ~Converter();

    static void convertMatToQImage(Mat &_src, QImage &_result);
};

#endif // CONVERTER_H
