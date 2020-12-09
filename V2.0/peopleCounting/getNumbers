#pragma once
#include<bits/stdc++.h>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

//得到一帧每个像素点的深度值并返回深度值之和
int getDepth(int* depth, int x) {
	//得到帧的完整路径
	char path1[50] = "F:\\TOF_NumberOfPeople\\\\Frame2\\frame";
	char path2[50];

	_itoa_s(x, path2, 10);
	char path3[50] = ".txt";
	strcat_s(path2, 50, path3);
	strcat_s(path1, 50, path2);

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
	for (int i = 0; i < 320 * 240; i++) {
		fscanf_s(f, "%s", str, 15);
		depth[i] = atoi(str);
		sum += depth[i];
	}
	fclose(f);
	return sum;
}

//得到视频帧的宽度和高度
void getVideoSize(int& width, int& hight, string videoPath) {
	VideoCapture cap;
	cap.open(videoPath);
	width = cap.get(CAP_PROP_FRAME_WIDTH); //视频帧的宽度
	hight = cap.get(CAP_PROP_FRAME_HEIGHT); //视频帧的高度
}

int people = 0;
int startFrame = 1, endFrame = 500;
int commonDepth = 370000000; //略小于无人情况下的深度值
#define oneThreshold 340000000 //取值略大一点
#define twoThreshold 300000000 //取值略大一点
#define threeThreshold 100
int threshold[4] = { 0,oneThreshold,twoThreshold,threeThreshold };
int depth[320 * 240] = { 0 };
//递归版（最多两人同时出现的情况）
void getNumberOfPeople(int tsd,int number,int& i) //number是此时同时出现的人数，tsd是此时对应的深度阈值，start是初始帧
{
	for (; i <= endFrame; i++) {
		int depthValue = getDepth(depth, i); //得到第i帧所有像素点的深度值之和
		if (depthValue <= tsd) {
			people++;
			printf("第 %d 帧有人出现，此时的总人数为: %d\n\n", i, people);
			while (i <= endFrame) {
				if (number == 1) { //出循环条件是回到无人情况
					if (depthValue >= commonDepth) break;
					else if (depthValue <= threshold[number + 1]) getNumberOfPeople(threshold[number + 1], number + 1, i);
				}
				else if (number == 2) { //出循环条件是回到一人或无人情况
					if (depthValue >= commonDepth || (depthValue <= oneThreshold && depthValue >= twoThreshold)) return;
					//else if (depthValue <= threshold[number + 1]) getNumberOfPeople(threshold[number + 1], number + 1, i);
				}
				//else if (number == 3) { //出循环条件是回到一人或两人或无人情况
				//	if (depthValue >= commonDepth || (depthValue <= oneThreshold && depthValue >= twoThreshold)
				//		|| (depthValue <= twoThreshold && depthValue >= threeThreshold)) return;
				//}
				if (i > endFrame) break;
				i++;
				depthValue = getDepth(depth, i);
			}
		}
	}
}
