#pragma once
#include<bits/stdc++.h>
using namespace std;

//得到第x帧所有像素点的深度值，并将其存放在depth数组
void getDepth(int *depth,int x) {
	char path1[50] = "F:\\TOF_NumberOfPeople\\Frame2\\frame";
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
    //将这帧的每个像素点的深度值都存到depth数组中
    //第i个像素点的深度值为depth[i]
    for (int i = 0; i < 320 * 240; i++) {
        fscanf_s(f, "%s", str, 15);
        depth[i] = atoi(str);
    }
    fclose(f);
}
