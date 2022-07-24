#include <filesystem>  
#include <iostream>

#include "response.h"
#include "search.cpp"

namespace fs = std::filesystem;

int main(int argc, char** argv) {
    // Parse args (All the interesting stuff is handled in the other source files)

    // Default to -h
    if (argc < 2) {
        std::cout << HELP << std::endl;
        return 0;
    } 

    // TODO: Clean up control flow
    const char* cmd = argv[1];
    if (!strcmp(cmd, "-h")) {
    // -h <cmd>
        if (argc < 3) {
            // General help
            std::cout << HELP << std::endl;
        } else {
            if (!strcmp(argv[2], "s")) { std::cout << HELP_SEARCH << std::endl; }
            else if (!strcmp(argv[2], "t")) { std::cout << "TOUCH" << std::endl; } // TODO
            else { std::cout << HELP << std::endl; }
        }
    } else if (!strcmp(cmd, "-v")) {
        // -v
        std::cout << VERSION << std::endl;
    } else if (!strcmp(cmd, "s")) {
        // s <target> <directory>
        if (argc < 3) {
            // Must pass target parameter
            std::cout << "Please enter a target to search for." << std::endl;
            std::cout << HELP_SEARCH << std::endl;
        } else {
            // Set up search parameters
            std::string target = argv[2];
            fs::path search_path;
            int max_results = 256;

            if (argc == 3) { search_path = "."; } // Default search_path to cwd (.)
            else if (argc == 4) { search_path = argv[3]; } // Default max_results to 1024 matches
            else { search_path = argv[3]; max_results = atoi(argv[4]); }

            // Perform search, store results in vector
            std::cout << "Searching for " << max_results << " occurences of \"" << target << "\" in path " << search_path.string() << std::endl;
            std::vector<std::string> matches = search(target, search_path, max_results);

            // Output matches
            std::cout << "Found " << matches.size() << " result(s)" << std::endl;
            for (std::string match : matches) {
                std::cout << match << std::endl;
            }
        }
    } else if (!strcmp(cmd, "t")) {
        // TODO: Implement touch
    } else {
        // Default to -h
        std::cout << "Unknown command " << cmd << ". Try: pf -h" << std::endl;
    }

    return 0;
}