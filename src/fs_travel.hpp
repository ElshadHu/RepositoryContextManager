#ifndef FSTRAVEL_H
#define FSTRAVEL_H
#include <vector>
#include <iostream>
#include <filesystem>
#include <string>
#include <fstream>
#include <algorithm>
#include <array>
#include <iomanip>

#define SIZEOFFILE 16000
namespace fsTravel {
	namespace fs = std::filesystem;

	void displayDirTree(const fs::path& pathToAnalyze, int depth = 0);
	bool allowedExtensions(const std::string& ext);
	void displayFileContents(const fs::path& pathToAnalyze);
	void readDisplayFile(const fs::path& filepath);
	const std::string getLanguageExtension(const std::string& ext);

}
#endif
