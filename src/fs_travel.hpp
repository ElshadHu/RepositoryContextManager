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
#include <stdexcept>
#include "utils.hpp"

namespace fsTravel {
	namespace fs = std::filesystem;


	void travelDirTree(const fs::path& pathToAnalyze,int depth);
	void travelFileContents(const fs::path& filepath);
	void travelSingleFile(const fs::path& filePath);
	
	

}
#endif
