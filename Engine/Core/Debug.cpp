#include "Debug.h"

Debug::MessageType Debug::severity = Debug::MessageType::TYPE_NONE;
std::string Debug::outputName = "";

void Debug::OnCreate(const std::string& _name) {
	outputName = _name + ".txt";
	std::ofstream out;
	out.open(outputName.c_str(), std::ios::out);
	out.close();
	severity = MessageType::TYPE_INFO;
}

void Debug::SetSeverity(MessageType _severity) {
	severity = _severity;
}

void Debug::LogInfo(const std::string& _message, const std::string& _filename, const int _line) {
	WriteLog(MessageType::TYPE_INFO, "[INFO]: " + _message, _filename, _line);
}

void Debug::LogTrace(const std::string& _message, const std::string& _filename, const int _line) {
	WriteLog(MessageType::TYPE_TRACE, "[TRACE]: " + _message, _filename, _line);
}

void Debug::LogWarning(const std::string& _message, const std::string& _filename, const int _line) {
	WriteLog(MessageType::TYPE_WARNING, "[WARNING]: " + _message, _filename, _line);
}

void Debug::LogError(const std::string& _message, const std::string& _filename, const int _line) {
	WriteLog(MessageType::TYPE_ERROR, "[ERROR]: " + _message, _filename, _line);
}

void Debug::LogFatal(const std::string& _message, const std::string& _filename, const int _line) {
	WriteLog(MessageType::TYPE_FATAL, "[FATAL]: " + _message, _filename, _line);
}

void Debug::WriteLog(const MessageType _type, const std::string& _message, const std::string& _filename, const int _line) {
	if (_type <= severity && severity > MessageType::TYPE_NONE) {
		std::ofstream out;
		out.open(outputName.c_str(), std::ios::app | std::ios::out);
		out << _message << " in " << _filename << " at line " << _line << std::endl;
		out.flush();
		out.close();
	}
}