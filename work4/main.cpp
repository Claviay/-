// 
// 
// 这里查资料确认一下使用睡眠模拟天数过程中————Sleep和sleep的混淆：
//   <unistd.h> 使用sleep(1)睡眠1秒，单位是秒
//   <windows.h> 使用 Sleep(1000)睡眠1秒，单位是毫秒

#include <windows.h> // 模拟养鱼程序中天数流逝(work4的作业2)
#include <iostream>
#include <iomanip>
#include <string> // 为了substr操作string的各类函数(work4的作业1)
#include <cmath>  // 用到了pow之类的计算利息(work4的作业1)
#include <cstdlib> // 包含rand()和srand()
#include <ctime>   // 包含time()
#include <iomanip>
#include <vector>

using namespace std;

/* ————————————————————————————————————Deposit类     work4的作业1———————————————————————————————————————————————————————————— */
class Deposit {
private:

    // 静态成员变量————存款ID
    static int id; 

    int other_id; // 存款的唯一ID

    int particularly_password; // 存款账户密码

    string personal_name; // 存款者姓名

    double particularly_money; // 存款金额

    // 存款的具体日期
    string particular_year;
    string particular_month;
    string particular_days;

    // 上次计算利息的日期
    string lastSumYear, lastSumMonth, lastSumDay;

    // 静态成员变量————记录当前日期
    static string year, month, day;

    static double special_rate; // 静态成员变量，记录特殊利率

public:
    // 构造函数，初始化存款账户
    // 参数默认值————允许构造函数在没有提供具体参数时使用这些默认值
    // password: 账户密码，默认为0
    // accountName: 账户名称，默认为"没有收到名字！"
    // money: 存款金额，默认为0
    // date: 日期，默认为"0000-00-00"
    

    // 这样更加方便到时候查找错误
    Deposit(int password = 0, string accountName = "没有收到名字！", double money = 0, string date = "0000-00-00") :
        personal_name(accountName), // 初始化账户名称
        particularly_money(money), // 初始化账户金额
        particularly_password(password) { // 初始化账户密码
        id++; // 为每个存款账户生成唯一的ID————通过对静态成员变量id自增实现的
        other_id = id; // 将生成的唯一ID赋值给other_id，用于识别不同的存款账户

        // 解析传入的日期字符串，提取年、月、日
        // find_first_of和find_last_of用于在字符串中查找字符'-'出现的位置
        int firstSplit = date.find_first_of('-');
        int lastSplit = date.find_last_of('-');

        // 根据'-'的位置，使用substr方法提取年、月、日
        // particular_year存储年份
        particular_year = date.substr(0, firstSplit);
       


        particular_month = date.substr(firstSplit + 1, lastSplit - firstSplit - 1);   // particular_month存储月份，提取从第一个'-'之后到最后一个'-'之间的字符串


        // particular_days存储日，提取最后一个'-'之后所有的字符串
        particular_days = date.substr(lastSplit + 1);

        // 将提取的日期设置为账户的最后结算日期
        lastSumYear = particular_year;
        lastSumMonth = particular_month;
        lastSumDay = particular_days;
    }

    // 显示存款详情
    void reveal() {
        count_the_money(); // 计算当前存款金额，包括利息
        cout << other_id << " ";
        cout << personal_name;
        cout << " ";
        cout << particularly_password << " ";
        cout << fixed << setprecision(2);
        cout << particularly_money << " ";
        cout << special_rate;
        cout << "% " << particular_year << '-';
        cout << particular_month << '-';
        cout << particular_days << " " << endl;
    }


    // 更改特殊利率
    // 此函数接收一个字符串形式的利率，然后更新全局变量special_rate
    // 特殊利率用于后续计算存款增长
    static void changeRate(string rate) {
        // 查找利率字符串中'%'字符的位置
        int index = rate.find_last_of('%');
        // 删除'%'字符，只保留数值部分
        rate.erase(index);
        // 将字符串形式的利率转换为double类型，并更新全局变量special_rate
        special_rate = stod(rate);
    }

    // 更新当前日期
    // 此函数用于更新全局日期变量，包括年、月、日
    static void the_finals(string date) {
        // 查找第一个'-'字符的位置，用于分隔年份
        int firstSplit = date.find_first_of('-');


        // 查找最后一个'-'字符的位置，用于分隔月份和日期
        int lastSplit = date.find_last_of('-');



        year = date.substr(0, firstSplit);


        // 提取并更新月份，需要计算起始位置和长度
        month = date.substr(firstSplit + 1, lastSplit - firstSplit - 1);
        // 提取并更新日期
        day = date.substr(lastSplit + 1);
    }

