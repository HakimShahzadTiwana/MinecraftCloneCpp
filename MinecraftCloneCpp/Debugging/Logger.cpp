#include "Logger.h"

LogLevel Logger::logLevel = LogLevel::Log;

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

std::string Logger::getLogColorPrefix(LogLevel level)
{
	switch (level)
	{
	case LogLevel::Verbose:
		return "\033[0m";
	case LogLevel::Log:
		return "\033[32m";
	case LogLevel::Warning:
		return "\033[33m";
	case LogLevel::Error:
		return "\033[31m";
	default:
		return "\033[0m";
	}
}
