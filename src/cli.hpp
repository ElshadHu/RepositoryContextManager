#ifndef CLI_HEADER
#define CLI_HEADER
#include <string_view>
#include <vector>
#include <string>

namespace cli {
	//single POD struct is implemented because it  handles everthing about the cli parsing.It is clean and extendable
	struct Options {
		bool showHelp = false;
		bool showVersion = false;
		std::string outputFile;
		std::vector<std::string_view>inputFiles;
	};
	Options parse(int argc, char** argv);
}

#endif