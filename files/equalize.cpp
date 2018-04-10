#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv){
  Mat image;
  int width, height;
  vector<Mat> planes;
  int nbins = 64;
  float range[] = {0, 256};
  const float *histrange = { range };
  bool uniform = true;
  bool acummulate = false;

    image = imread("elon.png", CV_LOAD_IMAGE_GRAYSCALE);
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
  //equalization for one channel
  Mat histImg(histh, histw, CV_8UC1, Scalar(0,0,0));
  Mat histImgEQ(histh, histw, CV_8UC1, Scalar(0,0,0));
  Mat eq;
  equalizeHist(image, eq);
  Mat hist, histEQ;
    calcHist(&image, 1, 0, Mat(), hist, 1,
             &nbins, &histrange,
             uniform, acummulate);
    calcHist(&eq, 1, 0, Mat(), histEQ, 1,
             &nbins, &histrange,
             uniform, acummulate);

    cout << "chegou aqui";

    normalize(hist, hist, 0, histImg.rows, NORM_MINMAX, -1, Mat());
    normalize(histEQ, histEQ, 0, histImgEQ.rows, NORM_MINMAX, -1, Mat());

    histImg.setTo(Scalar(0));
    histImgEQ.setTo(Scalar(0));
    
    for(int i=0; i<nbins; i++){
      line(histImg,
           Point(i, histh),
           Point(i, histh-cvRound(hist.at<float>(i))),
           Scalar(255), 1, 8, 0);
      line(histImgEQ,
           Point(i, histh),
           Point(i, histh-cvRound(histEQ.at<float>(i))),
           Scalar(255), 1, 8, 0);
    }
    histImg.copyTo(image(Rect(0, 0       ,nbins, histh)));
    histImgEQ.copyTo(eq(Rect(0, histh   ,nbins, histh)));
    imshow("image", image);
    imshow("eq", eq);
    imwrite("equalize.png", image);
    imwrite("equalizeeq.png", eq);
    waitKey();

  return 0;
}
