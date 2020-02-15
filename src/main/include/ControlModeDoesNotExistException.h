#include <iostream>
#include <exception>

class ControlModeDoesNotExistException : public std::exception {
    public:
        virtual const char* printException() const throw() {
            return "Control mode does not exist";
        }
};