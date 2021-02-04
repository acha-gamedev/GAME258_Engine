#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>
#include <string>
#include <fstream>

class Debug {
public:
	enum class MessageType {
		TYPE_NONE = 0,
		TYPE_FATAL,
		TYPE_ERROR,
		TYPE_WARNING,
		TYPE_TRACE,
		TYPE_INFO
	};

	Debug() = delete;
	Debug(const Debug&) = delete;
	Debug(Debug&&) = delete;
	Debug& operator=(const Debug&) = delete;
	Debug& operator=(Debug&&) = delete;

	//Initialize the debug logger
	static void OnCreate(const std::string& _name = "GAME258Engine Log");

	//Set the max severity to log
	//PARAMS: _severity: the max severity level to log
	static void SetSeverity(MessageType _severity);

	//Writes an Info-level message to log
	//PARAMS: _message: the message to log; _filename: the file the message is from; _line: the line the message is from
	static void LogInfo(const std::string& _message, const std::string& _filename, const int _line);

	//Writes an Trace-level message to log
	//PARAMS: _message: the message to log; _filename: the file the message is from; _line: the line the message is from
	static void LogTrace(const std::string& _message, const std::string& _filename, const int _line);

	//Writes an Warning-level message to log
	//PARAMS: _message: the message to log; _filename: the file the message is from; _line: the line the message is from
	static void LogWarning(const std::string& _message, const std::string& _filename, const int _line);

	//Writes an Error-level message to log
	//PARAMS: _message: the message to log; _filename: the file the message is from; _line: the line the message is from
	static void LogError(const std::string& _message, const std::string& _filename, const int _line);

	//Writes an Fatal-level message to log
	//PARAMS: _message: the message to log; _filename: the file the message is from; _line: the line the message is from
	static void LogFatal(const std::string& _message, const std::string& _filename, const int _line);

private:
	static void WriteLog(const MessageType _type, const std::string& _message, const std::string& _filename, const int _line);

	static MessageType severity;
	static std::string outputName;
};

#endif //DEBUG_H