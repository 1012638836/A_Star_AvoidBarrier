# A_Star_AvoidBarrier

这是我的人工智能实验报告，这个程序实现了简单的避障寻路算法。我们通过在map里面设置障碍(1)以及起始点(2)和终点(3)，成功的利用启发式算法A* 以较快的速度找到了一条最短路径。我认为介绍A* 算法最好的额博文链接如下：https://blog.csdn.net/denghecsdn/article/details/78778769 这篇博文将A* 算法与传统的最短路径算法Dijkstra以及基于启发算法的最佳搜索算法(BFS)进行比较，将加入过OpenList列表的点着色，着色标准为评价函数的数值。这篇博文完美的解释了A* 算法，值得一看！

此外，我上传了我的报告，以供以后的复习

bug记录：
<br>2018.12.18  
<br>bug表现：发现路径越界现象，当路径达到边界之后直接穿了过去。
<br>bug原因：已知Arr类型为LNode** 的二维数组的指针。当x=5,y=0时，Arr[x]+y-1等于Arr[4][9]，通过指针访问数组发生了边界越界。
<br>bug修改：在check_around_curNode函数中对x,y的数值进行限制，当(x,y)到达边界之后，对一些越界的点进行减枝。

<br>2018.12.19
<br>bug表现：发现个别点的G值计算错误
<br>bug原因：count_LNode_G函数位置判断函数错误
<br>bug修改：修改判断语句
    
