#include <fmorph.h>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <unistd.h>

int main(int argc,char** argv) {
  cv::Mat frame1, frame2;
  FaceFeatureExtract ffExtract;
  if(argc != 3) {
    cv::VideoCapture cam(0);
    std::cout << "Press any key to taking a picture and continue" << std::endl; 
    getchar();

    cam.read(frame1);


    std::cout << "Press any key to taking a picture and continue" << std::endl; 
    getchar();

    cam.read(frame2);
  } else {
    frame1 = cv::imread(argv[1], cv::IMREAD_COLOR);
    frame2 = cv::imread(argv[2], cv::IMREAD_COLOR);
  }

  DelaunayTriangles f1Triangles;
  DelaunayTriangles f2Triangles;

  if ( !( f1Triangles.init(ffExtract, frame1) && f2Triangles.init(ffExtract, frame2)) ) {
    return -1;
  }
  cv::Mat frame1_orig = frame1.clone();
  cv::Mat frame2_orig = frame2.clone();
  //convert Mat to float data type
  frame1.convertTo(frame1, CV_32F);
  frame2.convertTo(frame2, CV_32F);
  std::vector<cv::Mat> morphFrames;
  for(double dt = 0.0; dt <= 1.0; dt+=.01) {
    cv::Mat morphFrame = cv::Mat::zeros(frame1.size(), CV_32FC3);
    AffineFactory::createMorph(f1Triangles[0], f2Triangles[0], frame1, frame2, dt, morphFrame);
    morphFrames.push_back(morphFrame  / 255.0);
  }
  int count = 0;
  std::cout <<  "# of frames: " << morphFrames.size() << std::endl;
  cv::Scalar triColor(255,0,255);
  DelaunayTriangleExtract::draw(frame1_orig,f1Triangles[0],triColor);
  DelaunayTriangleExtract::draw(frame2_orig,f2Triangles[0],triColor);
  imshow("picture 1", frame1_orig);
  imshow("picture 2", frame2_orig);
  while(true) {
    if(count == 1) {
      usleep(1000000);
    }
    if(count == morphFrames.size()) {
      usleep(1000000);
      count = 0;
    }
    imshow("morph", morphFrames[count]);
    count++;
    if (cv::waitKey(1) == 27) break;
  }

}
