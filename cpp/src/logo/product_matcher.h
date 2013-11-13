#ifndef PRODUCTMATCHER_H
#define PRODUCTMATCHER_H

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <string>

enum MatchType { FREAK_MATCH, SURF_MATCH, BARCODE_MATCH, BAG_OF_WORDS_MATCH };

class ProductMatcher {
  private:
    cv::Mat freak_descriptors;
    cv::Mat surf_descriptors;
    std::string imagebase_path;

    double matchLogos(MatchType);
    double matchBarcodes();
    double matchBagOfWords();
  public:
    ProductMatcher(cv::Mat& freak_descriptors, cv::Mat& surf_desciptors, std::string& image_path);
    double match(MatchType match_type);
};

#endif
