#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const int MAXN = 1004;
int N;
int BFS[MAXN];
int DFS[MAXN];
int BFSIDX[MAXN]; // BFS 数组中的每个元素的索引值

vector<int> ans[MAXN];

/*
    l: 根节点的 index
    r: 树的右边界的 index
    l 到 r 是一棵完整的树
    相对来说，处理的是 DFS 的序列
*/
void solve(int l, int r)
{
    if (l == r)
    {
        return;
    }
    int cur_root = DFS[l];
    int i = l + 1;
    int last_i = i;
    // 先把 DFS[i] 放进去，因为以 curNode 为根节点的 DFS 的第二个节点必然是 curNode 的子节点
    ans[cur_root].push_back(DFS[i]);
    i += 1;
    while (i <= r) // i 从 l + 2 开始遍历
    {
        int last_node = ans[cur_root].back();
        int cur_node = DFS[i];
        // 当前的节点比 cur_root 的第一个子节点的值要大
        // 并且是 BFS 中 last_node 的下一个值 => 确保是另一个子节点
        if (cur_node > last_node && BFSIDX[cur_node] == BFSIDX[last_node] + 1)
        {
            solve(last_i, i - 1); // i - 1 => 把 i 这个右子树的根节点排除掉
            ans[cur_root].push_back(cur_node);
            last_i = i; // 此时 last_i 变成了右子树的根节点，即: i
        }
        ++i;
    }
    solve(last_i, r);
}

int main(int argc, char *argv[])
{
    std::ifstream file_input("./uva10410/uva10410.txt");
    std::streambuf *cinbuf = std::cin.rdbuf();
    std::cin.rdbuf(file_input.rdbuf());

    while (cin >> N)
    {
        for (int i = 1; i <= N; i++)
        {
            cin >> BFS[i];
            BFSIDX[BFS[i]] = i;
            ans[i].clear();
        }
        for (int i = 1; i <= N; i++)
        {
            cin >> DFS[i];
        }
        solve(1, N);
        for (int i = 1; i <= N; i++)
        {
            cout << i << ':';
            for (int j = 0; j < ans[i].size(); j++)
            {
                cout << " " << ans[i][j];
            }
            cout << '\n';
        }
    }
    return 0;
}
