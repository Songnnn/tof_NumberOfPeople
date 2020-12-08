#include"getVideo.h"
#include"fileRead.h"

int main()
{
    uint8_t Rainbow[3][65536];
    makeColorTbl(Rainbow);
 
    //视频存放位置，视频格式，帧率，像素值，是否有颜色
    VideoWriter video = VideoWriter("F:\\TOF_NumberOfPeople\\Frame2All.mp4",
        CAP_OPENCV_MJPEG, 10, Size(320, 240), 0);

    int depth[320 * 240] = { 0 };
    //将第一帧到第9920帧转成mp4视频
    for (int i = 1; i <= 9920; i++) {
        getDepth(depth, i);
        Mat image = getMat(depth, Rainbow);
        imshow("tofVideo", image);
        waitKey(5);
        video.write(image);
    }
    return 1;
}
