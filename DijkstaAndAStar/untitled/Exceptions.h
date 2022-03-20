#pragma once
#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <iostream>
#include <exception>
#include <string>

class Exception : public std::exception
{
protected:
    std::string error;
public:
    Exception() = default;
    Exception(const std::string& error_msg);
    const char* what() const override;
    ~Exception() = default;
};


class BuilderException final : public Exception
{
private:
    char bad_symbol;
public:
    BuilderException(const std::string& error_msg, const char symbol) {error = error_msg; bad_symbol = symbol;};
    void        set_new_str(const std::string str) {error = str;};
    void        set_bad_symbol(const char symbol) {bad_symbol = symbol;};
    std::string builder_what() const;
};

#endif // EXCEPTIONS_H
