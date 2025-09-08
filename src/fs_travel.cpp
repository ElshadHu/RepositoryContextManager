#include "fs_travel.hpp"

namespace fs = std::filesystem;

void iterateOverDirectory(const std::filesystem::path& root) {

	fs::path absoluteRoot = fs::absolute(root);
	std::cout << absoluteRoot << '\n';

	if (!fs::exists(absoluteRoot)) {
		std::cerr << "Error with " << root << "does not exist\n";
		return;
	}

	if (fs::is_regular_file(absoluteRoot)) {
		std::cout << "File: " << absoluteRoot.filename().string() << '\n';
		return;
	}

	if (fs::is_directory(absoluteRoot)) {
		for (const auto& entry : fs::directory_iterator(absoluteRoot)) {
			fs::path rel = fs::relative(entry.path(), absoluteRoot);

			if (fs::is_directory(entry)) {
				std::cout << "Directory: " << rel.string() << '\n';
			}
			else if (fs::is_regular_file(entry)) {
				std::cout << "File: " << rel.filename().string() << '\n';
			}
		}
		return;
	}
	std::cerr << "Error with " << root << "is not a valid file or directory\n";
}