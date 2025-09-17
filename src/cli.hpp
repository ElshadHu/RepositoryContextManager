#ifndef CLI_HEADER
#define CLI_HEADER
#include <string_view>
#include <vector>
#include <string>

namespace cli {
	//single POD struct is implemented because it  handles everything about the cli parsing.It is clean and extendable
	struct Options {
		bool showHelp = false;
		bool showVersion = false;
		std::string outputFile;
		std::vector<std::string_view>inputFiles; //for getting more than one file
		//for new featurues
		std::string fileExtension;
		std::string excludePattern;
		std::string outputFormat = "markdown";
		std::string maxFileSize;
	};
	Options parse(int argc, char** argv); //using the  main arguments which the first is size the second is vector
}

#endif