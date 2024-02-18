// 需在根目录下编译运行
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

using namespace std;

vector<int> tokens;
struct Transition
{
    // 当前 transition 的每个 place 上应该被拿走的 token 的数量
    unordered_map<int, int> input;
    // 会被放入 token 的 place，每个 place 会放入 1 个，这里面的 place 会有重复的
    vector<int> output;

    bool enabled() const
    {
        for (auto entry : input)
        {
            if (tokens[entry.first] < entry.second)
            { // 如果该 place 的 tokens 不够
                return false;
            }
        }
        return true;
    }

    void fire() const
    {
        for (auto entry : input)
        {
            tokens[entry.first] -= entry.second;
        }
        for (auto ele : output)
        {
            tokens[ele] += 1;
        }
    }
};

vector<Transition> Trans;
/*
    取出第一个可以转移的转移序列
*/
int enabledTrans()
{
    for (int i = 0; i < Trans.size(); i++)
    {
        if (Trans[i].enabled())
        {
            return i;
        }
    }
    return -1;
}

int main(int argc, char *argv[])
{
    std::ifstream file_input("./uva804/uva804.txt");
    // 将输入重定向到 ifstream 对象
    std::streambuf *cinbuf = std::cin.rdbuf(); // 保存原始输入缓冲区
    std::cin.rdbuf(file_input.rdbuf());        // 将输入重定向到文件

    int NP, NT, NF;
    for (int kase = 1; cin >> NP && NP; kase++)
    {
        tokens.resize(NP);
        for (int i = 0; i < NP; i++)
        {
            cin >> tokens[i];
        }
        cin >> NT;
        Trans.clear();
        Trans.resize(NT);
        for (int i = 0; i < NT; i++)
        {
            int pi; // place index
            auto &t = Trans[i];
            while (cin >> pi && pi != 0)
            {
                if (pi < 0)
                {
                    t.input[-pi - 1] += 1;
                }
                else
                {
                    t.output.push_back(pi - 1);
                }
            }
        }
        cin >> NF;
        int cnt = 0;
        bool live = true;
        for (int nf = 0; nf < NF; nf++)
        {
            int first_enabled_index = enabledTrans();
            if (first_enabled_index == -1)
            {
                live = false;
                break;
            }
            Trans[first_enabled_index].fire();
            cnt += 1;
        }
        cout << "Case " << kase << ": ";
        if (live)
        {
            cout << "still live after " << NF << " transitions\n";
        }
        else
        {
            cout << "dead after " << cnt << " transitions\n";
        }
        cout << "Places with tokens:";
        for (int pi = 0; pi < NP; pi++)
        {
            if (tokens[pi])
            {
                cout << " " << pi + 1 << " (" << tokens[pi] << ")";
            }
        }
        cout << "\n";
    }
    return 0;
}
