#ifndef BITMAPLOAD_HPP_INCLUDED
#define BITMAPLOAD_HPP_INCLUDED
#include <fstream>
#include <vector>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "definitions.h"
#include <math.h>

using namespace cv;
using namespace std;

void createAlphaMat(Mat &mat)
{	

    for (int i = 0; i < IMAGE_WIDTH; ++i) {
        for (int j = 0; j < IMAGE_HEIGHT; ++j) {

            Vec4b& rgba = mat.at<Vec4b>(j,i);//-(j-511)
			int offset= 4*i + 4*j*IMAGE_WIDTH;	
		rgba[0] = saturate_cast<uchar>((float)FBptr[offset+2]);
		rgba[1] = saturate_cast<uchar>((float)FBptr[offset+1]);
		rgba[2] = saturate_cast<uchar>((float)FBptr[offset+0]);           
		rgba[3] = saturate_cast<uchar>((float)FBptr[offset+3]);
		
        }
    } 

}

unsigned char* readBMP(){
    Mat image;
	int offset;
    image = imread( "img1.bmp", 1 );
unsigned char*data = new unsigned char[4*IMAGE_WIDTH*IMAGE_HEIGHT];
		
  for (int i = 0; i < IMAGE_WIDTH; ++i) {
        for (int j = 0; j < IMAGE_HEIGHT; ++j) {
		offset=4*i+4*j*IMAGE_WIDTH;
		Point3_<uchar>* p = image.ptr<Point3_<uchar> >(i,j);

			int offset= 4*i + 4*j*IMAGE_WIDTH;	
		data[offset+0]=(unsigned char)p->z;//red
		data[offset+1]=(unsigned char)p->y;//green
		data[offset+2]=(unsigned char)p->x;//blue
		data[offset+3]=255;
		
		
        }
    }
	return (unsigned char*)data;
}

#endif // BITMAPLOAD_HPP_INCLUDED
