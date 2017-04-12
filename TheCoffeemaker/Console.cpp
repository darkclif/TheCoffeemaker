#include "Console.h"

namespace CMaker {

	namespace Console {
		// Console extern objects
		Debug debug;
		Info info;

		Log consoleLog;


		/*
		Accesing logs
		*/
		std::vector<std::string>::iterator Log::logDebugIt()
		{
			return logDebug.begin();
		}

		std::vector<std::string>::iterator Log::logInfoIt()
		{
			return logDebug.begin();
		}

		/*
		Writing to logs
		*/
		void Log::writeDebug(std::string _line) {
			while (logDebug.size() == MAX_LOG) {
				logDebug.erase(logDebug.begin());
			}

			// Adding new lines
			std::size_t pos = _line.find('\n');
			while (pos != std::string::npos) {
				logDebug.back() += _line.substr(0, pos);

				_line = _line.substr(pos + 1);
				logDebug.push_back("");
				pos = _line.find('\n');
			}

			logDebug.back() += _line;
		}

		void Log::writeInfo(std::string _line) {
			while (logInfo.size() == MAX_LOG) {
				logInfo.erase(logInfo.begin());
			}

			// Adding new lines
			std::size_t pos = _line.find('\n');
			while (pos != std::string::npos) {
				logInfo.back() += (_line.substr(0, pos));

				_line = _line.substr(pos + 1);
				logInfo.push_back("");
				pos = _line.find('\n');
			}

			logInfo.back() += _line;
		}

		/*
		Specialized operators for Debug
		*/
		Debug& operator<< (Debug &s, std::ostream& (*f)(std::ostream &)) {
#			ifdef _SHOW_DEBUG
			f(std::cout);
#			endif

#			ifdef _CONSOLE_LOG
			std::ostringstream tmpStream;
			f(tmpStream);
			consoleLog.writeDebug(tmpStream.str());
#			endif

			return s;
		}

		Debug& operator<< (Debug &s, std::ostream& (*f)(std::ios &)) {
#			ifdef _SHOW_DEBUG
			f(std::cout);
#			endif

#			ifdef _CONSOLE_LOG
			std::ostringstream tmpStream;
			f(tmpStream);
			consoleLog.writeDebug(tmpStream.str());
#			endif

			return s;
		}

		Debug& operator<< (Debug &s, std::ostream& (*f)(std::ios_base &)) {
#			ifdef _SHOW_DEBUG
			f(std::cout);
#			endif

#			ifdef _CONSOLE_LOG
			std::ostringstream tmpStream;
			f(tmpStream);
			consoleLog.writeDebug(tmpStream.str());
#			endif

			return s;
		}

		/*
		Info specialized operators
		*/
		Info& operator<< (Info &s, std::ostream& (*f)(std::ostream &)) {
#			ifdef _SHOW_INFO
			f(std::cout);
#			endif

#			ifdef _CONSOLE_LOG
			std::ostringstream tmpStream;
			f(tmpStream);
			consoleLog.writeInfo(tmpStream.str());
#			endif

			return s;
		}

		Info& operator<< (Info &s, std::ostream& (*f)(std::ios &)) {
#			ifdef _SHOW_INFO
			f(std::cout);
#			endif

#			ifdef _CONSOLE_LOG
			std::ostringstream tmpStream;
			f(tmpStream);
			consoleLog.writeInfo(tmpStream.str());
#			endif

			return s;
		}

		Info& operator<< (Info &s, std::ostream& (*f)(std::ios_base &)) {
#			ifdef _SHOW_INFO
			f(std::cout);
#			endif

#			ifdef _CONSOLE_LOG
			std::ostringstream tmpStream;
			f(tmpStream);
			consoleLog.writeInfo(tmpStream.str());
#			endif

			return s;
		}

	}

}