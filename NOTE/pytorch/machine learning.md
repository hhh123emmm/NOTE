# machine learning

## supervised learning
监督学习
### examples
* 数据-->拟合曲线-->推测实际情况——实际情况不会改变
* 给算法一个包含了正确答案的数据集，算法的目的是给出正确的结果
    * 回归问题--给出连续结果，法预测连续集的数据
    * 分类问题--设法预测一个离散集的结果classification--discrete valued output（0 or 1）
* 多个特征 多个结果-->无穷多特征-->
### result
监督学习 数据集--预测--正确性
* regression problem 回归问题——连续
* classification problem 分类问题——离散
## unsupervised learning
无监督学习
### contrast
* supervised be-called right or wrong
* unsupervised be-called only dataset
    * cluster --聚类算法
    * cocktail --鸡尾酒会算法
    ```cpp
    Octave
    [W,s,v]=svd((repmat(sum(x.*x,1),size(x,1),1).*x)*x');
    ```
把 数据 分组
### result
无监督学习 让算法自主找到数据结构
## 学习算法
### 线性回归 linear regression
用数据集画图/模型拟合/training set求出模型参数值使画出的线与数据点更好地拟合
* 符号
    * m=样本数量
    * x=输入
    * y=输出
    * (x,y)=一个训练样本
    * ($x^i,y^i$)=序号训练样本
* task--想学习算法输入数据集-->假设函数hypothesis
    * $h_{\theta}(x)=\theta_0+\theta_1*x$
    * 拟合线性函数
    * 线性回归模型/单变量线性回归
* practice
    * $\theta$模型参数
    * $J(\theta_0,\theta_1)=1/(2m)*\sum_{i=1}^m(h_{\theta}(x^i)-y^i)^2$,代价函数，关于模型参数minimize J
    * $minimize_{\theta_0,\theta_1}J(\theta_0,\theta_1)$
### 代价函数 cost function
* 简化版本
    * hypothesis：$h_\theta=\theta_1*x$
    * parameters:$\theta_1$
    * cost function:$J(\theta_1)=1/(2m)\sum_{i=1}^m(h_\theta(x^i)-y^i)^2$
    * goal:$minimize_{\theta_1} J(\theta_1)$-->线性回归的目标函数
* 假设函数$h(x)$和代价函数$J(\theta_1)$
* 优化目标：Goal
* contour plots/figures等高线图
```cpp
cout<<"hello world";
```
### 梯度下降 gradient descent
apply线性回归or else to 最小化其他函数
局部最优点
* repeat until convergence收敛
* $\theta_j := \theta_j - 
\alpha*\frac{\partial J(\theta_0,\theta_1)}{\partial \theta_j} for(j=0 and j=1)$
    * :=赋值
    * =判断 asserting
    * 同时更新$\theta_0,\theta_1$
    * $\alpha$，学习速率，learning rate
### 线性回归的梯度下降
* $\theta_0 :=\theta_0-\alpha\frac{1}{m}\sum_{i=1}^{m}(h(x^i)-y)^2$
* $\theta_1 :=\theta_1-\alpha\frac{1}{m}\sum_{i=1}^{m}(h(x^i)-y)^2*x^i$
* Batch 梯度下降--每一步使用了所有数据样例
### 线性代数
* 矩阵$\begin{bmatrix}a & b\\c & d\end{bmatrix}$
    * $A_{ij}$ $i^{th}$ row
* 向量 $\begin{bmatrix}a\\b\\c\end{bmatrix}$
    * $y_i$ $i^{th}$ row
* 矩阵加法乘法
    * 乘法不满足交换律满足结合律
    * I $I_{n,n}$-单位矩阵-Identity Matrix-对角线上为1，其余0。
        * $I*A=A*I=A$
        * |mxm  |nxn   A:mxn
* 矩阵转置 逆
    * 逆矩阵 inverse matrix $A*A^{-1}=I$--只有方阵才有逆矩阵
    ```octave
    pinv(A)
    ```
    * 转置，m*n-->n*m
### 多元
多个特征量--多元线性回归：
* Notation:
    * $x^2_3$ ,第2个样本输入第三个特征值
    * $h_\theta(x)=\theta_0+\theta_1x_1+\theta_2x_2...+\theta_nx_n$
    * x 特征向量，n+1维，$\begin{bmatrix}x_0\\x_1\\...\\x_n\end{bmatrix}$
    * $\theta$ 参数变量$\begin{bmatrix}\theta_0,\theta_1,...,\theta_n\end{bmatrix}$
* gradient descent:
    * $\theta_j:=\theta_j-\alpha\frac{1}{m}\sum_{i=1}^m(h_\theta(x^i_j)-y^i)x^i_j$
    * 直到收敛
    * 特征缩放:使特征值范围大约-1~1——Feature Scaling
        * $x_1:0-2000,x_2:1-5$
        * $x_1/2000,x_2/5$
    * 均值归一化：尽可能使平均值为0——Mean normalization
        * $(x_1-1000)/2000,(x_2-2)/5$
        * $\frac{x-\mu}{s}$
    * learning rate $\alpha$
        * cost function $J(\theta)$
            * 一直下降 √
            * 一直上升/并不会每次都下降 too large ×
            * 降太慢 too small ×
        * 3倍调整
* 选择不同的特征和算法--多项式回归/多元线性回归
    * $h_\theta(x)=\theta_0+\theta_1x+\theta_2x^2+\theta_3x^3$-->多项式拟合为线性
        * $x_1=x$
        * $x_2=x^2$
        * $x_3=x^3$
    * length/width-->area
### 正规方程 normal equation n上万后就不太合适，建议梯度下降
直接得到最优解--求cost function偏微分置0--优点：不需要选择学习速率/迭代，缺点：计算复杂
* input：X m,n+1
    * $x^i=\begin{bmatrix}x^i_0\\x^i_1\\x^i_2\\...\\x^i_n\end{bmatrix},x^i_0=1$
    * $X=\begin{bmatrix}(x^1)^T\\(x^2)^T\\...\\(x^n)^T\end{bmatrix}$
* output：y m $\begin{bmatrix}y_1\\y_2\\...\\y_n\end{bmatrix}$
* $\theta=(X^TX)^(-1)X^Ty$
```cpp
prinv(X'*X)*X'*y
```
#### 不可逆性
* what if $X^TX$ is non-invertible?不可逆-->也可以得到答案
    * pinv伪逆
    * inv逆
* 不可逆原因
    * redundant features，特征冗余-->线性相关
    * 特征太多 （m<=n）-->删除/regularization正规化
### Coding语言
* python numpy？ R
* matlab/octave
```cpp
what
ones/zeros/eye
disp--printf
[2 3] (:)
save/load
```
* 根据索引查找/save load
#### 算法
MATLAB
## 分类问题
离散，logistics algorithm-->多分类
### 二分类
线性回归算法