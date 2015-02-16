#include "converter.h"

Converter::Converter() {}

Converter::~Converter() {}
void Converter::convertMatToQImage(Mat &_src, QImage &_result) {


    if (_src.channels() == 3){
        cv::cvtColor(_src, _src, CV_BGR2RGB);
        _result = QImage((const unsigned char*)(_src.data),_src.cols,_src.rows,_src.step,QImage::Format_RGB888);
       // _result.bits();

    }

    else {
        _result = QImage((const unsigned char*)(_src.data),_src.cols,_src.rows,QImage::Format_Indexed8);
    }

}

