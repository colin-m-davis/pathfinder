#ifndef SPLICE_CPP_
#define SPLICE_CPP_

#include <filesystem>
#include <string>
#include <iostream>

namespace fs = std::filesystem;

// Copies directory contents to parent before removing directory.
bool splice(const fs::path& dir) {
    if (!fs::is_directory(dir)) {
        // Entry is not a directory (e.g. is a file)
        std::cerr << "Unable splice--entry is not a directory." << std::endl;
        return false;
    } else if (!dir.has_parent_path()) {
        // Directory has no parent (e.g. root directory)
        std::cerr << "Unable to splice--directory has no parent." << std::endl;
        return false;
    }

    fs::path parent_path = dir.parent_path();
    try {
        // Copy each entry in dir to its parent
        std::cerr << "Copying contents to parent " << parent_path << "..." << std::endl;
        int i = 0; // Record # entries copied
        for (const fs::directory_entry& entry : fs::directory_iterator(dir)) {
            std::error_code e;
            if (e) { std::cerr << "Unable to splice--could not copy " << entry.path().string() << ": " << e << std::endl; return false; }
            i++;
        }
        // Delete directory
        std::cerr << i << "entries copied to parent. Deleting directory..." << std::endl;
        fs::remove_all(dir);

    } catch (const fs::filesystem_error& err) {
        std::cerr << err.what() << '\n';
        return false;
    }

    return true;
}

#endif // SPLICE_CPP_