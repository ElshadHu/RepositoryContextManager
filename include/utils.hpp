#pragma once
#include <iostream>
#include <filesystem>
#include <string>
#include <string_view>
#include <array>
#include <algorithm>


 bool isExcludedDirectory(const std::filesystem::path& p);
 bool isExcludedFile(const std::filesystem::path& p);
 bool allowedExtensions(const std::string& ext);
 const std::string getLanguageExtension(const std::string& ext);
 std::filesystem::path findGitRepository(const std::filesystem::path& beginPath);