/*
    仓库位置：https://github.com/adfwer233/Cube

    Update 11-16
        实现了12种旋转函数
    
    Update 11-17
        对12种旋转函数中的输出添加了预编译指令
        实现了用于生成测试案例并输出打乱公式的函数

    Update 11-23
        实现了底层十字函数并编写了测试函数


*/

#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <ctime>

using namespace std;

// 预编译指令
// #define RotateDebug
#define CrossDebug

// 数据结构
// 分别用来存放魔方各个面的颜色
/*
    各个面的放置情况guide中所示
    1-6分别为前后左右上下

    cube[7][4][4]
    
    一些约定：
    数组下标从1开始，每个cube[i]中保存一个3*3矩阵
    魔方状态用对应单词首字母表示

    char opts[] : 保存各种操作
    char StandardColor[] : 保存各个面的标准颜色
*/

char ***cube;
char opts[] = "RrUuFfDdLlBb";
char StandardColor[] = "GBORWY";

// 初始化cube数组
void init()
{
    cube = new char **[7];
    for (int i = 1; i <= 6; i++)
    {
        cube[i] = new char *[55];
        for (int j = 1; j <= 3; j++)
            cube[i][j] = new char[45];
    }
}

// 输入输出函数

// 从标准输入流中读入一个魔方，标准如guide文件所示
void Sread()
{
    for (int i = 1; i <= 6; i++)
        for (int j = 1; j <= 3; j++)
            for (int k = 1; k <= 3; k++)
                cin >> cube[i][j][k];
}

// 将当前魔方的状态输出的到标准输出流中
void Sprint()
{
    for (int i = 1; i <= 6; i++)
    {
        for (int j = 1; j <= 3; j++)
            for (int k = 1; k <= 3; k++)
                cout << cube[i][j][k];
        cout << endl;
    }
}

// 辅助旋转函数：用于实现12个操作的辅助函数

// 对一个3*3的方阵进行顺时针旋转
void ClockwiseRotate(char **a)
{
    char b[4][4];
    for (int i = 1; i <= 3; i++)
        for (int j = 1; j <= 3; j++)
            b[j][3 - i + 1] = a[i][j];
    for (int i = 1; i <= 3; i++)
        for (int j = 1; j <= 3; j++)
            a[i][j] = b[i][j];
}

// 对一个3*3的方阵进行逆时针旋转
void antiClockwiseRotate(char **a)
{
    char b[4][4];
    for (int i = 1; i <= 3; i++)
        for (int j = 1; j <= 3; j++)
            b[3 - j + 1][i] = a[i][j];
    for (int i = 1; i <= 3; i++)
        for (int j = 1; j <= 3; j++)
            a[i][j] = b[i][j];
}

// 交换a,b,c,d ---> d,a,b,c
void Exchange(char *a[4], char *b[4], char *c[4], char *d[4])
{
    char tmp[4] = {0};
    for (int i = 1; i <= 3; i++)
        tmp[i] = *a[i];

    for (int i = 1; i <= 3; i++)
        *(a[i]) = *(d[i]);
    for (int i = 1; i <= 3; i++)
        *(d[i]) = *(c[i]);
    for (int i = 1; i <= 3; i++)
        *(c[i]) = *(b[i]);
    for (int i = 1; i <= 3; i++)
        *(b[i]) = tmp[i];
}

// 旋转函数，分别实现了12个旋转函数，对应魔方的12种旋转操作

void R()
{
    char *a[4], *b[4], *c[4], *d[4];
    for (int i = 1; i <= 3; i++)
        a[i] = &(cube[1][i][3]);
    for (int i = 1; i <= 3; i++)
        b[i] = &(cube[5][i][3]);
    for (int i = 1; i <= 3; i++)
        c[i] = &(cube[2][3 - i + 1][1]);
    for (int i = 1; i <= 3; i++)
        d[i] = &(cube[6][i][3]);

    Exchange(a, b, c, d);
    ClockwiseRotate(cube[4]);
#ifdef RotateDebug
    Sprint();
#endif
}

void Ri()
{
    char *a[4], *b[4], *c[4], *d[4];
    for (int i = 1; i <= 3; i++)
        a[i] = &(cube[1][i][3]);
    for (int i = 1; i <= 3; i++)
        b[i] = &(cube[5][i][3]);
    for (int i = 1; i <= 3; i++)
        c[i] = &(cube[2][3 - i + 1][1]);
    for (int i = 1; i <= 3; i++)
        d[i] = &(cube[6][i][3]);

    Exchange(d, c, b, a);
    antiClockwiseRotate(cube[4]);
#ifdef RotateDebug
    Sprint();
#endif
}

