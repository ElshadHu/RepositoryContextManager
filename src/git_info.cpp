#include "git_info.hpp"
#include <ctime> //for  converting timestamps into human readble format it is better because of simplicity compared to chrono


namespace gitInfo {

	bool checkRepositoryOpen(const std::string& path, git_repository** repo) {
			git_libgit2_init();//after opening we need to shut it down for avoiding memory leak
			if (git_repository_open(repo, path.c_str()) == 0) {
				return true; 
			}
			//after opening we need to shut it down for avoiding memory leak here directly shut it down
				git_libgit2_shutdown(); 
				return false;
	}

	bool getHeadReference(git_repository* repo,git_reference** headRef) {
	
		if (git_repository_head(headRef, repo) == 0)
			return true;

			return false;
	}
	bool getCommitInfo(git_repository* repo, const git_oid* oid, GitInfo& info) {

		git_commit* commit = nullptr;
		if (git_commit_lookup(&commit, repo, oid) != 0) return false;
		//getting SHA
			char sha[GIT_OID_HEXSZ + 1];
			// it is unique string via hash  we need to convert it
			git_oid_tostr(sha, sizeof(sha), oid);
			info.m_commit = sha;
			//getting author and date 
			const git_signature* author = git_commit_author(commit);
			//if it points then get the data via struct
			if (author) {
				
				info.m_author = std::string(author->name) + "< " + std::string(author->email) + " > ";
				time_t time = author->when.time;
				char* time_str = ctime(&time);
				if (time_str) {
					info.m_date = time_str;
					
					if (!info.m_date.empty() && info.m_date.back() == '\n') {
						info.m_date.pop_back();
					}
				}
			}
			//after opening  we need to make it free because of memory leaks
			git_commit_free(commit);
			return true;
	}


	GitInfo getGitData(const std::string&path) {
		GitInfo info;
		git_repository* repo = nullptr;
		if (!checkRepositoryOpen(path,&repo)) {
			git_libgit2_shutdown();
			return info;
		}
		info.m_isGitRepository = true;
		git_reference* headRef = nullptr;

		if (!getHeadReference(repo,&headRef)) {
			git_repository_free(repo);
			git_libgit2_shutdown();
			return info;
		}

		const char* branch = git_reference_shorthand(headRef);//will get us the info in a short form
		if (branch) info.m_branch = branch;

		const git_oid* oid = git_reference_target(headRef);
		getCommitInfo(repo, oid, info);

		git_reference_free(headRef);
		git_repository_free(repo);
		git_libgit2_shutdown();
		return info;
	}



}