#include "utils.hpp"

	//we are gonna initialize these variable and during the execution we will check
	//static  std::string m_includedExtension;
	//static std::string m_excludedExtension;




bool isGitIgnored(const std::filesystem::path& filePath) {
	std::string pathStr = filePath.string();
	std::string filename = filePath.filename().string();
	std::string extension = filePath.extension().string();

	// Convert to forward slashes for consistent matching
	std::replace(pathStr.begin(), pathStr.end(), '\\', '/');

	if (!filename.empty() && filename[0] == '.' && filename != ".gitignore") {
		return true;
	}
	constexpr std::array<std::string_view, 22> ignoredGit{
			".d", ".slo", ".lo", ".o", ".obj", ".gch", ".pch", ".ilk",
		".pdb", ".so", ".dylib", ".dll", ".mod", ".smod", ".lai",
		".la", ".a", ".lib", ".exe", ".out", ".app", ".dwo"
	};
	constexpr std::array<std::string_view, 8>ignoredDirs{
		".vs", "build", "out", ".git", ".github", ".gitignore", ".gitmodules", ".gitattributes"
	};

	for (const auto& ext : ignoredGit) {
		if (extension == ext) return true;
	}
	std::istringstream pathStream(pathStr);
	std::string component;
	while (std::getline(pathStream, component, '/')) {
		if (!component.empty()) {
			// Checking exact matches
			for (const auto& ignored : ignoredDirs) {
				if (component == ignored) return true;
			}
			if (component.find("build") != std::string::npos) return true;
		}
	}

	return false;
}

	bool matchingFileDir(const std::string& path, const std::string& filter) {
		
		std::string str = filter;
		if (filter == "*") 
			return true;

		if (filter.empty()) 
			return false;

		if (!str.empty() && str[0] == '*')
			 str.erase(0, 1);
		if (!str.empty() && str.back() == '*')
			str.pop_back();
		//after trimming if there is nothing match everything because of  *
		if (str.empty())
			return false;

		//if it finds true othervise false
		return path.find(str) != std::string::npos;
	}


	bool isRecentlyModified(const std::filesystem::path& filepath, int days) {
		if (!std::filesystem::exists(filepath)) {
			return false;
		}

		try {
			auto lastWriteTime = std::filesystem::last_write_time(filepath);

			// Convert to system clock time_point
			auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
				lastWriteTime - std::filesystem::file_time_type::clock::now()
				+ std::chrono::system_clock::now()
			);

			auto now = std::chrono::system_clock::now();
			auto age = std::chrono::duration_cast<std::chrono::hours>(now - sctp).count() / 24;

			return age <= days;
		}
		catch (const std::filesystem::filesystem_error& e) {
			std::cerr << "Error checking file timestamp: " << filepath << " (" << e.what() << ")\n";
			return false;
		}
	}



	bool onlyIncludedExtensions(const std::string& filepath, const std::string& includedFiles) {
		if (filepath.empty() || !std::filesystem::exists(filepath))
			return false;
		if (includedFiles.empty())
			return true;

		const std::string fullPath = std::filesystem::path(filepath).string();

		std::stringstream ss(includedFiles);
		std::string str;
		while (std::getline(ss, str, ',')) {
			std::size_t posFirst = str.find_first_not_of("\t ");
			std::size_t posLast = str.find_last_not_of("\t ");
			if (posFirst == std::string::npos) continue;

			str = str.substr(posFirst, posLast - posFirst + 1);

			if (matchingFileDir(fullPath, str))
				return true;
		}
		return false;
	}


 std::filesystem::path findGitRepository(const std::filesystem::path& beginPath) {
	std::filesystem::path searchingPath = std::filesystem::absolute(beginPath);//we get the absolute path
	//if it exists it will return  this path  that is the first check
	//later when we create the parentPath  and will change the path and gets the parent directory until it finds or path becomes same . if it does not find C:/ = C:/ break it and return empty {}
	while (!searchingPath.empty()) {
		if (std::filesystem::exists(searchingPath / ".git")) {
			return searchingPath;
		}

		auto parentPath = searchingPath.parent_path();
		if (parentPath == searchingPath) {
			break;
		}
		searchingPath = parentPath;
	}
	//if did not find return empty path
	return std::filesystem::path{};
}

 // new feature for file size
 std::uintmax_t getFileSize(const std::filesystem::path& filepath) {

	 try {
		 return std::filesystem::file_size(filepath);
	 }
	 catch(const std::filesystem::filesystem_error& e){
		 std::cerr << "Error getting file size " << e.what() << '\n';
		 return 0;
	 }

 }





 bool excludedExtensions(const std::string& filepath, const std::string& excludedList) {
	 if (excludedList.empty()) 
		 return false;
	 if (filepath.empty() || !std::filesystem::exists(filepath))
		 return false;

	 const std::string fullPath = std::filesystem::path(filepath).string();

	 std::stringstream ss(excludedList);
	 std::string token;
	 while (std::getline(ss, token, ',')) {
		 // trimming
		 std::size_t posFirst = token.find_first_not_of("\t ");
		 std::size_t posLast = token.find_last_not_of("\t ");
		 if (posFirst == std::string::npos) continue;
		 token = token.substr(posFirst, posLast - posFirst + 1);
		 if (token.empty()) continue;

		 // if any exclude matches  exclude it
		 if (matchingFileDir(fullPath, token)) return true;
	 }
	 return false;
 }



