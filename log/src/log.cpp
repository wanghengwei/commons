#include "log.h"

template<>
auto clogger::_os = &std::clog;
