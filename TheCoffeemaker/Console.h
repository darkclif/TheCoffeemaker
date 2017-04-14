#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

namespace CMaker {

	namespace Console {

		// On/off switch
		#define _SHOW_DEBUG
		#define _SHOW_INFO

		// Consoles shortcut
		#define C_DEBUG CMaker::Console::debug
		#define C_INFO CMaker::Console::info

		// Console shortcuts
		#define S_ERROR "ERROR: "
		#define S_WARNING "WARNING: "

		// Save debug and info
		class Log {
		public:
			std::vector<std::string>::iterator logDebugIt();
			std::vector<std::string>::iterator logInfoIt();

			void writeDebug(std::string _line);
			void writeInfo(std::string _line);

			Log() {};
		private:
			static const int MAX_LOG = 100;

			std::vector<std::string> logDebug = { "" };
			std::vector<std::string> logInfo = { "" };
		};
		extern Log consoleLog;

		/*
			Debug stream
		*/
		struct Debug {};
		extern Debug debug;
		
		template <typename T>
		Debug& operator<< (Debug &s, const T &x) {
#			ifdef _SHOW_DEBUG
			std::cout << x;
#			endif

#			ifdef _CONSOLE_LOG
			std::ostringstream tmpStream;
			tmpStream << x;
			consoleLog.writeDebug(tmpStream.str());
#			endif

			return s;
		}

		Debug& operator<< (Debug &s, std::ostream& (*f)(std::ostream &));
		Debug& operator<< (Debug &s, std::ostream& (*f)(std::ios &));
		Debug& operator<< (Debug &s, std::ostream& (*f)(std::ios_base &));

		/*
			Info stream
		*/
		struct Info {};
		extern Info info;

		template <typename T>
		Info& operator<< (Info &s, const T &x) {
#			ifdef _SHOW_INFO
			std::cout << x;
#			endif

#			ifdef _CONSOLE_LOG
			std::ostringstream tmpStream;
			tmpStream << x;
			consoleLog.writeInfo(tmpStream.str());
#			endif

			return s;
		}

		Info& operator<< (Info &s, std::ostream& (*f)(std::ostream &));
		Info& operator<< (Info &s, std::ostream& (*f)(std::ios &));
		Info& operator<< (Info &s, std::ostream& (*f)(std::ios_base &));
	}

}