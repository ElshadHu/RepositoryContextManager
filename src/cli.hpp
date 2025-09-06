#ifndef CLI_HEADER
#define CLI_HEADER
#include <string_view>
#include <vector>
#include <string>

namespace cli {

	struct Options {
		bool showHelp = false;
		bool showVersion = false;
		std::string outputFile;
		std::vector<std::string_view>inputFiles;
	};
	Options parse(int argc, char** argv);
}

#endif