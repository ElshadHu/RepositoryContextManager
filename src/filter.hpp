#ifndef FILTER_HPP
#define FILTER_HPP
#include <filesystem>
#include <array>
#include <algorithm>
#include <chrono>
#include <iostream>
#include "cli.hpp"
#include "utils.hpp"

namespace Filter {
	class FilterManager {
		const cli::Options& config;

	public:
		FilterManager(const cli::Options& opt);
		bool checkingExcludeInclude(const std::filesystem::path& filepath) const;

	};

}



#endif