std::size_t countLines(const std::filesystem::path& filepath) {

	std::ifstream file(filepath);
	if (!file) {
		std::cerr << "file did not open for line counting: "<< filepath << '\n';
		return 0;
	}
	std::size_t numOfLines = 0;
	std::string line;
	while (std::getline(file, line)) {
		++numOfLines;
	}
	return numOfLines;
}


const std::string getLanguageExtension(const std::string& ext) {
	if (ext == ".cpp" || ext == ".hpp" || ext == ".h") {
		return "cpp";
	}
	else if (ext == ".c") {
		return "c";
	}
	else if (ext == ".js" || ext == ".mjs") {
		return "javascript";
	}
	else if (ext == ".py") {
		return "python";
	}
	else if (ext == ".java") {
		return "java";
	}
	else if (ext == ".ts") {
		return "typescript";
	}
	else if (ext == ".cs") {
		return "csharp";
	}
	else if (ext == ".go") {
		return "go";
	}
	else if (ext == ".json") {
		return "json";
	}
	else if (ext == ".xml") {
		return "xml";
	}
	else if (ext == ".yml") {
		return "yaml";
	}
	else if (ext == ".md") {
		return "markdown";
	}
	else if (ext == ".txt") {
		return "text";
	}
	return "text";
}



void readDisplayFile(const std::filesystem::path& filepath) {

	std::ifstream file(filepath);
	if (!file.is_open()) {
		std::cerr << "cannot open file: " << filepath << '\n';
		return;
	}

	std::cout << "\n### File:" << std::filesystem::relative(filepath) <<" (" << getFileSize(filepath) << " bytes )" << '\n';
	std::string format = filepath.extension().string();
	std::cout << "``` " << getLanguageExtension(format) << '\n';
	size_t bytes = 0;
	std::string str;
	bool truncated = false;
	while (std::getline(file, str)) {
		if (bytes + str.length() > MAX_SIZE_FILE) {
			truncated = true;
			break;
		}
		std::cout << str << '\n';
		bytes += str.length() + 1;//for newline
	}
	if (truncated) {
		std::cout << "\n.. [File truncated - exceeded " << MAX_SIZE_FILE << " bytes\n";
	}
	std::cout << "```" << '\n';
}

void showHelp() {
	std::cout << "the usage of repoctx [path..] [options]\n"
		<< "-h --help Show help\n"
		<< "-v --version Show version\n"
		<< " -o --output  Write output to file\n"
		<< " --include  Include file extensions (*.cpp,*.h)\n"
		<< " --exclude  Exclude files \n"
		<< " -r --recent  Show recently modified files \n"
		<< "--dirs-only -d Show Directory Structure with other sections except for File Contents\n";
}

void showVersion() {
	std::cout << "repoctx release 0.1\n";
}
