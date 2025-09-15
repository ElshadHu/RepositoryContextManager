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
#define SIZEOFFILE 16234

namespace fsTravel {
	namespace fs = std::filesystem;

	//struct Totals {
	//	std::size_t m_totalLines;
	//	std::size_t m_totalFiles;
	//};

	void travelDirTree(const fs::path& pathToAnalyze,int depth);
	void travelFileContents(const fs::path& filepath);
	void readDisplayFile(const fs::path& filepath);
	//std::size_t countLines(const fs::path& filepath);
	//Totals getStatus(const fs::path& pathToAnalyze);
	

}
#endif
