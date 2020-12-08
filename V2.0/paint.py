//绘制视频帧的深度值之和变化

#得到每一帧的像素点深度值之和
def getDepthSum(x):
    depthSum=0
    #计算F:\\TOF_NumberOfPeople\\Frame2\\framex.txt的深度值之和
    fileName="F:\\TOF_NumberOfPeople\\Frame2\\frame"+str(x)+".txt"
    with open(fileName,"r") as f:
        #去掉第一行的无用信息
        line=f.readline()
        while line!="":
            line=f.readline()
            if line!='':
                depthSum+=int(line)
    return depthSum

#将F:\\TOF_NumberOfPeople\\Frame2中的第1到第500帧转成视频
#再将此视频截成500帧
#以这500帧观察深度值的变化
depth=[]
for i in range(1,501):
    depth.append(getDepthSum(i))

import numpy as np 
from matplotlib import pyplot as plt 

x = np.arange(1,500,1) 
y = np.array(depth)[x-1] #depth[0]存放的是第1帧的深度值之和
plt.title("values of frame's depth") 
plt.xlabel("frames") 
plt.ylabel("value of depth") 
plt.plot(x,y) 
plt.show()
