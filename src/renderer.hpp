#pragma once
#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <sstream>
#include "cli.hpp"
#include "git_info.hpp"
#include "fs_travel.hpp"

namespace output {
	//output target
	std::ostream& targetOut(std::ofstream& file, const std::string& filename);
	void writeGitInfo(std::ostream& o, const std::filesystem::path& absolute);
	bool writeCliCommands(const cli::Options& opt);
	void renderRepositoryContext(const std::string& filename,const cli::Options&opt);
	void writeFileStructure(std::ostream& o, const std::filesystem::path& path);
	fsTravel::TotalStatistics writeFileContents(std::ostream& o, const std::filesystem::path& path);

}