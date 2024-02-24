#include <iostream>
#include <fstream>
#include <deque> // 双端队列
#include <list>  // 双端列表
#include <set>
#include <string>

using namespace std;

typedef deque<int> Pile;

const int CARD_NUM = 52; // 去掉了大小王的牌的数量
Pile cards;              // 手里的牌
Pile allPiles[7];        // 默认会初始化
list<Pile *> piles;      // 桌面上的 7 堆
set<string> phases;      // 已经出现过的牌的状态

/*
    对当前的桌子上加手中的牌的状态进行编码
*/
void encode(string &ans)
{
    ans.clear();
    for (auto &pp : piles)
    {
        Pile &p = *pp;
        for (auto c : p)
        {
            ans += "(" + to_string(c) + ")";
        }
        ans += '|';
    }
    for (auto c : cards)
    {
        ans += "(" + to_string(c) + ")";
    }
}

/*
    p: 把手上的牌放入的堆，p 是已经放入后的状态
*/
void procPile(Pile &p)
{
    int n = p.size();
    if (n < 3)
    {
        return;
    }
    // 三张牌加起来最大是 30，所以，这里只需要判断是否可以被 10 整除即可
    if ((p[0] + p[1] + p.back()) % 10 == 0)
    {
        cards.push_back(p[0]);
        cards.push_back(p[1]);
        cards.push_back(p.back());
        p.pop_front();
        p.pop_front();
        p.pop_back();
        procPile(p);
        return;
    }
    if ((p[0] + p[n - 2] + p[n - 1]) % 10 == 0)
    {
        cards.push_back(p[0]);
        cards.push_back(p[n - 2]);
        cards.push_back(p[n - 1]);
        p.pop_front();
        p.pop_back();
        p.pop_back();
        procPile(p);
        return;
    }
    if ((p[n - 3] + p[n - 2] + p[n - 1]) % 10 == 0)
    {
        cards.push_back(p[n - 3]);
        cards.push_back(p[n - 2]);
        cards.push_back(p[n - 1]);
        p.pop_back();
        p.pop_back();
        p.pop_back();
        procPile(p);
        return;
    }
}

bool simulate(int time)
{
    if (piles.empty())
    {
        cout << "Win : " << time << endl;
        return false;
    }
    if (cards.empty())
    {
        cout << "Loss: " << time << endl;
        return false;
    }
    string pha;
    encode(pha);
    if (phases.count(pha))
    {
        cout << "Draw: " << time << endl;
        return false;
    }
    else
    {
        phases.insert(pha);
    }

    int c = cards.front();
    cards.pop_front();
    // 把需要处理的 Pile 挪到最右端
    piles.push_back(piles.front());
    piles.pop_front();
    Pile &p = *(piles.back());
    p.push_back(c);
    procPile(p);
    if (p.empty())
    {
        piles.pop_back();
    }
    return true;
}

int main(int argc, char *argv[])
{
    std::ifstream file_input("./uva246/uva246.txt");
    std::streambuf *cinbuf = std::cin.rdbuf();
    std::cin.rdbuf(file_input.rdbuf());

    while (true)
    {
        cards.clear();
        piles.clear();
        phases.clear();
        // 初始化手中的牌
        for (int i = 0; i < CARD_NUM; i++)
        {
            int c;
            cin >> c;
            if (c == 0)
            {
                return 0;
            }
            cards.push_back(c);
        }
        // 放置初始的 7 张牌
        for (int i = 0; i < 7; i++)
        {
            Pile &p = allPiles[i];
            p.clear();
            p.push_back(cards.front());
            cards.pop_front();
            piles.push_back(&p);
        }
        int t = 7;
        while (true)
        {
            if (!simulate(t++))
            {
                break;
            }
        }
    }
    return 0;
}
