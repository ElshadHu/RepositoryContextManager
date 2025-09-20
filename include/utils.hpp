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

void setFiltering(const std::string& include, const std::string& exclude);
 bool excludedExtensions(const std::string& filepath, const std::string& excludedExtension);
 bool checkingExcludeInclude(const std::filesystem::path& filepath);
 const std::string getLanguageExtension(const std::string& ext);
 std::filesystem::path findGitRepository(const std::filesystem::path& beginPath);
 std::size_t countLines(const std::filesystem::path& filepath);
 std::size_t countTokens(const std::filesystem::path& filePath);
 bool onlyIncludedExtensions(const std::string& extension,const std::string&includedFiles);
 bool isGitIgnored(const std::filesystem::path& filePath);
 bool matchingFileDir(const std::string& path, const std::string& filter);
 bool isRecentlyModified(const std::filesystem::path& filePath, int days = 7); // new

 static bool m_recentOnly = false; // new