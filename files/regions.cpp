/*
author: victor cortez
This program was made to exemplify image manipulation
using C++ and opencv on a linux.
It asks for an initial and final point and reverses the
(grayscale) image in the square between the points.
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
    image = imread("biel.png", CV_LOAD_IMAGE_GRAYSCALE);
    if (!image.data)
    {
        cout << "nao abriu" << endl;
    }
    namedWindow("janela", WINDOW_AUTOSIZE);

    MyPoint pointA, pointB;
    cout << "type the x, y coordinates for point 1" << endl;
    cin >> pointA.x >> pointA.y;
    cout << "type the x, y coordinates for point 2" << endl;
    cin >> pointB.x >> pointB.y;

    for (int i = pointA.x; i < pointB.x; i++)
    {
        for (int j = pointA.y; j < pointB.y; j++)
        {
            image.at<uchar>(i, j) = 255-image.at<uchar>(i, j);
        }
    }

    imshow("janela", image);
    waitKey();
    imwrite("regionsOUT.png", image);
    waitKey();
    
    return 0;
}
