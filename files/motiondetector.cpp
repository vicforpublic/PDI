#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

bool motionDetected(Mat beforeHist, Mat afterHist){

  //comparing histogram based on correlation.
  double correl = compareHist(beforeHist, afterHist, CV_COMP_CORREL);
  cout << correl << endl;
  if(correl < 0.98){
    return true;
  }else{
    return false;
  }

  
}

int main(int argc, char** argv){
  Mat image,oldImage;
  int width, height;
  vector<Mat> planes;
  int nbins = 64;
  float range[] = {0, 256};
  const float *histrange = { range };
  bool uniform = true;
  bool acummulate = false;

//com uma webcam estariamos comparando o frame anterior
//neste caso estamos comparando duas imagens.
    oldImage = imread("elon.png", CV_LOAD_IMAGE_GRAYSCALE);
    if (!oldImage.data)
    {
        cout << "nao abriu" << endl;
    }
    image = imread("equalizeeq.png", CV_LOAD_IMAGE_GRAYSCALE);
    if (!image.data)
    {
        cout << "nao abriu" << endl;
    }
    namedWindow("janela", WINDOW_AUTOSIZE);  
  
  width  = image.size().width;
  height = image.size().height;

  cout << "largura = " << width << endl;
  cout << "altura  = " << height << endl;

  int histw = nbins, histh = nbins/2;
  
  Mat histImg(histh, histw, CV_8UC1, Scalar(0,0,0));
  Mat hist, oldHist;
  calcHist(&image, 1, 0, Mat(), hist, 1,
             &nbins, &histrange,
             uniform, acummulate);
  

  normalize(hist, hist, 0, histImg.rows, NORM_MINMAX, -1, Mat());
  calcHist(&oldImage, 1, 0, Mat(), oldHist, 1,
             &nbins, &histrange,
             uniform, acummulate);

  normalize(oldHist, oldHist, 0, histImg.rows, NORM_MINMAX, -1, Mat());

  histImg.setTo(Scalar(0));

  for(int i=0; i<nbins; i++){
      line(histImg,
           Point(i, histh),
           Point(i, histh-cvRound(hist.at<float>(i))),
           Scalar(255), 1, 8, 0);
    }
    histImg.copyTo(image(Rect(0, 0       ,nbins, histh)));


    //at the end of the printing process, check if the two images
    //correlate.
    if(motionDetected(hist, oldHist)){
      cout << "ALARM"<<endl;
    }
  return 0;
}
