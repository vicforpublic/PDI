/*
author: victor cortez
This program was made to swap the quadrants 1 with 4 and 2
with 3 in a grayscale image
*/

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

typedef struct
{
    int x;
    int y;
} MyPoint;

int main(int, char **)
{
    Vec3b val; //unused

    Mat image;
    image = imread("elon.png", CV_LOAD_IMAGE_GRAYSCALE);
    if (!image.data)
    {
        cout << "nao abriu" << endl;
    }
    namedWindow("janela", WINDOW_AUTOSIZE);

    cout << "the image has(h,w):" << endl;
    cout <<image.size().height << " " << image.size().width;

    //getting the first quadrant and saving in a rect structure
    //**the two ending coordinates are RELATIVE to the two
    //initial ones!
    //*the order is: columns, rows
    Rect rect = Rect(0,0, image.cols/2, image.rows/2);
    //or Rect rect(0,0, image.rows/2, image.cols/2)

    //this is actually referencing the main image. we need to COPY the roi.
    //used if we wanted to work on the original image.
    //Mat tempImg = image(rect);

    //getting a copy of the first quadrant
    Mat temp_img = image(rect).clone();

    //copy exerpt of 4th quadrant to 1st
    image(Rect(image.cols/2,image.rows/2,image.cols/2,image.rows/2))
    .copyTo(image(rect));

    //copy exerpt of 1st to 4th
    temp_img
    .copyTo(image(Rect(image.cols/2,image.rows/2,image.cols/2,image.rows/2)));

    //same with 2nd and 3rd quadrants
    rect = Rect(image.cols/2,0, image.rows/2, image.cols/2);
    temp_img = image(rect).clone();
    image(Rect(0,image.rows/2,image.cols/2,image.rows/2))
    .copyTo(image(rect));
    temp_img
    .copyTo(image(Rect(0,image.rows/2,image.cols/2,image.rows/2)));

    imshow("janela", image);
    waitKey();
    imwrite("trocaregioesOUT.png", image);

    
    return 0;
}