    // 根据特殊利率和时间计算存款增长
    // ————从上次结算日期到当前日期，基于特殊利率的存款增长
    void count_the_money() {
        // 计算自上次结算以来的月数差
        // 首先将年份差转换为月份，然后加上月份差
        int cMonth = 12 * (stoi(year) - stoi(lastSumYear)) + stoi(month) - stoi(lastSumMonth);

        // 特殊利率(special_rate)是以百分比形式存储的，因此除以100转换为小数
        particularly_money *= pow(1 + special_rate / 100, cMonth);   // 使用pow函数进行增长的复合计算

        // 更新最后结算的日期，为下次计算准备
        lastSumYear = year;
        lastSumMonth = month;
        lastSumDay = day;
    }
};

// 静态成员变量的初始化
// 这是共享的
string Deposit::day = "0";
string Deposit::month = "0";
string Deposit::year = "0";
double Deposit::special_rate = 0;
int Deposit::id = 0;
/* ————————————————————————————————————Deposit类     work4的作业1———————————————————————————————————————————————————————————— */














/* ————————————————————————————————————养鱼     work4的作业2———————————————————————————————————————————————————————————— */

class Fish {
public:
    string name;  // 鱼的名字
    string color;   // 鱼的颜色
    int weight;    // 鱼的体重
    int lastFedDay;
    int daysWithoutFood; // 连续未吃食物的天数
    bool isAlive; // 鱼儿生死状态
    static int totalCount; // 鱼儿存活只数！


    // 这是构造函数
    Fish(string n, string c) : name(n), color(c), weight(100), lastFedDay(0), isAlive(true) {
        ++totalCount;
    }

    //返回当前鱼的总数
    static int getTotalCount() {
        return totalCount;
    }

    // 更新鱼的状态
    void updateStatus(int currentDay) {
        if (currentDay - lastFedDay > 1) { // 如果当前天与上次喂食天的差大于1，说明至少有一天没吃到
            daysWithoutFood++;// 增加未喂食的天数
        }
        else {
            daysWithoutFood = 0; // 如果被喂食了，重置计数
        }

        if (daysWithoutFood >= 5) {
            weight -= 10; // 从第五天开始，连续未吃食物的每天减少10克体重
        }



        // 检查鱼是否因体重问题死亡
        if (weight <= 0) {
            isAlive = false;
            --totalCount;
            cout << name << " 鱼饿死了。" << endl;
        }
        else if (weight >= 300) {
            isAlive = false;
            --totalCount;
            cout << name << " 撑死了！" << endl;
        }
    }

};

// 喂食鱼的函数
void feedFish(vector<Fish>& fishes, int currentDay) {

    // 存储指向活着的鱼的指针
    vector<Fish*> aliveFishes; // 这里很重要!!

    for (auto& fish : fishes) {
        if (fish.isAlive) {
            aliveFishes.push_back(&fish);
        }
    }

    // 如果有活着的鱼，随机选择一条喂食
    if (!aliveFishes.empty()) {
        int index = rand() % aliveFishes.size();  // 仅选择活着的鱼
        Fish* fish = aliveFishes[index];
        fish->weight += 10;
        fish->lastFedDay = currentDay; // 更新最后喂食天数 
        cout << "第" << currentDay << "天：" << fish->name << " 吃到了食物" << endl;
    }
}

// 更新所有鱼的状态的函数
void updateFishStatuses(vector<Fish>& fishes, int currentDay) {
    for (auto& fish : fishes) {
        fish.updateStatus(currentDay);
    }
}

// 打印所有活着的鱼的状态的函数
void printFishStatus(const vector<Fish>& fishes) {
    cout << "名字\t颜色\t体重\t上次吃食时间" << endl;
    for (const auto& fish : fishes) {
        if (fish.isAlive) {
            cout << fish.name << "\t" << fish.color << "\t" << fish.weight << "g\t\t" << "第" << fish.lastFedDay << "天" << endl;
        }
    }
}


int Fish::totalCount = 0;  // 初始化静态成员变量!


/* ————————————————————————————————————养鱼     work4的作业2———————————————————————————————————————————————————————————— */









