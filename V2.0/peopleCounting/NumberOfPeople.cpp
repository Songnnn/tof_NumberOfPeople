#include"fileRead.h"
#include"getNumbers.h"
using namespace std;


int main()
{
    //Frame2.mp4是Frame2的第1帧到500帧转成的视频
    //getFrames("F:\\TOF_NumberOfPeople\\Frame2.mp4");
    
    //得到第1到500帧，每一帧所有像素点的深度值之和
    /*
    for (int i = 1; i <= 500; i++) {
        int depth[320 * 240] = { 0 };
        printf("第 %d 帧的深度值之和为：%d\n\n", i, getDepth(depth,i));
    }
    */
    /*
    string videoPath = "";
    int videoWidth = 0, videoHight = 0;
    getVideoSize(videoWidth, videoHight, videoPath);
    */


    /*
    * 非递归版本，比较繁琐，虽然加了很多注释，但可读性还是比较差，还是递归版本简略一些
    int people = 0;
    int startFrame = 1, endFrame = 500;
    int commonDepth; //略小于无人情况下的深度值
    int oneThreshold, twoThreshold, threeThreshold; //深度值小于oneThreshold则认为至少有一个人出现，这里假设最多同时出现三人,如果有多人同时出现，则考虑递归
    for (int i = startFrame; i <= endFrame-2; i++) {
        int depth[320 * 240] = { 0 };
        double depthValue = getDepth(depth, i); //得到第i帧所有像素点的深度值之和
        if (depthValue <= oneThreshold) { //有人出现（这里不考虑特殊的干扰情况，一旦下降到阈值即认为有人出现）
            people++;
            printf("第 %d 帧有人出现，此时的总人数为: %d\n\n", i, people);
            while (i <= endFrame - 2) { //出循环的条件为回到了无人情况
                if (depthValue <= twoThreshold) { //两个人同时出现
                    people++;
                    printf("第 %d 帧有人出现，此时的总人数为: %d\n\n", i, people);
                    while (i <= endFrame - 2) { //出循环的条件为回到了无人或一人情况
                        if (depthValue <= threeThreshold) { //三个人同时出现
                            people++;
                            printf("第 %d 帧有人出现，此时的总人数为: %d\n\n", i, people);
                            while (i <= endFrame - 2) { //出循环的条件为回到了无人或两人或一人情况
                                if (depthValue >= commonDepth || (depthValue <= oneThreshold && depthValue >= twoThreshold)
                                    || (depthValue <= twoThreshold && depthValue >= threeThreshold)) break;
                                i++;
                                depthValue = getDepth(depth, i);
                            }
                        }
                        else if (depthValue >= commonDepth || (depthValue <= oneThreshold && depthValue >= twoThreshold)) break;
                        i++;
                        depthValue = getDepth(depth, i);
                    }
                }
                else if (depthValue >= commonDepth) break;
                i++;
                depthValue = getDepth(depth, i);
            }
        }
    }
    */
    
    getNumberOfPeople(oneThreshold, 1, startFrame);
    return 1;
}

