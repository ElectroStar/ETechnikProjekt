#include "exception.h"

namespace eagleeye {
    EeException::EeException(Type type) : type(type){}

    EeException::Type EeException::getType() {
        return type;
    }
}
