work3 类和对象（3）
类的组合
2024.3.13


程序设计：矩形类，矩形的顶点是点类的对象。
本程序中，所有矩形的边都是平行于坐标轴的。

下面描述了程序的功能。每个类的具体成员函数（public），请自行设计。每个类通常都要包含构造函数、Set函数、Get函数、输出函数Show等等。矩形类包含平移Move函数。“判定矩形相交“需要设计线段类Line .

（1）1分
矩形数据文件rect.txt，文件中存放了10个矩形数据，每个矩形用对角顶点的坐标表示。(ch1_绪论.ppt p.70~71 举例介绍了文本文件(txt)的输入和输出)。
1 1 3 4
0 0 2 2
3 3 3 4
-2 3 2 6
0 0 0 0
1 1 -3 -2
-4 -1 -1 4
-2 -2 -2 1
3 4 8 7
5 2 7 4

（2）
设计点类Point，包含数据（private）_x , _y；(2分)
设计矩形类Rect ，包含成员数据（private）_p1、_p2，_p1和_p2是矩形的对角顶点。
从文件rect.txt中读取10个矩形数据，形成矩形数组arrRect。输出数组arrRect中每一个矩形的信息，如果这个数据不能构成矩形，输出“Can‘t construct rectangle.” 。如果可以构成矩形，输出对角顶点的坐标和矩形的面积、周长 ；（5分）

（3）2分
移动矩形：
用户输入矩形数组arrRect中的任意1个矩形的编号（例如1表示第1个矩形（1 1 3 4）），用户输入平移量（横坐标移动几个单位，纵坐标移动几个单位），程序把这个矩形按照平移量平移；输出平移以后的矩形信息。

（4）选作部分  
判定矩形相交：
设计一个类外函数判断2个矩形是否相交，如果不相交，返回0；如果相交，返回1表示交集是一个点Point，此时p就是交点；如果相交，返回2表示交集是一个线段Line ,此时l就是交线；如果相交，返回3表示交集是一个矩形，此时r3 就是交集矩形 .
int InterSectRect(Rect r1, Rect r2, Point& p, Line& l, Rect& r3, );
用户输入矩形数组arrRect中的任意2个矩形的编号（例如1表示第1个矩形（1 1 3 4）），程序判断这2个矩形是否相交，程序输出判断结果，如果相交，输出交集。

（5）程序的运行结果（供参考）
在“移动矩形“和“判定矩形相交“的过程中，如果用户输入的矩形编号其实并不能构成矩形，则给出提示并且让用户再次输入，直到用户输入的编号可以构成矩形。

程序的一次运行：
10 rectangles in arrRect：
Rect(1 1 3 4) area=6 perimeter=10
Rect(0 0 2 2) area=4 perimeter=8
3 3 3 4 Can’t construct rectangle. 
Rect(-2 3 2 6) area=12 perimeter=14
0 0 0 0 Can’t construct rectangle.
Rect(1 1 -3 -2) area=12 perimeter=14
Rect(-4 -1 -1 4) area=15 perimeter=16
-2 -2 -2 1 construct rectangle
Rect(3 4 8 7) area=15 perimeter=16
Rect(5 2 7 4) area=4 perimeter=8

Move a rectangle:
Input no. of rectangle: 3
3 3 3 4 Can’t construct rectangle.
Input no. of rectangle: 10
Rect(5 2 7 4) area=4 perimeter=8
Input the offset:
offset x: 3
offset y: -7
Rect(8 -5 10 -3) area=4 perimeter=8

Judge 2 rectangles intersect:
Input no. of rectangle1: 1
Rect(1 1 3 4) area=6 perimeter=10
Input no. of rectangle2: 2
Rect(0 0 2 2) area=4 perimeter=4
Rect(1 1 3 4) intersect with Rect(0 0 2 2) at Rect(1 1 2 2)

某一次运行判断矩形相交（供参考）：
Judge 2 rectangles intersect:
Input no. of rectangle1: 3
3 3 3 4 Can’t construct rectangle.
Input no. of rectangle1: 6
Rect(1 1 -3 -2) area=12 perimeter=14
Input no. of rectangle2: 7
Rect(-4 -1 -1 4) area=15 perimeter=16
Rect(1 1 -3 -2) intersect with Rect(-4 -1 -1 4) at Rect(-3 1 -1 -1)

其他多次运行判断矩形相交，略

