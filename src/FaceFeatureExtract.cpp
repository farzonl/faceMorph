#include "FaceFeatureExtract.hpp"

FaceFeatureExtract::FaceFeatureExtract() :
    // Load Face Detector
    faceDetector(cv::CascadeClassifier("haarcascade_frontalface_alt2.xml")) {
  // Create an instance of Facemark
  facemark = cv::face::FacemarkLBF::create();
  // Load landmark detector
  facemark->loadModel("lbfmodel.yaml");
}

bool FaceFeatureExtract::getFaceLandMarks(const cv::Mat &frame, 
                                          std::vector<std::vector<cv::Point2f> > &landmarks) {
  cv::Mat gray;
  cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

  // Find faces
  std::vector<cv::Rect> faces;
  faceDetector.detectMultiScale(gray, faces);

  return facemark->fit(frame,faces,landmarks);
}