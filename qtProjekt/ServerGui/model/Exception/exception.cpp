#include "exception.h"

namespace eagleeye {
    Exception::Exception(Type type) : type(type){}

    Exception::~Exception() {}

    Exception::Type Exception::getType() {
        return type;
    }
}
