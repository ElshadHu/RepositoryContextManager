#ifndef CLI_HEADER
#define CLI_HEADER
#include <string_view>
#include <vector>
#include <string>
#include <functional>
#include <filesystem>
#include "utils.hpp"


namespace cli {
	//single POD struct is implemented because it  handles everything about the cli parsing.It is clean and extendable

	using FilteringStrategy = std::function<bool(const std::filesystem::path&)>;

	struct Options {
		bool showHelp = false;
		bool showVersion = false;
		bool recent = false; // new
		bool dirsOnly = false; //new
		std::string outputFile;
		std::vector<std::string_view>inputFiles; //for getting more than one file and  getting total inputs
		std::string excludePattern;
		std::string includePattern;
		FilteringStrategy onIncludeFilter = nullptr;
		FilteringStrategy onExcludeFilter = nullptr;
		FilteringStrategy onRecentFilter = nullptr;

	};
	Options parse(int argc, char** argv); //using the  main arguments which the first is size the second is vector
}

#endif