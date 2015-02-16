
#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include "config.h"
#include <exception>

namespace eagleeye {
    class EeException : public std::exception{
    public:
        enum Type {
            ERROR_OPEN_CONFIGURATIONFILE,
            INVALID_CONFIGURATIONFILE,
            ERROR_DURING_CALIBRATION
        };

        EeException(Type type);
        virtual ~EeException() throw() {}

        Type getType();
    private:
        Type type;
    };
}

#endif /* EXCEPTION_H_ */
