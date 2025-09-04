#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc > 1 && (std::string(argv[1]) == "-v" || std::string(argv[1]) == "--version")) {
        std::cout << "RepositoryContextManager v0.1\n";
        return 0;
    }

	std::cout << "reportx running..\n";
}