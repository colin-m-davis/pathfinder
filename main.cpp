#include <filesystem>  
#include <iostream>
#include <queue>

#include "response.h"

namespace fs = std::filesystem;

std::vector<std::string> search(std::string target, const fs::path& search_path, int max_matches = 256) {
    // Declare vector to store matches and reserve appropriate size
    std::vector<std::string> matches;
    matches.reserve(max_matches);

    // Initialize queue with given path
    std::queue<fs::path> q;
    q.push(search_path);

    // Perform BFS on search_path
    try {
        while (!q.empty() && matches.size() < max_matches) {
            fs::path curr = q.front();
            q.pop();
            for (const fs::directory_entry& entry : fs::directory_iterator(curr, fs::directory_options::skip_permission_denied)) {
                if (entry.is_directory()) {
                    // Push any directories to end of queue
                    q.push(entry);
                }
                else if (entry.is_regular_file()) {
                    // Push any matching files to matches vector
                    std::string filename_str = entry.path().filename().string();
                    std::string path_str = entry.path().string();
                    if (filename_str == target) {
                        matches.push_back(path_str); }
                }
            }
        }
    }
    catch (const fs::filesystem_error& err) {
        std::cerr << err.what() << '\n';
    }

    return matches;
}

int main(int argc, char** argv) {
    // Parse argv

    // Default to -h
    if (argc < 2) {
        std::cout << HELP << std::endl;
    } else {

    }

    const char* cmd = argv[1];
    // -h <cmd>
    if (!strcmp(cmd, "-h")) {
        // General help
        if (argc < 3) {

        }
        // Command help
        else {

        }
        std::cout << HELP << std::endl;
    }
    // -v
    else if (!strcmp(cmd, "-v")) {
        std::cout << VERSION << std::endl;
    }
    // s <target> <directory>
    else if (!strcmp(cmd, "s")) {
        std::cout << "SEARCH" << std::endl;
        if (argc < 3) {
            // Must pass target parameter
            std::cout << "Please enter a target to search for" << std::endl;
            std::cout << HELP_SEARCH << std::endl;
        } else {
            // Set up search parameters
            std::string target = argv[2];
            fs::path search_path;
            int max_results = 256;

            if (argc == 3) { search_path = "."; } // Default to current directory
            else if (argc == 4) { search_path = argv[3]; } // Default to 1024 matches
            else { search_path = argv[3]; max_results = atoi(argv[4]); }

            // Perform search, store results in vector
            std::cout << "Searching for " << max_results << " occurences of \"" << target << "\" in path " << search_path.string() << std::endl;
            std::vector<std::string> matches = search(target, search_path);

            // Output matches
            std::cout << "Found " << matches.size() << " result(s)" << std::endl;
            for (std::string match : matches) {
                std::cout << match << std::endl;
            }
        }
    }
    // Default to -h
    else {
        std::cout << HELP << std::endl;
    }

    return 50;
}