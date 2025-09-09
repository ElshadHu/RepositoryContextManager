#include "git_info.hpp"
#include <ctime> //for  converting timestamps into human readble format it is better because of simplicity compared to chrono

//git_libgit2_init()  is written before writing other functions for global state and threading .It will return how may times it is called or error code
//git_repository_head(gith_reference**out,git_repository*reop) pointer to the reference which will be retrieved and a repository object after it is done git_reference_free should be called for memeory
//git_reference_shorthand(head_ref)     // Get branch name we dont need to free the momory it is owned by reference
//git_reference_target(head_ref)        // Get commit OID git_reference_resolve() and then this function (or maybe use git_reference_name_to_id() to directly reslove it
//git_commit_lookup(&commit, repo, oid)  // Get commit object the return object should be released with git_commit_free
//git_commit_author(commit)              // Get author signature
//git_commit_free(commit)                // Clean up commit
namespace gitInfo {

	bool checkRepositoryOpen(const std::string& path, git_repository** repo) {
			git_libgit2_init();
			if (git_repository_open(repo, path.c_str()) == 0) {
				return true;
			}
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
			git_oid_tostr(sha, sizeof(sha), oid);
			info.m_commit = sha;
			//getting author and date
			const git_signature* author = git_commit_author(commit);
			
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

		const char* branch = git_reference_shorthand(headRef);
		if (branch) info.m_branch = branch;

		const git_oid* oid = git_reference_target(headRef);
		getCommitInfo(repo, oid, info);

		git_reference_free(headRef);
		git_repository_free(repo);
		git_libgit2_shutdown();
		return info;
	}



}