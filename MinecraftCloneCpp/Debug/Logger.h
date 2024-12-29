#pragma once
#include <iostream>
#include <sstream>
#include <format>
#include <string>


#define LOG(level, _string, ...) Logger::log(LogLevel::level, "{}:: " + std::string(_string), __func__ , ##__VA_ARGS__)
#define LOG_FUNC() LOG(Verbose,"")

enum class LogLevel {Verbose = 0,Log = 1,Warning = 2,Error = 3};

class Logger 
{
public:

	// Enables logs that have a log level equal to or higher than the level set
	// if logLevel Set to Warnings, then only Warnings and Errors will be displayed
	static LogLevel logLevel;

	// Displays logs with depending on the Log Level Set
	// Formatting string is done by adding {} symbol and then adding the corresponding values as additional arguements to the function
	// For example log(LogLevel::Log,"My name is {}.","Jhon")
	template<typename... Args>
	static void log(LogLevel level, const std::string& formatString, Args&&...args);

private:

	// Varidic message formatting.
	template<typename T, typename...Args>
	static void formatMessage(std::ostringstream& oss, const std::string& formatString, T&& value, Args&&... args);

	// Base case function for recusive formatting
	static void formatMessage(std::ostringstream& oss, const std::string& formatString);

	// Returns the prefix used to display information about the current log level
	static std::string getLogLevelPrefix(LogLevel level);
};

#pragma region Template Implementations

template<typename... Args>
static void Logger::log(LogLevel level, const std::string& formatString, Args&&...args) 
{
	// Check if this log's level is equal or higher to the log level set to be displayed
	if (level >= logLevel) 
	{
		std::ostringstream oss;

		// format the string by replacing the arguements inplace of the formatting symbols 
		formatMessage(oss, formatString, std::forward<Args>(args)...);
		
		// Display formatted log messasge
		std::cout << getLogLevelPrefix(level) << oss.str() << std::endl;
	}
}



template<typename T, typename...Args>
static void Logger::formatMessage(std::ostringstream& oss, const std::string& formatString, T&& value, Args&&... args) 
{
	// Find the position of the first argument injection symbol
	size_t formatPos = formatString.find("{}");

	// C++20 format function but wanted to implement one myself
	//std::string message = std::vformat(formatString, std::make_format_args(std::forward<Args>(args)...));

	// Check if the argumenet injection symbol was found
	if (formatPos != std::string::npos)
	{
		// Get the subsystring from the start to where the symbol was found and then add the value 
		oss << formatString.substr(0, formatPos) << value;

		// Recursively check the remaining subsystring for the symbols and add the corresponding values
		formatMessage(oss, formatString.substr(formatPos + 2), std::forward<Args>(args)...);
	}
	else 
	{
		// If no more symbols were found just add the rest of the string using the base case function for the recursion
		formatMessage(oss, formatString);
	}
}


#pragma endregion

