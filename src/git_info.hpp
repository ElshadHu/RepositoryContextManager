#ifndef GIT_INFO_H
#define GIT_INFO_H
#include <filesystem>
#include <iostream>
#include <string>
#include <git2.h>


namespace fs = std::filesystem;
namespace gitInfo {
	//as a container for making clear and simpler
	struct GitInfo {
		bool m_isGitRepository = false;
		std::string m_commit;
		std::string m_branch;
		std::string m_author;
		std::string m_date;
	};
	GitInfo getGitData(const std::string&path);
	bool checkRepositoryOpen(const std::string& path, git_repository** repo);
	bool getHeadReference(git_repository* repo,git_reference**headRef);
	bool getCommitInfo(git_repository* repo, const git_oid* oid, GitInfo& info);


}

#endif