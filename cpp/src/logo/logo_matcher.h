#ifndef LOGOMATCHER_H
#define LOGOMATCHER_H

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <string>
#include <iostream>

double matchLogosFreak(std::string sent_file_path, std::string reference_image_path);
double matchLogosSurf(std::string sent_file_path, std::string reference_image_path);

#endif
