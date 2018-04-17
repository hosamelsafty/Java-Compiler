#include "ErrorLog.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/ostreamwrapper.h"
ErrorLog::ErrorLog() {

}

ErrorLog::~ErrorLog() {

}

void ErrorLog::add(const std::string &lexeme, int lineNumber,
		const std::string &message) {
	elog[lineNumber] = std::make_pair(lexeme, message);
}

std::ostream& operator<<(std::ostream& out,
		const ErrorLog &errorLog) {

	for (const std::pair<int, std::pair<std::string, std::string> > & logrow : errorLog.elog) {
		out << "Line = " << logrow.first;
		out << ", lexem = " << logrow.second.first
				<< ", message = " << logrow.second.second
				<< "\n";

	}

	return out;
}
