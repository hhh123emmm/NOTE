import matplotlib.pyplot as plt


input_txt = 'E:\\TEST\\DS4\\cost1.txt'
x = []
y = []
z = []

f = open(input_txt)#打开文件
for line in f:#逐行读取
    line = line.strip('\n')#去除换行符
    line = line.split(' ')#每行按空格分隔成列表

    x.append(int(line[0]))#第一列序号-->x
    y.append(float(line[1]))#第二列时间-->y

f.close#关闭文件

input_txt = 'E:\\TEST\\DS4\\cost2.txt'
f = open(input_txt)
for line in f:
    line = line.strip('\n')
    line = line.split(' ')

    z.append(float(line[1]))#第二列时间-->z

f.close

plt.plot(x, y, marker='o', label='backtrack')#绘图
plt.plot(x, z, marker='*', label='branch_bound',linestyle="--")


plt.xticks(x[0:len(x):2], x[0:len(x):2], rotation=45)#设置x轴刻度和标签旋转角度
plt.margins(0)#设置绘图区域的边界
plt.xlabel("data")#x轴标签
plt.ylabel("cost(ms)")#y轴标签
plt.title("compare time")#标题
plt.tick_params(axis="both")#设置坐标轴的刻度
plt.legend()#添加图例
plt.show()#显示