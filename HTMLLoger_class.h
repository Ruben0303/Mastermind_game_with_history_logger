#pragma once
#ifndef html_log_is_incl
#define html_log_is_incl
#include "Logger_class.h"
#include <iostream>
#include <fstream>
namespace my_logger
{
	class HTMLLogger :public Logger {
	public:
		HTMLLogger(std::ofstream & fout, std::string file_path) : my_fout(fout), file_path(file_path)
		{ 
			my_fout.open(file_path);
			my_fout << "<table border =\"1\">\n";
		}
		~HTMLLogger()
		{
			my_fout << "</table>\n";
			my_fout.close();
		}
		virtual void LogMessage(std::string Name,std::string msg) override
		{
			my_fout << "<tr>\n";
			{

				my_fout << "<td>";
				my_fout << Name << " ";
				my_fout << "</td>";
				my_fout <<  "<td>";
				my_fout << " "<< msg <<"\n";
				my_fout << "</td>";
				my_fout << "</tr>\n";

			}
		}
	private:
		std::string file_path;
		std::ofstream & my_fout;
	};
}
#endif // !html_log_is_incl

