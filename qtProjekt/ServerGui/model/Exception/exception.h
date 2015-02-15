
#ifndef EXCEPTION_H_
#define EXCEPTION_H_

namespace eagleeye {
    class Exception {
    public:
        enum Type {
            ERROR_OPEN_CONFIGURATIONFILE,
            INVALID_CONFIGURATIONFILE,
            ERROR_DURING_CALIBRATION
        };

        Exception(Type type);
        virtual ~Exception();

        Type getType();
    private:
        Type type;
    };
}

#endif /* EXCEPTION_H_ */
