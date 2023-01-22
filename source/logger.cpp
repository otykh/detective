#include<iostream>
#include<logger.h>

Logger Logger::ls = Logger(Logger::SILENT);
Logger Logger::l = Logger(Logger::INFO);
Logger Logger::lwarn = Logger(Logger::WARN);
Logger Logger::lerr = Logger(Logger::ERR);
Logger Logger::lcrit = Logger(Logger::CRIT);

//const cstring Logger::signs[5] = {cstring("[i] "), "\033[1;33m[!]\033[0m ", "\033[1;31m[e]\033[0m ", "\033[41;30m[CRITICAL]\033[0m ", "\0"};

const cstring Logger::signs[5] = {
	cstring("[i] "),
	cstring("[!] ", cstring::YELLOW),
	cstring("[e] ", cstring::RED),
	cstring("[CRITICAL] ", cstring::BLACK, cstring::RED),
	"\0"};
	//"\033[41;30m[CRITICAL]\033[0m ", "\0"};

void Logger::test()
{
	Logger::l << "This is just a test" << std::endl;
	Logger::ls << "This is a silent test" << std::endl;
	Logger::lwarn << "This is a warning" << std::endl;
	Logger::lerr << "This is an error!" << std::endl;
	Logger::lcrit << "This is critical! Something has went horribly wrong" << std::endl;

	Logger::ls << cstring("White text") << std::endl;
	for(int i = 0; i < 7; i++)
	{
		Logger::ls << cstring("THE ", (cstring::COLORS)i);
		Logger::ls << std::endl;
		for(int j = 0; j < 7; j++)
		{
			Logger::ls << cstring("END ", (cstring::COLORS)i, (cstring::COLORS)j);
			for(int n = 0; n < 4; n++)
			{
				Logger::ls << cstring("IS NEVER ", (cstring::COLORS)i, (cstring::COLORS)j, (cstring::STYLE)n);
			}
			Logger::ls << std::endl;
		}
		Logger::ls << std::endl;
	}
}

Logger::Logger(msgtype type)
{
	Logger::messageType = type;
}
