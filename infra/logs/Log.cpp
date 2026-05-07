#include "Log.h"

Log::Log(
    const std::string& action,
    const std::string& timestamp
)
    : action(action),
      timestamp(timestamp) {}

std::string Log::getAction() const {
    return action;
}

std::string Log::getTimestamp() const {
    return timestamp;
}

std::string Log::toString() const {

    return action + " | " + timestamp;
}