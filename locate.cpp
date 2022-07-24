#ifndef SEARCH_CPP_
#define SEARCH_CPP_

#include <filesystem>
#include <string>
#include <vector>
#include <queue>
#include <iostream>

namespace fs = std::filesystem;

// Perform BFS to locate matches to target
std::vector<std::string> locate(
    std::string target,
    const fs::path& search_path = ".",
    int max_matches = 1,
    std::string mode = "-f"
) {

    // Declare vector to store matches and reserve appropriate size
    std::vector<std::string> matches;
    matches.reserve(max_matches);

    // Initialize queue with given path
    std::queue<fs::path> q;
    q.push(search_path);

    try {
        while (!q.empty() && matches.size() < max_matches) {
            // Serve first element
            fs::path curr = q.front();
            q.pop();

            // Iterate over entries in directory
            bool match = false;
            for (const fs::directory_entry& entry : fs::directory_iterator(curr, fs::directory_options::skip_permission_denied)) {
                if (entry.is_directory()) {
                    // Push directories to end of queue
                    q.push(entry);
                }

                // Match files to target based on mode
                // I wanted to use enum but it was a hassle to convert argv element to enum type
                else if (entry.is_regular_file()) {
                    if (mode == "-x") {
                        // Extension
                        std::string extension_str = entry.path().extension().string();
                        match = (extension_str == target);
                    } else {
                        // Default to mode flag == "-f"
                        // Filename
                        std::string filename_str = entry.path().filename().string();
                        match = (filename_str == target);
                    }

                    if (match) {
                        // TODO: Handle duplicates matched through symlinks
                        // Push matching file path to matches vector
                        std::string path_str = fs::relative(entry.path(), search_path).string();
                        matches.push_back(path_str);
                    }
                }
            }
        }
    }
    catch (const fs::filesystem_error& err) {
        std::cerr << err.what() << '\n';
    }

    return matches;
}

#endif // SEARCH_CPP_