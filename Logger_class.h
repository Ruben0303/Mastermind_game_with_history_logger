#pragma once
#ifndef logger_is_incl
#define logger_is_incl
#include<iostream>
#include<string>
#include<chrono>
#include<ctime>
#include <stdio.h>
#include <time.h>

namespace  my_logger
{
	// Get current date/time, format is YYYY-MM-DD.HH:mm:ss

	enum LogCategory
	{
		Debug,
		Info,
		Warning,
		Error,
	};
	class Logger {
	private: std::ostream& my_out;
	protected:
		LogCategory verbosity;
	public:
		Logger(std::ostream & out = std::cout) : my_out(out), verbosity(Debug) {}
		virtual ~Logger(){}
		virtual void LogMessage(std::string Name ,std::string msg)
		{
				my_out << Name << " " << msg << "\n";
		}
		void SerVerbosity(LogCategory verbosity) { this->verbosity = verbosity; }
		const std::string currentDateTime() {
			time_t now = time(0);
			tm obj;
			localtime_s(&obj, &now);
			std::string result = std::to_string(obj.tm_year + 1900);
			result.push_back('-');
			std::string month = std::to_string(obj.tm_mon + 1);
			result += (month.size() < 2) ? '0' + month : month;
			result.push_back('-');
			std::string days = std::to_string(obj.tm_mday);
			result += (days.size() < 2) ? '0' + days : days;
			result.push_back(' ');
			std::string hour = std::to_string(obj.tm_hour);
			result += (hour.size() < 2) ? '0' + hour : hour;
			result.push_back(':');
			std::string min = std::to_string(obj.tm_min);
			result += (min.size() < 2) ? '0' + min : min;
			result.push_back(':');
			std::string secs = std::to_string(obj.tm_sec);
			result += (secs.size() < 2) ? '0' + secs : secs;
			return result;

		}
	};
}

#endif // !logger_is_incl
