#pragma once

#include <vector>
#include <string>

#include "Log.h"

class LogHandler {

private:

    std::vector<Log> logs;

    std::string filename;

    void loadLogs();

    std::string generateTimestamp();

public:

    LogHandler(
        const std::string& filename = "data/logs.txt"
    );

    void addLog(const std::string& action);

    void showLogs() const;

    std::vector<Log>& getLogs();
};