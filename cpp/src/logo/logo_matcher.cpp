#include "logo_matcher.h"
using namespace cv;

double matchLogosFreak(std::string sent_file_path, std::string reference_image_path) {
    Mat sent = imread(sent_file_path);
    Mat reference = imread(reference_image_path);

    SurfFeatureDetector detector (400);
    FREAK freak;

    vector<KeyPoint> sent_keypoints;
    vector<KeyPoint> reference_keypoints;

    detector.detect(sent, sent_keypoints);
    detector.detect(reference, reference_keypoints);

    Mat sent_descriptors;
    Mat reference_descriptors;
    freak.compute(sent, sent_keypoints, sent_descriptors);
    freak.compute(reference, reference_keypoints, reference_descriptors);

    //FlannBasedMatcher matcher;
    //std::vector<DMatch> matches;
    //matcher.match(sent_descriptors, reference_descriptors, matches);
    //
    //double max_dist = 0, min_dist = 100;
    //for (int i = 0; i < sent_descriptors.rows; i++) {
    //    double dist = matches[i].distance;
    //    max_dist = (dist > max_dist) ? dist : max_dist;
    //    min_dist = (dist < min_dist) ? dist : min_dist;
    //}

    //std::vector<DMatch> good_matches;
    //for (int i = 0; i < sent_descriptors.rows; i++) {
    //    if (matches[i].distance <= 2*min_dist) {
    //        good_matches.push_back(matches[i]);
    //    }
    //}

    //return good_matches.size() * 1.0 / matches.size();
    return 0.0;
}

double matchLogosSurf(std::string sent_file_path, std::string reference_image_path) {
    Mat sent = imread(sent_file_path);
    Mat reference = imread(reference_image_path);

    SurfFeatureDetector detector (400);
    SurfDescriptorExtractor surf;

    vector<KeyPoint> sent_keypoints;
    vector<KeyPoint> reference_keypoints;

    detector.detect(sent, sent_keypoints);
    detector.detect(reference, reference_keypoints);

    Mat sent_descriptors;
    Mat reference_descriptors;
    surf.compute(sent, sent_keypoints, sent_descriptors);
    surf.compute(reference, reference_keypoints, reference_descriptors);

    FlannBasedMatcher matcher;
    std::vector<DMatch> matches;
    matcher.match(sent_descriptors, reference_descriptors, matches);
    
    double max_dist = 0, min_dist = 100;
    for (int i = 0; i < sent_descriptors.rows; i++) {
        double dist = matches[i].distance;
        max_dist = (dist > max_dist) ? dist : max_dist;
        min_dist = (dist < min_dist) ? dist : min_dist;
    }

    std::vector<DMatch> good_matches;
    for (int i = 0; i < sent_descriptors.rows; i++) {
        if (matches[i].distance <= 2*min_dist) {
            good_matches.push_back(matches[i]);
        }
    }

    return good_matches.size() * 1.0 / matches.size();
}
