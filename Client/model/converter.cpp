//============================================================================
// Datei	: converter.cpp
// Autor	: Eric Buschermoehle
// Version	: 1.0
//============================================================================

#include "converter.h"

Converter::Converter() {}

Converter::~Converter() {}
void Converter::convertMatToQImage(Mat &_src, QImage &_result) {


    if (_src.channels() == 3){
        _result = QImage((const unsigned char*)(_src.data),_src.cols,_src.rows,_src.step,QImage::Format_RGB888);
    }

    else {
        _result = QImage((const unsigned char*)(_src.data),_src.cols,_src.rows,QImage::Format_Indexed8);
    }
}

