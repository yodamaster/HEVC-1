#ifndef _LOGGER_
#define _LOGGER_

#include "TypeDef.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>

class Logger
{

private:

	std::string m_logPath; ///< sciezka do pliku logu
	std::ofstream m_logStream; ///< strumien do pliku logu
	Bool m_printSpaces;

	UInt m_numTabs;
	UInt m_step; 
	std::string m_spaces;

	Bool m_loggingOn; ///< wlacza/wylacza log

	template<typename T>
	struct identity { typedef T type; };

	Void emptyBuffer();

	Void printSpaces();

	template<typename T>
	Void write(T s, identity<T> i);

	Void write(const Char* s, identity<const Char*> i)
	{
		std::string str(s);
		write(str);
	}

	Void write(std::string s, identity<std::string> i)
	{
		if(!s.compare("\n") || s.find("\n")!=std::string::npos)
		{
			m_printSpaces=true;
			m_logStream << s;
			return;
		}
		else
		{
			if(m_printSpaces)
			{
				printSpaces();
			}
			m_logStream << s;
		}
	}

public:
	
	Logger();
	Logger(std::string logPath, Bool isLogging);
	~Logger();

	Bool includeDetails; ///< czy dodaje parametry typu offsety, shifty, info o glebii bitowej itp.

	template<typename T>
	friend Logger& operator<<(Logger& o, T const& t);

	Void increaseSpaces();
	Void decreaseSpaces();
	Logger& operator++() 
	{ 
		this->increaseSpaces();
		return *this;
  }
	Logger& operator--() 
	{ 
		this->decreaseSpaces();
		return *this;
  }

	Void setLogging(Bool log);
	Void changeLogPath(std::string path);
	Bool isLogging(){return m_loggingOn;}

	Void setTabLength(UInt len);
	Void setTabStep(UInt len);
	
	template<typename T>
	Void write(T s);
};

#include "LoggerImpl.h"

Logger& operator<<(Logger& o, std::ostream& (*f)(std::ostream&));

#endif