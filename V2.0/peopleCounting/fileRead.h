#pragma once
#include"getNumbers.h"
using namespace std;
using namespace cv;


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
		String path = "F:\\TOF_NumberOfPeople\\framsofFrame2\\" + to_string(i + 1) + ".jpg"; //文件的取名得规范，得含有原视频的信息
		imwrite(path, frame);
	}
	cap.release();
	return frames;
}