int main()
{

    /* ————————————————————————————————————Deposit类     work4的作业1———————————————————————————————————————————————————————————— */
    Deposit* member[5];
    Deposit::changeRate("0.5%");
    member[0] = new Deposit(123456, "张三", 10000, "2020-5-1");
    member[1] = new Deposit(112233, "李四", 20000, "2020-7-1");
    member[2] = new Deposit(111111, "王五", 15000, "2021-10-1");
    member[3] = new Deposit(222222, "赵六", 58000, "2021-2-1");
    member[4] = new Deposit(888888, "周七", 50000, "2022-1-1");

    Deposit::the_finals("2022-7-1");

    cout << "2022-7-1，输出所有账户的信息：" << endl << "账号	户名 密码 金额 月利率 开户时间\n";
    for (int i = 0; i < 5; i++) {
        member[i]->reveal();
    }

    cout << "----------------------------------------------------------";
    cout << endl;
    cout << "----------------------------------------------------------\n";

    Deposit::the_finals("2022-8-1");
    cout << "2022-8-1，输出所有账户的信息：" << endl << "账号	户名 密码 金额 月利率 开户时间\n";
    for (int i = 0; i < 5; i++) {
        member[i]->reveal();
    }

    cout << "----------------------------------------------------------";
    cout << endl;
    cout << "----------------------------------------------------------\n";

    Deposit::the_finals("2022-9-1");
    cout << "2022-9-1，输出所有账户的信息：" << endl << "账号	户名 密码 金额 月利率 开户时间\n";
    Deposit::changeRate("0.4%");
    for (int i = 0; i < 5; i++) {
        member[i]->reveal();
    }

    cout << "----------------------------------------------------------";
    cout << endl;
    cout << "----------------------------------------------------------\n";

    Deposit::the_finals("2022-10-1");
    cout << "2022-10-1，输出所有账户的信息：" << endl << "账号	户名 密码 金额 月利率 开户时间\n";
    for (int i = 0; i < 5; i++) {
        member[i]->reveal();
    }

    cout << "----------------------------------------------------------";
    cout << endl;
    cout << "----------------------------------------------------------\n";

    Deposit::the_finals("2022-11-1");
    cout << "2022-11-1，输出所有账户的信息：" << endl << "账号	户名 密码 金额 月利率 开户时间\n";
    for (int i = 0; i < 5; i++) {
        member[i]->reveal();
    }

    cout << "----------------------------------------------------------";
    cout << endl;
    cout << "----------------------------------------------------------\n";

    Deposit::the_finals("2022-12-1");
    cout << "2022-12-1，输出所有账户的信息：" << endl << "账号	户名 密码 金额 月利率 开户时间\n";
    for (int i = 0; i < 5; i++) {
        member[i]->reveal();
    }
    /* ————————————————————————————————————Deposit类     work4的作业1———————————————————————————————————————————————————————————— */









    /* ————————————————————————————————————养鱼     work4的作业2———————————————————————————————————————————————————————————— */
    cout << "\n\n--------------------------------------------------";
    cout << "\n接下来是work4的作业2\n";
    cout << "现在是养鱼时间！请看下面：\n";


    srand(static_cast<unsigned>(time(0))); // 初始化随机数生成器！

    vector<Fish> fishes; // 存储所有鱼的容器
    int N; // 用户要养的鱼的数量

    cout << "您要养几条鱼（N>=5）: ";
    cin >> N;
    while (N < 5) {
        cout << "鱼的数量至少为5，这个不符合题意！请重新输入：\n";
        cin >> N;
    }

    // 输入每条鱼的名字和颜色
    for (int i = 1; i <= N; ++i) {
        string name, color;
        cout << "请输入第" << i << "条鱼的名字、颜色：";
        cin >> name >> color;
        fishes.emplace_back(name, color);
    }

    cout << "开始养鱼了！！！\n";

    int day = 1;
    char cont = 'N';
    do {
        feedFish(fishes, day);  // 喂鱼
        updateFishStatuses(fishes, day);  // 更新鱼的状态

        if (day % 10 == 0) {  // 每10天打印状态
            printFishStatus(fishes);
        }

        cout << "您要结束养鱼吗？(Y/N) : ";
        cin >> cont;
        day++;
    } while (cont != 'Y' || Fish::getTotalCount() > 0); // 要么主动推出游戏，要么鱼全饿死了、全撑死了总之要么全挂了

    if (Fish::getTotalCount() == 0) {
        cout << "抱歉，所有的鱼都死了，养鱼失败了，程序结束。" << endl;
    }
    else {
        cout << "程序结束。" << endl;
    }

    /* ————————————————————————————————————养鱼     work4的作业2———————————————————————————————————————————————————————————— */




    return 0;
}
