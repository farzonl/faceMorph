
#ifndef __TRIANGLE__FACTORY_HPP__
#define __TRIANGLE__FACTORY_HPP__

#include "stdafx.h"

template<class T=float>
class Triangle_ {
  public:
    std::vector<cv::Point_<T>> pts;
    Triangle_() : pts(3) {}
    cv::Point_<T> &operator[] (unsigned int); 
    const cv::Point_<T>& operator[](unsigned int)const;
    bool operator<( const Triangle_<T>& triangle ) const;
  private:
    void getCentroid(cv::Point_<T> & outPnt) const;
};

template<class T>
bool Triangle_<T>::operator<( const Triangle_<T>& triangle ) const{
   cv::Point_<T> a_center, b_center;
    this->getCentroid(a_center);
    triangle.getCentroid(b_center);
    if ( a_center.y != b_center.y ) {
        return a_center.y < b_center.y;
    }
    return a_center.x <= b_center.x;
}

template<class T>
void Triangle_<T>::getCentroid(cv::Point_<T> & outPnt) const{ 
        outPnt.x = (pts[0].x+pts[1].x+pts[2].x)/3.;
        outPnt.y = (pts[0].y+pts[1].y+pts[2].y)/3.;
}

template<class T>
cv::Point_<T> &Triangle_<T>::operator[](unsigned int index) {
  if (index >= 3) {
        std::cerr << "Triangle index out of bound, exiting"; 
        exit(0); 
  }
  return pts[index]; 
}

template<class T>
const cv::Point_<T> &Triangle_<T>::operator[](unsigned int index) const {
  if (index >= 3) {
        std::cerr << "Triangle index out of bound, exiting"; 
        exit(0); 
  }
  return pts[index]; 
}

typedef Triangle_<float> Trianglef;
typedef Triangle_<int> Trianglei;
typedef Trianglef Triangle;

class TriangleFactory {
  public:
    static void interpolate(const std::vector<Triangle> &t1,
                      const std::vector<Triangle> &t2,
                      float dt,
                      std::vector<Triangle> &alphaTri);
  private:
    static cv::Point2f lerp(cv::Point p1, cv::Point p2, float dt);
    TriangleFactory() = delete;
};


#endif // __TRIANGLE__FACTORY_HPP__