#ifndef __AFFINE__FACTORY_HPP__
#define __AFFINE__FACTORY_HPP__

#include "stdafx.h"
#include "TriangleFactory.hpp"

class AffineFactory {
  public:
    static void createMorph(const std::vector<Triangle> &t1, 
                            const std::vector<Triangle> &t2,
                            const cv::Mat &img1, const cv::Mat &img2,
                            double dt,
                            cv::Mat &morphImg);
  private:
    AffineFactory() = delete;
    static void affineTransform(const cv::Mat &src,
                                const Triangle &srcTri,
                                const Triangle &dstTri,
                                cv::Mat &warpImage);
};

#endif // __AFFINE__FACTORY_HPP__