void U()
{
    char *a[4], *b[4], *c[4], *d[4];
    for (int i = 1; i <= 3; i++)
        a[i] = &(cube[1][1][i]);
    for (int i = 1; i <= 3; i++)
        b[i] = &(cube[4][1][i]);
    for (int i = 1; i <= 3; i++)
        c[i] = &(cube[2][1][i]);
    for (int i = 1; i <= 3; i++)
        d[i] = &(cube[3][1][i]);

    Exchange(d, c, b, a);
    ClockwiseRotate(cube[5]);
#ifdef RotateDebug
    Sprint();
#endif
}

void Ui()
{
    char *a[4], *b[4], *c[4], *d[4];
    for (int i = 1; i <= 3; i++)
        a[i] = &(cube[1][1][i]);
    for (int i = 1; i <= 3; i++)
        b[i] = &(cube[4][1][i]);
    for (int i = 1; i <= 3; i++)
        c[i] = &(cube[2][1][i]);
    for (int i = 1; i <= 3; i++)
        d[i] = &(cube[3][1][i]);

    Exchange(a, b, c, d);
    antiClockwiseRotate(cube[5]);
#ifdef RotateDebug
    Sprint();
#endif
}

void F()
{
    char *a[4], *b[4], *c[4], *d[4];
    for (int i = 1; i <= 3; i++)
        a[i] = &(cube[5][3][i]);
    for (int i = 1; i <= 3; i++)
        b[i] = &(cube[3][3 - i + 1][3]);
    for (int i = 1; i <= 3; i++)
        c[i] = &(cube[6][1][3 - i + 1]);
    for (int i = 1; i <= 3; i++)
        d[i] = &(cube[4][i][1]);

    Exchange(d, c, b, a);
    ClockwiseRotate(cube[1]);
#ifdef RotateDebug
    Sprint();
#endif
}

void Fi()
{
    char *a[4], *b[4], *c[4], *d[4];
    for (int i = 1; i <= 3; i++)
        a[i] = &(cube[5][3][i]);
    for (int i = 1; i <= 3; i++)
        b[i] = &(cube[3][3 - i + 1][3]);
    for (int i = 1; i <= 3; i++)
        c[i] = &(cube[6][1][3 - i + 1]);
    for (int i = 1; i <= 3; i++)
        d[i] = &(cube[4][i][1]);

    Exchange(a, b, c, d);
    antiClockwiseRotate(cube[1]);
#ifdef RotateDebug
    Sprint();
#endif
}

void L()
{
    char *a[4], *b[4], *c[4], *d[4];
    for (int i = 1; i <= 3; i++)
        a[i] = &(cube[1][i][1]);
    for (int i = 1; i <= 3; i++)
        b[i] = &(cube[6][i][1]);
    for (int i = 1; i <= 3; i++)
        c[i] = &(cube[2][3 - i + 1][3]);
    for (int i = 1; i <= 3; i++)
        d[i] = &(cube[5][i][1]);

    Exchange(a, b, c, d);
    ClockwiseRotate(cube[3]);
#ifdef RotateDebug
    Sprint();
#endif
}

void Li()
{
    char *a[4], *b[4], *c[4], *d[4];
    for (int i = 1; i <= 3; i++)
        a[i] = &(cube[1][i][1]);
    for (int i = 1; i <= 3; i++)
        b[i] = &(cube[6][i][1]);
    for (int i = 1; i <= 3; i++)
        c[i] = &(cube[2][3 - i + 1][3]);
    for (int i = 1; i <= 3; i++)
        d[i] = &(cube[5][i][1]);

    Exchange(d, c, b, a);
    antiClockwiseRotate(cube[3]);
#ifdef RotateDebug
    Sprint();
#endif
}

void D()
{
    char *a[4], *b[4], *c[4], *d[4];
    for (int i = 1; i <= 3; i++)
        a[i] = &(cube[1][3][i]);
    for (int i = 1; i <= 3; i++)
        b[i] = &(cube[4][3][i]);
    for (int i = 1; i <= 3; i++)
        c[i] = &(cube[2][3][i]);
    for (int i = 1; i <= 3; i++)
        d[i] = &(cube[3][3][i]);

    Exchange(a, b, c, d);
    ClockwiseRotate(cube[6]);
#ifdef RotateDebug
    Sprint();
#endif
}

