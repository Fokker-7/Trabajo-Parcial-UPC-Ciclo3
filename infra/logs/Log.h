#pragma once

#include <string>

class Log {

private:
    std::string action;
    std::string timestamp;

public:

    Log() = default;

    Log(
        const std::string& action,
        const std::string& timestamp
    );

    std::string getAction() const;

    std::string getTimestamp() const;

    std::string toString() const;
};