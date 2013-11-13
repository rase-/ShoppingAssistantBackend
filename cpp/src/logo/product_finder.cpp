#include "product_finder.h"
#include <dirent.h>

ProductFinder::ProductFinder(cv::Mat& freak_descriptors, cv::Mat& surf_descriptors, std::string image_folder_path) {
    this->image_folder_path = image_folder_path;
}

std::vector<std::string> ProductFinder::findFiles(std::string path) {
    DIR* dir;
    dir = opendir(image_folder_path.c_str());
    struct dirent* entry;
    std::vector<std::string> files;
    while ((entry = readdir(dir))) {
        files.push_back(std::string(entry->d_name));                
    }
    closedir(dir);
    return files;
}

void ProductFinder::findTopMatches(int k) {
    std::vector<std::string> file_names = findFiles(image_folder_path);
    for (size_t i = 0; i < file_names.size(); i++) {
        ProductMatcher p_matcher(freak_descriptors, surf_descriptors, file_names[i]);
        double confidence = p_matcher.match(FREAK_MATCH);
    }
    // return top k
}
