#include <stdlib.h>
#include <filesystem>  
#include <iostream>

#include "response.h"
#include "locate.cpp"
#include "splice.cpp"

namespace fs = std::filesystem;

int main(int argc, char** argv) {
    // Parse args
    // (all the interesting stuff is handled in the other source files)

    // Default to -h
    if (argc < 2) {
        std::cerr << HELP << std::endl;
        return 0;
    } 

    // TODO: Clean up control flow
    const char* cmd = argv[1];
    if (!strcmp(cmd, "-h")) {
        // -h <cmd>
        if (argc < 3) {
            // General help
            std::cerr << HELP << std::endl;
        } else {
            if (!strcmp(argv[2], "s")) { std::cerr << HELP_LOCATE << std::endl; }
            else if (!strcmp(argv[2], "t")) { std::cerr << "TOUCH" << std::endl; } // TODO
            else { std::cerr << HELP << std::endl; }
        }
    } else if (!strcmp(cmd, "-v")) {
        // -v
        std::cout << VERSION << std::endl;
    } else if (!strcmp(cmd, "l")) {
        // s <target> <directory>
        if (argc < 3) {
            // Must pass target parameter
            std::cerr << "Please enter a target to search for." << std::endl;
            std::cerr << HELP_LOCATE << std::endl;
        } else {
            // Set up search parameters
            std::string target = argv[2];
            fs::path search_path;
            int max_results = 1;
            std::string mode = "f";

            if (argc == 3) { search_path = "."; } // Default search_path to cwd (.)
            else if (argc == 4) { search_path = argv[3]; } // Default max_results to 1024 matches
            else if (argc == 5) { search_path = argv[3]; max_results = atoi(argv[4]); } // Default mode to filename
            else { search_path = argv[3]; max_results = atoi(argv[4]); mode = argv[5]; }

            // Perform search, store results in vector
            std::cerr << "Searching for " << max_results << " occurence(s) of \"" << target << "\" by mode" << mode << " in path " << search_path.string() << std::endl;
            std::vector<std::string> matches = locate(target, search_path, max_results, mode);

            // Output matches
            std::cerr << "Found " << matches.size() << " result(s)" << std::endl;
            for (std::string match : matches) { std::cout << match << std::endl; }
        }
    } else if (!strcmp(cmd, "s")) {
        if (argc < 3) {
            std::cerr << "Please enter a directory to splice at." << std::endl;
            std::cerr << HELP_SPLICE << std::endl;
        } else {
            // Confirm splice operation as to minimize unwanted erasure of user data
            std::string confirm;
            std::cout << "> WARNING: Confirm splice operation. Empty directories will be deleted. Use at your own risk. (Y/n) ";
            std::cin >> confirm;
            if (confirm != "Y") { std::cerr << "Splice operation aborted early" << std::endl; return 0; }

            char rp[256];
            std::string dir = realpath(argv[2], rp);
            if (splice(dir)) {
                std::cerr << "Successfully spliced at " << dir << std::endl;
            } else {
                std::cerr << "Something went wrong while attempting to splice at " << dir << std::endl;
            }
        }
    } else {
        // Default to -h
        std::cerr << "Unknown command " << cmd << ". Try: pf -h" << std::endl;
    }

    return 0;
}