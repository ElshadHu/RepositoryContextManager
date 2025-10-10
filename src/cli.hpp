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
		bool recent = false; 
		bool dirsOnly = false; 
		std::string outputFile;
		std::vector<std::string_view>inputFiles; 
		std::string excludePattern;
		std::string includePattern;
		FilteringStrategy onIncludeFilter = nullptr;
		FilteringStrategy onExcludeFilter = nullptr;
		FilteringStrategy onRecentFilter = nullptr;

	};
	Options parse(int argc, char** argv); 
}

#endif