#pragma once
#include<bits/stdc++.h>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include"fileRead.h"
using namespace std;
using namespace cv;

int people = 0, entrance = 0, exits = 0;
int startFrame = 1, endFrame = 500;
int commonDepth = 370000000; //略小于无人情况下的深度值
#define entranceThreshold 180000000 //入口处区域，无人情况下的深度值之和
#define exitThreshold 180000000 //出口处区域，无人情况下的深度值之和
#define oneThreshold 340000000 //一人出现时，整帧的最小深度值之和，取值要略大一点
#define twoThreshold 300000000 //两人同时出现时，整帧的最小深度值之和，取值要略大一点
#define threeThreshold 100 //此处画面中最多同时出现两个人，这个值用不到
int threshold[4] = { 0,oneThreshold,twoThreshold,threeThreshold };

//输入某一帧的检测区域，通过该区域的深度值变化判断是否有人进入
bool isComing(int x1, int x2, int y1, int y2, int frame,int threshold) {
	int depth = getRegionDepth(x1, x2, y1, y2, frame);
	if (depth < threshold) return true;
	return false;
}

//递归版
void getNumberOfPeople(int tsd,int number,int& i) //number是此时同时出现的人数，tsd是此时对应的深度阈值，start是初始帧
{
	for (; i <= endFrame; i++) {
		int depthValue = getDepth(depth, i); //得到第i帧所有像素点的深度值之和
		if (depthValue <= tsd) {
			people++;
			string tip = "第 " + to_string(i) + " 帧";
			if (isComing(0, videoWidth / 2, 0, videoHight, i, entranceThreshold)) { 
				//帧的整个左边为入口检测区域
				entrance++;
				tip += "有人从入口方向进入，此时入口处进入的人数累计为: " + to_string(entrance) + " 人，此时的总人数为：" + to_string(people) + "\n\n";
			}
			else if (isComing(videoWidth / 2, videoWidth, 0, videoHight, i, exitThreshold)) {
				exits++;
				tip += "有人从出口方向进入，此时出口处进入的人数累计为: " + to_string(exits) + " 人，此时的总人数为：" + to_string(people) + "\n\n";
			}
			cout << tip;
			while (i <= endFrame) {
				if (number == 1) { //出循环条件是回到无人情况
					if (depthValue >= commonDepth) break;
					else if (depthValue <= threshold[number + 1]) getNumberOfPeople(threshold[number + 1], number + 1, i);
				}
				else if (number == 2) { //出循环条件是回到一人或无人情况
					if (depthValue >= commonDepth || (depthValue <= oneThreshold && depthValue >= twoThreshold)) return;
				}
				if (i > endFrame) break;
				i++;
				depthValue = getDepth(depth, i);
			}
		}
	}
}