void Di()
{
    char *a[4], *b[4], *c[4], *d[4];
    for (int i = 1; i <= 3; i++)
        a[i] = &(cube[1][3][i]);
    for (int i = 1; i <= 3; i++)
        b[i] = &(cube[4][3][i]);
    for (int i = 1; i <= 3; i++)
        c[i] = &(cube[2][3][i]);
    for (int i = 1; i <= 3; i++)
        d[i] = &(cube[3][3][i]);

    Exchange(d, c, b, a);
    antiClockwiseRotate(cube[6]);
#ifdef RotateDebug
    Sprint();
#endif
}

void B()
{
    char *a[4], *b[4], *c[4], *d[4];
    for (int i = 1; i <= 3; i++)
        a[i] = &(cube[5][1][i]);
    for (int i = 1; i <= 3; i++)
        b[i] = &(cube[3][3 - i + 1][1]);
    for (int i = 1; i <= 3; i++)
        c[i] = &(cube[6][3][3 - i + 1]);
    for (int i = 1; i <= 3; i++)
        d[i] = &(cube[4][i][3]);

    Exchange(a, b, c, d);
    ClockwiseRotate(cube[2]);
#ifdef RotateDebug
    Sprint();
#endif
}

void Bi()
{
    char *a[4], *b[4], *c[4], *d[4];
    for (int i = 1; i <= 3; i++)
        a[i] = &(cube[5][1][i]);
    for (int i = 1; i <= 3; i++)
        b[i] = &(cube[3][3 - i + 1][1]);
    for (int i = 1; i <= 3; i++)
        c[i] = &(cube[6][3][3 - i + 1]);
    for (int i = 1; i <= 3; i++)
        d[i] = &(cube[4][i][3]);

    Exchange(d, c, b, a);
    antiClockwiseRotate(cube[2]);
#ifdef RotateDebug
    Sprint();
#endif
}

// ops -> operator 进行char变量对应操作
void StringToRotate(const char ops)
{
    if (ops == 'R')
        R();
    else if (ops == 'r')
        Ri();
    else if (ops == 'U')
        U();
    else if (ops == 'u')
        Ui();
    else if (ops == 'F')
        F();
    else if (ops == 'f')
        Fi();
    else if (ops == 'L')
        L();
    else if (ops == 'l')
        Li();
    else if (ops == 'D')
        D();
    else if (ops == 'd')
        Di();
    else if (ops == 'B')
        B();
    else if (ops == 'b')
        Bi();
    else
    {
        cout << "Wrong Rotate Type" << endl;
    }
}

// 用于进行与ops反方向旋转的函数
void StringToAntirotate(const char ops)
{
    if (ops == 'R')
        Ri();
    else if (ops == 'r')
        R();
    else if (ops == 'U')
        Ui();
    else if (ops == 'u')
        U();
    else if (ops == 'F')
        Fi();
    else if (ops == 'f')
        F();
    else if (ops == 'L')
        Li();
    else if (ops == 'l')
        L();
    else if (ops == 'D')
        Di();
    else if (ops == 'd')
        D();
    else if (ops == 'B')
        Bi();
    else if (ops == 'b')
        B();
    else
    {
        cout << "Wrong Rotate Type" << endl;
    }
}

// 获取相反的操作
char GetRevOpt(char ops)
{
    if (ops == 'R')
        return 'r';
    else if (ops == 'r')
        return 'R';
    else if (ops == 'U')
        return 'u';
    else if (ops == 'u')
        return 'U';
    else if (ops == 'F')
        return 'f';
    else if (ops == 'f')
        return 'F';
    else if (ops == 'L')
        return 'l';
    else if (ops == 'l')
        return 'L';
    else if (ops == 'D')
        return 'd';
    else if (ops == 'd')
        return 'D';
    else if (ops == 'B')
        return 'b';
    else if (ops == 'b')
        return 'B';
    else
    {
        cout << "Wrong Rotate Type in function GetRevOpt" << ' ' << ops << ' ' << '.' << endl;
    }
}

// 执行一段公式，Formula为公式对应数组，len为公式长度
void RunFormula(char *Formula, int len)
{
    for (int i = 0; i < len; i++)
        StringToRotate(Formula[i]);
}

// 用于手动测试旋转函数的函数
void TestRotate()
{
    char op = 0;
    while (1)
    {
        cin >> op;
        StringToRotate(op);
    }
}

// 用于生成测试数据的函数
/*
    生成测试案例的方法：
    将魔方状态初始化为已还原状态，并对其进行随机打乱
    向标准输出流中输出打乱后的魔方状态并输出打乱公式
    
    打乱步数作为参数传入TestCaseGenerator函数
    TestCaseGenerator函数同时提供一个Seed参数，若传入的Seed值为零，会以运行程序时的系统时间作为随机数种子，否则以传入的Seed值作为种子。
*/

