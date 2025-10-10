#ifndef FILTER_HPP
#define FILTER_HPP
#include <filesystem>
#include <iostream>
#include "cli.hpp"
#include "utils.hpp"

namespace Filter {
	class FilterManager {
		const cli::Options& config;

	public:
		FilterManager(const cli::Options& opt);
		bool isMatchingFilters(const std::filesystem::path& filepath) const;

	};

}



#endif
