
#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include <exception>
#include <QMetaType>

namespace eagleeye {
    class EeException : public std::exception{
    public:
        enum Type {
            ERROR_OPEN_CONFIGURATIONFILE,
            INVALID_CONFIGURATIONFILE,
            ERROR_DURING_CALIBRATION
        };
EeException();
        EeException(Type type);
        virtual ~EeException() throw() {}

        Type getType();
    private:
        Type type;
    };

}


#endif /* EXCEPTION_H_ */
