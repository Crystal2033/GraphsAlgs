#include "Exceptions.h"
Exception::Exception(const std::string& error_msg)
{
    error = error_msg;
}

const char* Exception::what() const
{
    return error.c_str();
}


std::string BuilderException::builder_what() const
{
    return error + "Bad symbol: " + (char)bad_symbol;
}