// 用来将魔方重置到标准状态的函数
void ReSet()
{
    for (int k = 1; k <= 6; k++)
        for (int i = 1; i <= 3; i++)
            for (int j = 1; j <= 3; j++)
                cube[k][i][j] = StandardColor[k - 1];
}

// 生成测试案例的函数
void TestCaseGenerator(int len, int Seed = 0)
{
    ReSet();
    if (Seed == 0)
        Seed = int(time(0));
    cout << "生成测试数据所用的随机数种子为：" << Seed << endl;
    srand(Seed);
    cout << "生成测试案例的打乱公式为" << endl;
    for (int i = 1; i <= len; i++)
    {
        char op = opts[rand() % 12];
        cout << op << ' ';
        StringToRotate(op);
    }
    cout << endl
         << "生成魔方的状态为：" << endl;
    //Sprint();
}

// 判断是否已经完成了底层十字 已完成则返回1，未完成返回0
bool IsCross()
{
    char std = cube[6][2][2];
    bool res = (cube[6][1][2] == std && cube[6][2][1] == std && cube[6][2][3] == std && cube[6][3][2] == std);
#ifdef CrossDebug
    if (res)
    {
        //Sprint();
    }
#endif
    return res;
}

// 进行底层十字的函数
/*
    尝试使用迭代加深搜索寻找底层十字公式
*/
#ifdef CrossDebug
double Sumtime = 0;
double Maxtime = 0;
#endif

int lim = 0;
char stack[10] = {0};
bool flag = 0;
bool IDFS(int deep)
{
    //cout << deep << endl;
    if (IsCross())
        return 1;
    if (deep > lim)
        return 0;
    bool res = 0;
    for (int i = 0; i < 12; i++)
    {
        char op = opts[i];
        if (deep >= 2 && op == GetRevOpt(stack[deep - 1]))
            continue;
        StringToRotate(op);
        stack[deep] = op;
        res = res || IDFS(deep + 1);
        if (res == 1)
        {
#ifdef CrossDebug
            if (flag == 0)
            {
                cout << "成功找到底层十字公式" << endl;
                for (int i = 1; i <= deep; i++)
                    cout << stack[i] << ' ';
                cout << endl;
                flag = 1;
            }
#endif
            stack[deep] = 0;
            return 1;
        }
        stack[deep] = 0;
        StringToAntirotate(op);
    }
    return 0;
}

void SearchCross()
{
    flag = 0;
    double start, finish;
    start = clock();
    if (IsCross())
        return;
    for (int i = 1; i <= 8; i++)
    {
        lim = i;
        if (IDFS(1))
        {
            break;
        }
    }
    finish = clock();
#ifdef CrossDebug
    cout << "本次SearchCross用时为 ： " << (finish - start) / CLOCKS_PER_SEC << endl;
    if ((finish - start) / CLOCKS_PER_SEC > 1)
        cout << "More than One Second !" << endl;
    double time = 0;
    time = (finish - start) / CLOCKS_PER_SEC;
    Sumtime += time;
    Maxtime = max(Maxtime, time);
#endif
}

// 进行底层角块归位的函数
// 尚未施工完成
/*
    先把底层角块旋转到顶层
*/
void FloorCorner()
{
    // 还原(1,3)位置的角块
    bool flag1 = 0;
    for (int i = 1; i <= 4; i++)
    {
        if (cube[4][1][1] == 'Y' && cube[1][1][3] == 'G' && cube[5][3][3] == 'R')
        {
            RunFormula("RUr", 3);
            flag1 = 1;
            break;
        }
        if (cube[1][1][3] == 'Y' && cube[5][3][3] == 'G' && cube[4][1][1] == 'R')
        {
            RunFormula("fuF", 3);
            flag1 = 1;
            break;
        }
        if (cube[5][3][3] == 'Y')
        {
        }
        U();
    }
    if (!flag1)
    {
    }
}

//用于测试底层十字的函数
void CrossTester()
{
    int n = 200;
    lim = 0;
    for (int i = 0; i <= 9; i++)
        stack[i] = 0;
    freopen("CrossResult.txt", "w", stdout);
    for (int i = 1; i <= n; i++)
    {
        ReSet();
        TestCaseGenerator(50, time(0) + i * 5);
        cout << "TestCase " << i << endl;
        SearchCross();
    }
    cout << endl;
    cout << "Average : " << Sumtime / n << endl;
    cout << "Maxtime : " << Maxtime << endl
         << endl;
    fclose(stdout);
}

int main()
{
    // 初始化动态数组cube
    init();

    // 从标准输入流中读入魔方状态

    // 随机生成测试数据
    //TestCaseGenerator(60);

    //SearchCross();

    CrossTester();
}