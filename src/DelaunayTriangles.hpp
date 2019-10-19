#ifndef __Delaunay_TRIANGLE_HPP__
#define __Delaunay_TRIANGLE_HPP__

#include "stdafx.h"
#include "TriangleFactory.hpp"
#include "FaceFeatureExtract.hpp"

class DelaunayTriangleExtract {
  public:
    static void getTriangles(const cv::Size &size, 
                             const std::vector<cv::Point2f> &faceLandMarks,
                             std::vector<Triangle> &triangles);

    static void draw(cv::Mat& img, const std::vector<Triangle> &triangles, cv::Scalar color);
  private:
    DelaunayTriangleExtract() = delete;
};

class DelaunayTriangles {
  public:
    bool init(FaceFeatureExtract &ffExtract, const cv::Mat& frame);
    const std::vector<std::vector<Triangle>>& getFaces() const;
    const std::vector<Triangle>& operator[](unsigned int)const;
  private:
    std::vector<std::vector<Triangle>> trianglesList;
};

#endif //__Delaunay_TRIANGLE_HPP__
