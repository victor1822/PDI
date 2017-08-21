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
{	//glRotated( 90, 0.0, 0.0, 1.0 );

    for (int i = 0; i < IMAGE_WIDTH; ++i) {
        for (int j = 0; j < IMAGE_HEIGHT; ++j) {

            Vec4b& rgba = mat.at<Vec4b>(j,-(i-511));//-(j-511)
			int offset= 4*i + 4*j*IMAGE_WIDTH;	
		rgba[0] = saturate_cast<uchar>((float)FBptr[offset+2]);
		rgba[1] = saturate_cast<uchar>((float)FBptr[offset+1]);
		rgba[2] = saturate_cast<uchar>((float)FBptr[offset+0]);           
		rgba[3] = saturate_cast<uchar>(255);
		//j=j-511; j=j*(-1);
        }
    } 

}

unsigned char* readBMP(char* filename)
{
    int i;
    FILE* f = fopen("img1.bmp", "rb");
    unsigned char info[54];
    fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

    // extract image height and width from header
    int width = *(int*)&info[18];
    int height = *(int*)&info[22];

    int size = 3 * width * height;
    unsigned char* data = new unsigned char[size]; // allocate 3 bytes per pixel
    fread(data, sizeof(unsigned char), size, f); // read the rest of the data at once
    fclose(f);

    for(i = 0; i < size; i += 3)
    {
            unsigned char tmp = data[i];
            data[i] = data[i+2];
            data[i+2] = tmp;    //converter de rbg para rgb
   }

    return (unsigned char*)data;
}

#endif // BITMAPLOAD_HPP_INCLUDED
