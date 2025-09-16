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

	struct TotalStatistics {
		std::size_t m_totalLines;
		std::size_t m_totalFiles;
		std::size_t m_totalTokens;
	};

	void travelDirTree(const fs::path& pathToAnalyze,int depth);
	TotalStatistics travelFileContents(const fs::path& filepath);
	void readDisplayFile(const fs::path& filepath);
	void travelSingleFile(const fs::path& filePath);
	//std::size_t countLines(const fs::path& filepath);
	
	

}
#endif
