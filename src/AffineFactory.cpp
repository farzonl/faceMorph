#include "AffineFactory.hpp"
#include "TriangleFactory.hpp"

void AffineFactory::createMorph(const std::vector<Triangle> &t1, 
                                const std::vector<Triangle > &t2,
                                const cv::Mat &img1, const cv::Mat &img2,
                                double dt,
                                cv::Mat &morphImg) {

    std::vector<Triangle> t;
    TriangleFactory::interpolate(t1,t2,dt,t);
    for(int i = 0; i < t1.size(); i++) {
      // Find bounding rectangle for each triangle
      cv::Rect r = boundingRect(t[i].pts);
      cv::Rect r1 = boundingRect(t1[i].pts);
      cv::Rect r2 = boundingRect(t2[i].pts);

      // Offset points by left top corner of the respective rectangles
      Triangle t1Rect, t2Rect, tRect;
      Trianglei tRectInt;
      for(int j = 0; j < 3; j++) {
          tRect[j] = cv::Point2f( t[i][j].x - r.x, t[i][j].y -  r.y);
          tRectInt[j] = cv::Point(t[i][j].x - r.x, t[i][j].y - r.y); // for fillConvexPoly

          t1Rect[j] = cv::Point2f( t1[i][j].x - r1.x, t1[i][j].y -  r1.y);
          t2Rect[j] = cv::Point2f( t2[i][j].x - r2.x, t2[i][j].y - r2.y);
      }
      // Get mask by filling triangle
      cv::Mat mask = cv::Mat::zeros(r.height, r.width, CV_32FC3);
      cv::fillConvexPoly(mask, tRectInt.pts, cv::Scalar(1.0, 1.0, 1.0), 16, 0);
      // Apply warpImage to small rectangular patches
      cv::Mat img1Rect, img2Rect;
      img1(r1).copyTo(img1Rect);
      img2(r2).copyTo(img2Rect);
      
      cv::Mat warpImage1 = cv::Mat::zeros(r.height, r.width, img1Rect.type());
      cv::Mat warpImage2 = cv::Mat::zeros(r.height, r.width, img2Rect.type());
      
      AffineFactory::affineTransform(img1Rect, t1Rect, tRect, warpImage1);
      AffineFactory::affineTransform(img2Rect, t2Rect, tRect, warpImage2);
      
      cv::Mat imgRect = (1.0 - dt) * warpImage1 + dt * warpImage2;
      //cv::Mat imgRect = warpImage1 + dt * (warpImage1 - warpImage2);
      
      // Copy triangular region of the rectangular patch to the output image
      cv::multiply(imgRect,mask, imgRect);
      cv::multiply(morphImg(r), cv::Scalar(1.0,1.0,1.0) - mask, morphImg(r));
      morphImg(r) = morphImg(r) + imgRect;
    }
}

// Apply affine transform calculated using srcTri and dstTri to src
void AffineFactory::affineTransform(const cv::Mat &src,
                                    const Triangle &srcTri,
                                    const Triangle &dstTri,
                                    cv::Mat &warpImage) {
    // find the affine transform.
    cv::Mat warpMat = cv::getAffineTransform( srcTri.pts, dstTri.pts );
    // Apply Transform to image
    cv::warpAffine( src, warpImage, warpMat, warpImage.size(), cv::INTER_LINEAR, cv::BORDER_REFLECT_101);
}