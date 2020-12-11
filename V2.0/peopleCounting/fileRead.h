#pragma once
#include<bits/stdc++.h>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;

int depth[320 * 240] = { 0 };
string videoPath = "F:\\TOF_NumberOfPeople\\Frame2.mp4"; //伪彩视频所在地址
string framesFilePath = "F:\\TOF_NumberOfPeople\\framsofFrame2"; //伪彩视频帧所在地址
string depthDatasPath = "F:\\TOF_NumberOfPeople\\Frame2"; //深度数据所在地址
//截下该视频的每一帧并存放在特定路径,并返回视频的总帧数
double getFrames(String videoPath) {
	VideoCapture cap;
	cap.open(videoPath);
	if (!cap.isOpened()) {
		cout << "视频打开失败！";
		exit(-1);
	}

	double frames = cap.get(CAP_PROP_FRAME_COUNT); //视频的总帧数
	//double width = cap.get(CAP_PROP_FRAME_WIDTH); //视频帧的宽度
	//double hight = cap.get(CAP_PROP_FRAME_HEIGHT); //视频帧的高度
	Mat frame;
	for (int i = 0; i < frames; i++) {
		if (!cap.read(frame)) cout << "视频读取失败！";
		String path = framesFilePath + to_string(i + 1) + ".jpg"; //文件的取名得规范，得含有原视频的信息
		imwrite(path, frame);
	}
	cap.release();
	return frames;
}

//得到视频帧的高度
int getVideoHight(string videoPath) {
	VideoCapture cap;
	cap.open(videoPath);
	return cap.get(CAP_PROP_FRAME_HEIGHT); //视频帧的高度
}

//得到视频帧的宽度
int getVideoWidth(string videoPath) {
	VideoCapture cap;
	cap.open(videoPath);
	return cap.get(CAP_PROP_FRAME_WIDTH); //视频帧的宽度
}

int videoWidth = 320;
int videoHight = 240;
//得到一帧每个像素点的深度值并返回深度值之和
int getDepth(int* depth, int x) {
	//得到帧的完整路径
	string path = depthDatasPath + "\\frame" + to_string(x) + ".txt";
	char path1[50];
	strcpy_s(path1, path.c_str());
	
	FILE* f;
	fopen_s(&f, path1, "r");
	if (!f) {
		cout << "文件打开失败！";
		exit(-1);
	}
	//除掉第一行的无效信息
	char str[20] = "";
	fscanf_s(f, "%s", str, 10);

	int sum = 0;
	for (int i = 0; i < videoWidth * videoHight; i++) {
		fscanf_s(f, "%s", str, 15);
		depth[i] = atoi(str);
		sum += depth[i];
	}
	fclose(f);
	return sum;
}

//得到第frame帧，指定区域所有像素点的深度值之和，矩阵从第0行开始
int getRegionDepth(int x1, int x2, int y1, int y2, int frame) {
	//所有像素点的深度值都存放在depth[videoWidth*videoHight]
	int sum = 0;
	getDepth(depth, frame);
	for (int i = y1; i < y2; i++) {
		for (int j = x1; j < x2; j++) {
			sum += depth[i * videoWidth + j];
		}
	}
	return sum;
}
