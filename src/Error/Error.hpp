#ifndef ERROR_HPP_
#define ERROR_HPP_

#include <exception>
#include <iostream>

class Error : public std::exception {
    public:
        Error(const char *message) : _message(message) {}
        ~Error() = default;
        const char *what()
        {
            return (_message);
        }
    private:
        const char *_message;
};

#endif /* !ERROR_HPP_ */
