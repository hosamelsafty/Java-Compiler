#include "writeErrorLogToFile.h"

void writeErrorLogToFile(const ErrorLog &errorLog, const std::string &filename)
{
	std::ofstream file;
	file.open(filename);
	file << errorLog;
	file.flush();
	file.close();
}
