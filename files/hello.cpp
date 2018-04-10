#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv){
  Mat image;
  image = imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);
  if(! image.data ) {
      cout << "Could not open or find the image" << std::endl;
      return -1;
  }
  imshow("image", image);
  waitKey();
  return 0;
}
