#pragma once
#include <bits/stdc++.h>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

//深度值转伪彩
void makeColorTbl(uint8_t Rainbow[][65536])
{
    int smax = 5000, smin = 0;
    int imMax = smax;
    int srange = 1020;
    double dsrange = (double)srange;
    for (int i = 0; i < imMax * 2 - 2; i++)
    {
        short ii;
        if (((double)(i - smin) / (double)(smax - smin)) * dsrange > dsrange + 512) ii = srange + 512;
        else ii = (short)(((double)(i - smin) / (double)(smax - smin)) * dsrange) + 255;

        if (ii < 0)
        {
            Rainbow[0][i] = 255; Rainbow[1][i] = 255; Rainbow[2][i] = 255;
        }
        else if (ii < 255)
        {
            Rainbow[0][i] = 255; Rainbow[1][i] = 255; Rainbow[2][i] = 255;
        }
        else if (ii < 511)
        {
            Rainbow[0][i] = (char)(0); Rainbow[1][i] = (char)(ii - 255); Rainbow[2][i] = (char)(255);
        }
        else if (ii < 766)
        {
            Rainbow[0][i] = (char)(0); Rainbow[1][i] = (char)(255); Rainbow[2][i] = (char)(765 - ii);
        }
        else if (ii < 1021)
        {
            Rainbow[0][i] = (char)(ii - 765); Rainbow[1][i] = (char)(255); Rainbow[2][i] = (char)(0);
        }
        else if (ii < 1276)
        {
            Rainbow[0][i] = (char)(255); Rainbow[1][i] = (char)(1275 - ii); Rainbow[2][i] = (char)(0);
        }
        else
        {
            Rainbow[0][i] = 0; Rainbow[1][i] = 0; Rainbow[2][i] = 0;
        }
        //printf("i %d ii %d, Rainbow_R %x, Rainbow_G %x, Rainbow_B %x\n", i, ii,Rainbow[0][i], Rainbow[1][i], Rainbow[2][i]);
    }
    
    //immax=5000
    for (int i = imMax * 2 - 2; i < 65536; i++)
    {
        Rainbow[0][i] = 0; Rainbow[1][i] = 0; Rainbow[2][i] = 0;
    }

    for (int i = 0; i < smin; i++)
    {
        Rainbow[0][i] = 255; Rainbow[1][i] = 255; Rainbow[2][i] = 255;
    }
    //smxa=5000
    for (int i = smax; i < 65536; i++)
    {
        //Rainbow[1][i]原来是0，此时背景是黑的，我改为了255，背景变绿
        Rainbow[0][i] = 0; Rainbow[1][i] = 255; Rainbow[2][i] = 0;
    }
    
}

Mat getMat(int depth[], uint8_t Rainbow[][65536]) {
    //240*320,无符号8位，3通道
    Mat image = Mat(240, 320, CV_8UC3);
    for (int row = 0; row < 240; row++) {
        for (int col = 0; col < 320; col++) {
            //printf("depth[75018]=%d\n", depth[75018]);
            //printf("depth[%d]=%d\n", row * 320 + col, depth[row * 320 + col]);
            image.at<Vec3b>(row, col)[0] = Rainbow[0][depth[row * 320 + col]];//R值
            image.at<Vec3b>(row, col)[1] = Rainbow[1][depth[row * 320 + col]];//G值
            image.at<Vec3b>(row, col)[2] = Rainbow[2][depth[row * 320 + col]];//B值
        }
    }
    return image;
}
