// Rectangle
// 
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;


// Point坐标类
class Point {
private:
    double _x, _y;

public:
    Point(double x = 0, double y = 0) : _x(x), _y(y) {}

    void Set(double x, double y) {
        _x = x;
        _y = y;
    }

    double GetX() const { return _x; }
    double GetY() const { return _y; }


    void Show() const {
        cout << _x << " " << _y;
    }
};



// Rect类
class Rect {
private:
    Point _p1, _p2;

public:
    Rect(Point p1 = Point(), Point p2 = Point()) : _p1(p1), _p2(p2) {}

    bool IsValid() const {
        return _p1.GetX() != _p2.GetX() && _p1.GetY() != _p2.GetY();
    }

    void Move(double dx, double dy) {
        _p1.Set(_p1.GetX() + dx, _p1.GetY() + dy);
        _p2.Set(_p2.GetX() + dx, _p2.GetY() + dy);
    }

    double Area() const {
        return abs((_p2.GetX() - _p1.GetX()) * (_p2.GetY() - _p1.GetY()));
    }

    double Perimeter() const {
        return 2 * (abs(_p2.GetX() - _p1.GetX()) + abs(_p2.GetY() - _p1.GetY()));
    }

    void Show() const {
        if (!IsValid()) {
            // 按照输出标准，不需要cout << "Rect(";
            _p1.Show();
            cout << " ";
            _p2.Show();

            // 按照输出标准，不需要cout << ") ";
            // 下面添加一个空格即可
            cout << " ";

            // 不能建立矩形
            cout << "Can't construct rectangle." << endl; 
            return;
        }

        // 可建立矩形的情况
        cout << "Rect(";
        _p1.Show();
        cout << " ";
        _p2.Show();
        cout << ") area=" << Area() << " perimeter=" << Perimeter() << endl;
    }

    Point GetP1() const { return _p1; }
    Point GetP2() const { return _p2; }
};



// 类外函数设计
// 判断相交

// 这里需要修改，没有满足题意
//bool IsIntersect(const Rect& r1, const Rect& r2) {
//    return !(r1.GetP1().GetX() > r2.GetP2().GetX() ||
//        r1.GetP2().GetX() < r2.GetP1().GetX() ||
//        r1.GetP1().GetY() > r2.GetP2().GetY() ||
//        r1.GetP2().GetY() < r2.GetP1().GetY());
bool IsIntersect(const Rect& r1, const Rect& r2, Rect& intersectRect) {
    double left = max(r1.GetP1().GetX(), r2.GetP1().GetX());
    double right = min(r1.GetP2().GetX(), r2.GetP2().GetX());
    double bottom = max(r1.GetP1().GetY(), r2.GetP1().GetY());
    double top = min(r1.GetP2().GetY(), r2.GetP2().GetY());

    if (left < right && bottom < top) {
        // 两个矩形相交
        intersectRect = Rect(Point(left, bottom), Point(right, top));
        return true;
    }
    return false;
}






