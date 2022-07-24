#ifndef SEARCH_CPP_
#define SEARCH_CPP_

#include <filesystem>
#include <string>
#include <vector>
#include <queue>
#include <iostream>

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
            // Serve first element
            fs::path curr = q.front();
            q.pop();

            // Iterate over entries in directory
            for (const fs::directory_entry& entry : fs::directory_iterator(curr, fs::directory_options::skip_permission_denied)) {
                std::cout << "\33[2K\r Searching " << entry.path() << "\r";
                if (entry.is_directory()) {
                    // Push directories to end of queue
                    q.push(entry);
                }
                else if (entry.is_regular_file()) {
                    // Match files in directory to target
                    std::string filename_str = entry.path().filename().string();
                    if (filename_str == target) {
                        // Push matching file path to matches vector
                        std::string path_str = fs::relative(entry.path(), search_path).string();
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

#endif // SEARCH_CPP_