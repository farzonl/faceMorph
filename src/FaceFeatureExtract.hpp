#ifndef __FACE__FEATURE_EXTRACT_HPP__
#define __FACE__FEATURE_EXTRACT_HPP__

#include "stdafx.h"
#include <opencv2/face.hpp>

class FaceFeatureExtract {
  private:
    cv::Ptr<cv::face::Facemark> facemark;
    cv::CascadeClassifier faceDetector;
  public:
    FaceFeatureExtract();
    bool getFaceLandMarks(const cv::Mat &frame, 
                          std::vector<std::vector<cv::Point2f> > &landmarks);
};

#endif // __FACE__FEATURE_EXTRACT_HPP__
