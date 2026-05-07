#include "LogHandler.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include <ctime>

LogHandler::LogHandler(
    const std::string& filename
)
    : filename(filename) {

    loadLogs();
}

std::string LogHandler::generateTimestamp() {

    std::time_t now = std::time(nullptr);

    std::tm* localTime =
        std::localtime(&now);

    char buffer[80];

    std::strftime(
        buffer,
        sizeof(buffer),
        "%Y-%m-%d %H:%M:%S",
        localTime
    );

    return std::string(buffer);
}

void LogHandler::loadLogs() {

    std::ifstream file(filename);

    if (!file.is_open())
        return;

    std::string line;

    while (std::getline(file, line)) {

        size_t separator =
            line.find('|');

        if (separator == std::string::npos)
            continue;

        std::string action =
            line.substr(0, separator - 1);

        std::string timestamp =
            line.substr(separator + 2);

        logs.push_back(
            Log(action, timestamp)
        );
    }

    file.close();
}

void LogHandler::addLog(
    const std::string& action
) {

    std::string timestamp =
        generateTimestamp();

    Log log(action, timestamp);

    //
    // Guardar en memoria
    //
    logs.push_back(log);

    //
    // Guardar en archivo
    //
    std::ofstream file(
        filename,
        std::ios::app
    );

    if (file.is_open()) {

        file
            << log.toString()
            << '\n';

        file.close();
    }
}

void LogHandler::showLogs() const {

    for (const auto& log : logs) {

        std::cout
            << log.toString()
            << '\n';
    }
}

std::vector<Log>& LogHandler::getLogs() {
    return logs;
}