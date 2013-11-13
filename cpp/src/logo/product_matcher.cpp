#include "product_matcher.h"

using namespace cv;

ProductMatcher::ProductMatcher(Mat& freak_descriptors, Mat& surf_descriptors, std::string& image_path) {
    this->freak_descriptors = freak_descriptors;
    this->surf_descriptors = surf_descriptors;
    this->imagebase_path = image_path;
}

// At least at first the scanning part is done on the phone, so let's just
// match with edit distance or so
double ProductMatcher::matchBarcodes() {
    return 0.0;
}

double ProductMatcher::matchLogos(MatchType match_type) {
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

    FlannBasedMatcher matcher;
    std::vector<DMatch> matches;
    if (match_type == FREAK_MATCH) matcher.match(freak_descriptors, ref_freak_descriptors, matches);
    else matcher.match(surf_descriptors, ref_surf_descriptors, matches);

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
    return good_matches.size() / matches.size();
}

// Here we can do euclidean distance of BoW representation or so
double ProductMatcher::matchBagOfWords() {
    return 0.0;
}

// Actually rethink this one
double ProductMatcher::match(MatchType match_type) {
    switch(match_type) {
        case BARCODE_MATCH:
            return matchBarcodes();
        case BAG_OF_WORDS_MATCH:
            return matchBagOfWords();
        default:
            return matchLogos(match_type);
    }
}
