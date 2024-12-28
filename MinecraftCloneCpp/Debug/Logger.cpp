#include "Logger.h"

LogLevel Logger::logLevel = LogLevel::Verbose;

void Logger::formatMessage(std::ostringstream& oss, const std::string& formatString)
{
	oss << formatString;
}

std::string Logger::getLogLevelPrefix(LogLevel level)
{
	switch (level) 
	{
	case LogLevel::Verbose:
		return "Verbose - ";
	case LogLevel::Log:
		return "Log - ";
	case LogLevel::Warning:
		return "Warning - ";
	case LogLevel::Error:
		return "Error - ";
	default:
		return "UnknownLvl - ";
	}
}
