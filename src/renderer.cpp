#include "renderer.hpp"

namespace output {

	//if filename is empty target the console otherwise write to the file
	std::ostream& targetOut(std::ofstream& file, const std::string& filename) {
		if (filename.empty())
			return std::cout;
		file.open(filename);
		if (!file)
			throw std::runtime_error("Error opening output File: " + filename);
		return file;

	}


	void writeGitInfo(std::ostream& o, const std::filesystem::path& absolute) {
		o << "### GIT INFO \n\n";

		const auto repo = findGitRepository(absolute);
		gitInfo::GitInfo gi;
		if (!repo.empty()) gi = gitInfo::getGitData(repo.string());
		if (!gi.m_isGitRepository) {
			o << "Not a git repository\n\n";
		}
		else {
			o << "- Commit: " << gi.m_commit << "\n"
				<< "- Branch: " << gi.m_branch << "\n"
				<< "- Author: " << gi.m_author << "\n"
				<< "- Date: " << gi.m_date << "\n\n";
		}

	}

	bool writeCliCommands( const cli::Options& opt) {
			if (opt.showHelp) {
				std::cout << "the usage of repoctx [path..] [options]\n"
					<< "-h --help Show help\n"
					<< "-v --version Show version\n"
					<< " -o --output  Write output to file\n"
					<< " --include  Include file extensions (*.cpp,*.h)\n"
					<< " --exclude  Exclude files \n"
					<< " -r --recent  Show recently modified files \n"; //new
				return true;
			}

			if (opt.showVersion) {
				std::cout << "repoctx release 0.1\n";
				return true;
			}

			
			return false;

	}


	//Capturing cout output original_out is the pointer to the ofstream object  it saves the current cout destination
	//  then caughtOut is created for accepting the temporary  string buffer
	//later we redirect the cout to the current cout destination
	// rdbuf is useful for redirecting the code without changing the code 
	void writeFileStructure(std::ostream& o, const std::filesystem::path& path) {
		o << "Structure\n\n";
		std::streambuf* original_out = std::cout.rdbuf();
		std::ostringstream caughtOut;
		std::cout.rdbuf(caughtOut.rdbuf());

		//calling my function
		fsTravel::travelDirTree(path, 0);

		//restoring cout
		std::cout.rdbuf(original_out);
		o << caughtOut.str() << "\n\n";


	}

	

	fsTravel::TotalStatistics writeFileContents(std::ostream& o, const std::filesystem::path& path) {
		//capturing the output

		std::streambuf* original_out = std::cout.rdbuf();
		std::ostringstream caughtOut;
		std::cout.rdbuf(caughtOut.rdbuf());
		//calling the function
		auto statistics = fsTravel::travelFileContents(path);
		std::cout.rdbuf(original_out);

		o << caughtOut.str();
		o << '\n';
		return statistics;
	}


	void renderRepositoryContext(const std::string& filename, const cli::Options& opt) {
		try {
			std::ofstream fileOutput;

			std::ostream& o = targetOut(fileOutput, filename);
			for (const auto& input : opt.inputFiles) {
				const auto absolute = std::filesystem::absolute(input);
				o << "## File System Location\n\n" << absolute.string() << "\n\n";
				if (!std::filesystem::exists(absolute)) {
					std::cerr << "Error: Path does not exist: " << absolute << std::endl;
					continue;
				}
				//write git repo information
				writeGitInfo(o, absolute);
				//write file structure
				writeFileStructure(o, absolute);

				// Recent Changes Section
                if (opt.recent) {
                    o << "## Recent Changes (last 7 days)\n\n";

                    std::error_code errCode;
                    for (auto const& entry : std::filesystem::recursive_directory_iterator(absolute, errCode)) {
                        if (errCode) {
                            std::cerr << "Error accessing " << entry.path() << ": " << errCode.message() << '\n';
                            errCode.clear();
                            continue;
                        }

                        if (entry.is_regular_file() && checkingExcludeInclude(entry.path()) &&
                            isRecentlyModified(entry.path())) {

                            auto ftime = std::filesystem::last_write_time(entry.path());
                            auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
                                ftime - std::filesystem::file_time_type::clock::now() + std::chrono::system_clock::now()
                            );
                            auto age = std::chrono::duration_cast<std::chrono::hours>(
                                std::chrono::system_clock::now() - sctp
                            ).count() / 24;

                            o << "- " << std::filesystem::relative(entry.path(), absolute).string()
                              << " (" << age << " days ago)\n";
                        }
                    }
                    o << "\n";
                }

				 auto  statistics = writeFileContents(o, absolute);
				 o << "## Summary\n";
				 o << "- Total Files: " << statistics.m_totalFiles << '\n';
				 o << "- Total Lines: " << statistics.m_totalLines << '\n';
				 o << "- Total tokens: " << statistics.m_totalTokens << '\n';
			}

		}
		catch (const std::exception& err) {
			std::cerr << "Error with rendering: " << err.what() << '\n';
		}
	}

}
