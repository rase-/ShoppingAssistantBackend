#include "product_matcher.h"

using namespace cv;

ProductMatcher::ProductMatcher(cv::Mat& freak_descriptors, cv::Mat& surf_descriptors, std::string& image_path) {
    this->freak_descriptors = freak_descriptors;
    this->surf_descriptors = surf_descriptors;
    this->imagebase_path = image_path;
}

// Actually rethink this one
double ProductMatcher::match() {
    Mat reference = imread(imagebase_path);
    SurfFeatureDetector detector (400);
    SurfDescriptorExtractor extractor;
    FREAK freak;
    vector<KeyPoint> keypoints;
    detector.detect(reference, keypoints);
    Mat ref_surf_descriptors;
    Mat ref_freak_descriptors;
    extractor.compute(reference, keypoints, ref_surf_descriptors);
    freak.compute(reference, keypoints, ref_freak_descriptors);

    cv::FlannBasedMatcher matcher;
    std::vector<cv::DMatch> matches;
    matcher.match(freak_descriptors, ref_freak_descriptors, matches);

    double max_dist = 0, min_dist = 100;
    for (int i = 0; i < freak_descriptors.rows; i++) {
        double dist = matches[i].distance;
        max_dist = (dist > max_dist) ? dist : max_dist;
        min_dist = (dist < min_dist) ? dist : min_dist;
    }

    std::vector<cv::DMatch> good_matches;
    for (int i = 0; i < freak_descriptors.rows; i++) {
        if (matches[i].distance <= 2*min_dist)
            good_matches.push_back(matches[i]);
    }

    // The ratio of good matches to all matches is the confidence estimate
    // we've got
    double confidence = good_matches.size() / matches.size(); 

    return confidence;
}

void ProductMatcher::loadProductInfo() {
    // Load from assets folder or something
}
