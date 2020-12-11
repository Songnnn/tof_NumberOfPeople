# tof_NumberOfPeople
tof视频，统计人数及进出方向

## 版本介绍
### V1.0
使用RGB值（准确的说是R值）的变化来统计人数，这个方法不太准确，算是间接利用深度值，主要是之前得不到直接的深度数据，只能这样做。

### V2.0
直接使用深度值来进行人数统计
#### 算法流程
输入：视频每一帧的每一个像素点的深度值，存放在frame1.txt到framex.txt，每行的数值就是一个像素点的深度值
输出：视频中出现的总人数，及各方向来的人数
步骤：
1. 将深度数据转成伪彩视频，再将该伪彩视频截成帧，用作验证
2. 计算每一帧所有像素点的深度值之和
3. 分析出无人情况、单人情况以及多人情况能够引起的最大深度值变化，以此进行人数统计
4. 对固定区域进行深度值变化监控，判断其进入的方向
#### 全局变量介绍
代码中共含18个全局变量，fileRead.h中有6个，getNumbers.h中有12个
##### fileRead.h中的全局变量
`depth[320*240]={0}`&emsp;&emsp;320\*240是视频帧的像素点个数，即videoWidth\*videoHight<br>
`videoPath`&emsp;&emsp;深度数据转出的伪彩视频所在地址<br>
`framesFilePath`&emsp;&emsp;伪彩视频帧所在地址<br>
`depthDatasPath`&emsp;&emsp;深度数据所在地址<br>
`videoWidth`&emsp;&emsp;像素点矩阵的宽<br>
`videoHight`&emsp;&emsp;像素点的高
##### getNumbers.h中的全局变量
`people`&emsp;&emsp;出现的总人数<br>
`entrance`&emsp;&emsp;从入口区域进入的人数<br>
`exits`&emsp;&emsp;从出口区域进入的人数<br>
`satrtFrame`&emsp;&emsp;开始帧<br>
`endFrame`&emsp;&emsp;结束帧<br>
`commonDepth`&emsp;&emsp;无人情况下整帧的深度值之和（取值略小一些）<br>
`entranceThreshold`&emsp;&emsp;入口处区域，无人情况下的深度值之和<br>
`exitThreshold`&emsp;&emsp;出口处区域，无人情况下的深度值之和<br>
`oneThreshold`&emsp;&emsp;一人出现的过程中，整帧的最小深度值之和（取值略大一些）<br>
`twoThreshold`&emsp;&emsp;两人同时出现的过程中，整帧的最小深度值之和（取值略大一些）<br>
`threeThreshold`&emsp;&emsp;三人同时出现的过程中，整帧的最小深度值之和（取值略大一些）（该值没有用到，因为这里假设画面最多同时出现两人）<br>
`int threshold[4] = { 0,oneThreshold,twoThreshold,threeThreshold }`&emsp;&emsp;如代码所示<br>
#### 运行前需要注意的点
1. 先算出videoWidth和videoHight，随后给它们赋上算好的值，depth\[videoWidth\*videoHight]初始化需要用常量
2. 出入口区域的选择很重要，不能太大也不能太小，入口区域的划定可以略小一点，因为代码是优先检测入口区域的
3. 深度阈值都需要事前赋值，获取这些阈值的相应函数代码也在项目中，这些阈值的选择很重要，略大还是略小看上方全局变量的解释
#### 需要改进的地方
1. 在两人接连进入画面时，若时间间隔足够短（小于1/fps秒），则有可能出现第二个人不被计数的情况。<br>
解决方案：如果深度值从oneThreshold回到commonDepth期间，帧数增大的范围较多（即“单人”停留时间过长），则考虑人数+1。
2. 由于此方法本身的缺陷性，任何能够引起类似深度值变化的物体经过画面时，都会被计数。（无解）



