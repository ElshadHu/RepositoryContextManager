#include "filter.hpp"

namespace Filter {

	FilterManager::FilterManager(const cli::Options& opt):config(opt) {}


	
	bool FilterManager::checkingExcludeInclude(const std::filesystem::path& filepath) const {
		if (!std::filesystem::exists(filepath) || isGitIgnored(filepath))
			return false;

		if (!config.includePattern.empty() && config.onIncludeFilter && !config.onIncludeFilter(filepath)) {
			return false;
		}
		if (!config.excludePattern.empty() && config.onExcludeFilter && config.onExcludeFilter(filepath)) {
			return false;
		}
		if (config.recent && config.onRecentFilter && !config.onRecentFilter(filepath)) {
			return false;
		}

		return true;
	}

}