int main() {
    vector<Rect> arrRect;  // 构建一个 vector 容器
    
    // 第（1）题，读取文件
    ifstream inFile("rect.txt");
    double x1, y1, x2, y2;

    // 当能成功从文件中读取到四个连续的浮点数时，就使用这些坐标创建一个新的 Rect 对象，并通过 emplace_back 方法将其添加到 arrRect 向量中。
    while (inFile >> x1 >> y1 >> x2 >> y2) {
        arrRect.emplace_back(Point(x1, y1), Point(x2, y2));
    }
    inFile.close();



    // 第（2）题 输出周长和面积等
    cout << "10 rectangles in arrRect：" << endl;
    for (auto& rect : arrRect) {
        rect.Show();
    }


    cout << endl; // 为了美观，空一行



    // 第（3）题 移动矩形
    // 第（5）题 满足用户重复输入
    cout << "Move a rectangle :" << endl;
    int flag = 1; // 循环判别标志
    int index;    // 矩形在文件中的索引
    double offsetX, offsetY; // 移动距离

    while (flag == 1) {
        // 提示输入index
        cout << "Input no. of rectangle: ";
        cin >> index;

        if (index <= 0 || index > 10) {
            cout << "错误的index";
            continue; // 循环，满足用户错误输入后，需要重复输入的需要
        }

        else {
            if (!arrRect[index - 1].IsValid()) { // 重新循环，直到满足生成矩形条件为止
                arrRect[index - 1].Show();
                continue;
            }

            else {
                // 打破循环
                flag = 0; 

                // 展示满足生成矩阵的数值（移动前）
                arrRect[index - 1].Show();
                cout << endl;

                // 输入移动的x，y移动距离
                cout << "Input the offset:" << endl;
                cout << "offset x:";
                cin >> offsetX;
                cout << "offset x:";
                cin >> offsetY;

                // 展示移动后的矩阵的数值
                arrRect[index - 1].Move(offsetX, offsetY);
                arrRect[index - 1].Show();

            }
        }
    }


    // 第（4）题 ，第（5）题在上文已完成
    // 重叠 IsIntersect函数
    cout << "Judge 2 rectangles intersect:" << endl;
    
    

    int index_1, index_2;       // 第一个、第二个 要比较的矩形的编号
    int flag_1 = 1, flag_2 = 1; // 第一个、第二个 循环标志

    // 开始输入第一个矩形编号
    while (flag_1 == 1) {
        // 提示输入index
        cout << "Input no. of rectangle1: ";
        cin >> index_1;

        // 增强代码的强壮性
        if (index_1 <= 0 || index_1 > 10) {
            cout << "第一个矩形编号输入错误！\n";
            continue; // 循环，满足用户错误输入后，需要重复输入的需要
        }

        else {
            if (!arrRect[index_1 - 1].IsValid()) { // 需要作为参与比较的rec组不满足生成矩形，则重新循环，直到满足生成矩形条件为止
                arrRect[index_1 - 1].Show();
                cout << endl;
                continue;
            }

            else {
                // 前置一切条件成立，打破循环
                flag_1 = 0;
                arrRect[index_1 - 1].Show(); // 展示详细信息
            }
        }
    }



    // 开始输入第二个矩形编号
    while (flag_2 == 1) {
        // 提示输入index
        cout << "Input no. of rectangle2: ";
        cin >> index_2;

        // 增强代码的强壮性
        if (index_2 <= 0 || index_2 > 10) {
            cout << "第二个矩形编号输入错误！\n";
            continue; // 循环，满足用户错误输入后，需要重复输入的需要
        }

        else {
            if (!arrRect[index_2 - 1].IsValid()) { // 需要作为参与比较的rec组不满足生成矩形，则重新循环，直到满足生成矩形条件为止
                arrRect[index_2 - 1].Show();
                cout << endl;
                continue;
            }

            else {
                // 前置一切条件成立，打破循环
                flag_2 = 0;
                arrRect[index_2 - 1].Show(); // 展示详细信息
            }
        }
    }

    // 通过以上两个循环找到两个矩形的编号
    // 然后使用类外函数
    Rect intersectRect;
    if (IsIntersect(arrRect[index_1 - 1], arrRect[index_2 - 1], intersectRect)) {
        cout << "Rect(" << arrRect[index_1 - 1].GetP1().GetX() << " " << arrRect[index_1 - 1].GetP1().GetY() << " " << arrRect[index_1 - 1].GetP2().GetX() << " " << arrRect[index_1 - 1].GetP2().GetY() << ") "
            << "intersect with Rect(" << arrRect[index_2 - 1].GetP1().GetX() << " " << arrRect[index_2 - 1].GetP1().GetY() << " " << arrRect[index_2 - 1].GetP2().GetX() << " " << arrRect[index_2 - 1].GetP2().GetY() << ") "
            << "at Rect(" << intersectRect.GetP1().GetX() << " " << intersectRect.GetP1().GetY() << " " << intersectRect.GetP2().GetX() << " " << intersectRect.GetP2().GetY() << ")" << endl;
    }
    else {
        cout << "No intersection." << endl;
    }

    return 0;
}
