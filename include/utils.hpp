#pragma once
#include <iostream>
#include <filesystem>
#include <string>
#include <string_view>
#include <array>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <chrono>
#include "cli.hpp"

constexpr size_t MAX_SIZE_FILE = 16234;
constexpr  int DEFAULT_RECENT_DAYS = 7;

bool isRecentlyModified(const std::filesystem::path& filepath, int days = DEFAULT_RECENT_DAYS);
bool isGitIgnored(const std::filesystem::path& filePath) ;
 bool excludedExtensions(const std::string& filepath, const std::string& excludedExtension);
 const std::string getLanguageExtension(const std::string& ext);
 std::filesystem::path findGitRepository(const std::filesystem::path& beginPath);
 std::size_t countLines(const std::filesystem::path& filepath);
 bool onlyIncludedExtensions(const std::string& extension,const std::string&includedFiles);
 bool matchingFileDir(const std::string& path, const std::string& filter);
 void readDisplayFile(const std::filesystem::path& filepath);
 std::uintmax_t getFileSize(const std::filesystem::path& filepath); 
 void showHelp();
 void showVersion();

