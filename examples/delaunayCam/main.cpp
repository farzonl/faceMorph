#include <fmorph.h>
#include <opencv2/highgui/highgui.hpp>


int main(int argc,char** argv)
{
    cv::Scalar triColor(255,0,255);
    // Set up webcam for video capture
    cv::VideoCapture cam(0);
    
    // Variable to store a video frame and its grayscale 
    cv::Mat frame;
    FaceFeatureExtract ffExtract;
    // Read a frame
    while(cam.read(frame))
    { 
      std::vector<std::vector<cv::Point2f>> landmarks;
      if(ffExtract.getFaceLandMarks(frame, landmarks)) {
        // Rectangle to be used with Subdiv2D
        cv::Size size = frame.size();
        std::vector<std::vector<Triangle>> trianglesList;
        for( std::vector<std::vector<cv::Point2f>>::iterator it = landmarks.begin(); it != landmarks.end(); it++) {
          std::vector<Triangle> triangles;
          DelaunayTriangleExtract::getTriangles(size,*it,triangles);
          trianglesList.push_back(triangles);
        }

        for(std::vector<std::vector<Triangle>>::iterator it = trianglesList.begin(); it != trianglesList.end(); it++) {
          DelaunayTriangleExtract::draw(frame,*it,triColor);
        }
      }
      imshow("delaunay", frame);
      // Exit loop if ESC is pressed
      if (cv::waitKey(1) == 27) break;
    }
    return 0;
}
