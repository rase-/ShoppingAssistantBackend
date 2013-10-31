#ifndef PRODUCTFINDER_H
#define PRODUCTFINDER_H

#include <string>
#include "product_matcher.h"
#include <vector>

class ProductFinder  {
  private:
    std::string image_folder_path;
    cv::Mat freak_descriptors;
    cv::Mat surf_descriptors;

    std::vector<std::string> findFiles(std::string path);
  public:
    ProductFinder(cv::Mat& freak_descriptors, cv::Mat& surf_descriptors, std::string);
    void findTopMatches(int k);
};

#endif
