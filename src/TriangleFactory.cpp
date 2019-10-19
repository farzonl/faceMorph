#include "TriangleFactory.hpp"


cv::Point2f TriangleFactory::lerp(cv::Point p1, cv::Point p2, float dt) {
  float x = p1.x + dt *(p2.x-p1.x);
  float y = p1.y + dt *(p2.y-p1.y);
  return cv::Point2f(x,y);
  
}

void TriangleFactory::interpolate(const std::vector<Triangle> &t1, 
                                  const std::vector<Triangle> &t2, 
                                  float dt,
                                  std::vector<Triangle> &triangles) {
  for(int i = 0; i < t1.size(); i++) {
    Triangle t;
    t.pts[0] = TriangleFactory::lerp(t1[i].pts[0], t2[i].pts[0], dt);
    t.pts[1] = TriangleFactory::lerp(t1[i].pts[1], t2[i].pts[1], dt);
    t.pts[2] = TriangleFactory::lerp(t1[i].pts[2], t2[i].pts[2], dt);
    triangles.push_back(t);
  }
}