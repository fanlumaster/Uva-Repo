#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 64 + 4;
// 方向: (0,0), (0,1), (1,0), (1,1) => NW, NE, SW, SE
const int DX[] = {0, 0, 1, 1};
const int DY[] = {0, 1, 0, 1};
int N;
char IMG[MAXN][MAXN];

/*
    path: 当前层所对应的块转化成五进制的值
    base5: 从根节点开始，当前的 NW/NE/SW/SE 所代表的数字应该乘上的值，初始是 1，每深入一层，就要乘以一个 5
    把黑色的像素块转成五进制值，放入 ans 中
*/
void countBlack(int x, int y, int len, vector<int> &blacks, int path = 0, int base5 = 1)
{
    int black_pixel_cnt = 0;
    int half_len = len / 2;
    for (int i = x; i < x + len; i++)
    {
        for (int j = y; j < y + len; j++)
        {
            black_pixel_cnt += IMG[i][j] - '0';
        }
    }
    if (black_pixel_cnt == 0) // 全部为白色像素块
    {
        return;
    }
    if (black_pixel_cnt == len * len) // 全部为黑色像素块
    {
        blacks.push_back(path);
        return;
    }
    for (int di = 0; di < 4; di++)
    {
        countBlack(x + DX[di] * half_len, y + DY[di] * half_len, half_len, blacks, path + base5 * (di + 1), base5 * 5);
    }
}

/*
    path: 五进制的一个值，即五进制序列中的一个元素
    x: 正方形的左上角的 x 坐标
    y: 正方形的左上角的 y 坐标
    len: 当前正方形的边长
*/
void draw(int path, int x, int y, int len)
{
    if (path == 0)
    {
        for (int i = x; i < x + len; i++)
        {
            for (int j = y; j < y + len; j++)
            {
                IMG[i][j] = '*';
            }
        }
        return;
    }
    int di = path % 5 - 1; // direction index
    int half_len = len / 2;
    draw(path / 5, x + DX[di] * half_len, y + DY[di] * half_len, half_len);
}

int main(int argc, char *argv[])
{
    std::ifstream file_input("./uva806/uva806.txt");
    // 将输入重定向到 ifstream 对象
    std::streambuf *cinbuf = std::cin.rdbuf(); // 保存原始输入缓冲区
    std::cin.rdbuf(file_input.rdbuf());        // 将输入重定向到文件

    for (int kase = 1; cin >> N && N; kase++)
    {
        if (kase > 1)
        {
            puts("");
        }
        cout << "Image " << kase << '\n';
        if (N > 0) // 输入是 0 1 矩阵的情况，要转成五进制序列
        {
            for (int i = 0; i < N; i++)
            {
                cin >> IMG[i];
            }
            vector<int> blacks;
            countBlack(0, 0, N, blacks);
            sort(begin(blacks), end(blacks));
            int sz = blacks.size();
            for (int i = 0; i < sz; i++)
            {
                cout << blacks[i] << ((i % 12 == 11 || i == sz - 1) ? '\n' : ' ');
            }
            cout << "Total number of black nodes = " << sz << '\n';
        }
        else // 输入是五进制序列的情况，要转成 . * 图
        {
            int p;
            memset(IMG, 0, sizeof(IMG));
            N = -N;
            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < N; j++)
                {
                    IMG[i][j] = '.';
                }
            }
            while (cin >> p && p >= 0)
            {
                draw(p, 0, 0, N);
            }
            for (int i = 0; i < N; i++)
            {
                cout << IMG[i] << '\n';
            }
        }
    }
    return 0;
}
