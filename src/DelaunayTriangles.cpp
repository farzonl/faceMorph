#include "DelaunayTriangles.hpp"

const std::vector<Triangle> &DelaunayTriangles::operator[](unsigned int index) const {
  if (index >= trianglesList.size()) {
        std::cerr << "Face index out of bound, exiting"; 
        exit(0); 
  }
  return trianglesList[index]; 
}

const std::vector<std::vector<Triangle>>& DelaunayTriangles::getFaces() const {
  return trianglesList;
}

bool DelaunayTriangles::init(FaceFeatureExtract &ffExtract, const cv::Mat& frame) {
  std::vector<std::vector<cv::Point2f>> landmarks;
  if(ffExtract.getFaceLandMarks(frame, landmarks)) {
    // Rectangle to be used with Subdiv2D
    cv::Size size = frame.size();
    for( std::vector<std::vector<cv::Point2f>>::iterator it = landmarks.begin(); it != landmarks.end(); it++) {
      std::vector<Triangle> triangles;
      DelaunayTriangleExtract::getTriangles(size,*it,triangles);
      trianglesList.push_back(triangles);
    }
    /*for(std::vector<std::vector<Triangle>>::iterator it = trianglesList.begin(); it != trianglesList.end(); it++) {
      std::sort(it->begin(), it->end()); 
    }*/
    return true;
  }
  return false;
}

void DelaunayTriangleExtract::draw(cv::Mat& img, const std::vector<Triangle> &triangles, cv::Scalar color) {
  cv::Size size = img.size();
  cv::Rect rect(0,0, size.width, size.height);
  for( size_t i = 0; i < triangles.size(); i++ ) {
    if (rect.contains(triangles[i].pts[0]) && 
        rect.contains(triangles[i].pts[1]) && 
        rect.contains(triangles[i].pts[2])) {
      line(img, triangles[i].pts[0], triangles[i].pts[1], color, 1, cv::LINE_AA, 0);
      line(img, triangles[i].pts[1], triangles[i].pts[2], color, 1, cv::LINE_AA, 0);
      line(img, triangles[i].pts[2], triangles[i].pts[0], color, 1, cv::LINE_AA, 0);
    }
  }
}

void DelaunayTriangleExtract::getTriangles(const cv::Size &size, 
                                           const std::vector<cv::Point2f> &faceLandMarks,
                                           std::vector<Triangle> &triangles)
{
      cv::Rect rect(0, 0, size.width, size.height);

      // Create an instance of Subdiv2D
      cv::Subdiv2D subdiv(rect);

      for(std::vector<cv::Point2f>::const_iterator it = faceLandMarks.begin(); it != faceLandMarks.end(); it++) {
        subdiv.insert(*it);
      }
      std::vector<cv::Vec6f> triangleList;
      subdiv.getTriangleList(triangleList);
      for( size_t i = 0; i < triangleList.size(); i++ ) {
        cv::Vec6f t = triangleList[i];
        Triangle triangle;
        triangle.pts[0] = cv::Point(cvRound(t[0]), cvRound(t[1]));
        triangle.pts[1] = cv::Point(cvRound(t[2]), cvRound(t[3]));
        triangle.pts[2] = cv::Point(cvRound(t[4]), cvRound(t[5]));
        if (rect.contains(triangle[0]) && 
            rect.contains(triangle[1]) && 
            rect.contains(triangle[2])) {
              triangles.push_back(triangle);
        }
      }
}
