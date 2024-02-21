#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

ostream &operator<<(ostream &oss, const vector<int> &v)
{
    for (vector<int>::const_iterator p = v.begin(); p != v.end(); p++)
    {
        oss << ' ' << *p;
    }
    return oss;
}

const int PILE_CNT = 52;

struct Card
{
    char rank;
    char suit;
    Card(char r, char s) : rank(r), suit(s)
    {
    }
    bool match(const Card &rhs) const // right-hand side
    {
        return suit == rhs.suit || rank == rhs.rank;
    }
};
struct Pile
{
    stack<Card> cards;
    Pile *prev;
    Pile *next;
    void init()
    {
        while (!cards.empty())
        {
            cards.pop();
        }
        prev = nullptr;
        next = nullptr;
    }
};

Pile piles[1 + PILE_CNT];
Pile *head;

/*
    把 p1 和 p2 连接起来
*/
void connect(Pile *p1, Pile *p2)
{
    if (p1)
    {
        p1->next = p2;
    }
    if (p2)
    {
        p2->prev = p1;
    }
}

/*
    获取左侧第三个堆的堆首的纸牌
*/
Pile *getLeft3(Pile *p)
{
    for (int i = 0; i < 3; i++)
    {
        p = p->prev;
        if (p == nullptr)
        {
            return nullptr;
        }
    }
    return p;
}

void solve()
{
    Pile *from;
    Pile *to;
    Pile *cur;
    while (true)
    {
        from = nullptr;
        to = nullptr;
        cur = head->next;
        while (cur)
        {
            // 先考虑左边的第三个是否满足条件
            Pile *left3 = getLeft3(cur);
            if (left3 != nullptr && left3 != head)
            {
                if (left3->cards.top().match(cur->cards.top()))
                {
                    from = cur;
                    to = left3;
                    break;
                }
            }
            Pile *left1 = cur->prev;
            if (left1 != head)
            {
                if (left1->cards.top().match(cur->cards.top()))
                {
                    from = cur;
                    to = left1;
                    break;
                }
            }
            cur = cur->next;
        }
        if (!from) // 整体状态稳定，没有可以移动的牌了
        {
            break;
        }
        to->cards.push(from->cards.top());
        from->cards.pop();
        if (from->cards.empty()) // 如果 from 在移走最上面的那张牌之后空了
        {
            connect(from->prev, from->next);
        }
    }
}

int main(int argc, char *argv[])
{
    std::ifstream file_input("./uva127/uva127.txt");
    std::streambuf *cinbuf = std::cin.rdbuf();
    std::cin.rdbuf(file_input.rdbuf());

    string s;
    bool end = false;
    head = &(piles[0]);
    head->init();
    head->next = &(piles[1]);

    while (true)
    {
        for (int i = 1; i <= PILE_CNT; i++)
        {
            if (cin >> s && s.size() == 2)
            {
                Pile &p = piles[i];
                p.init();
                p.prev = &(piles[i - 1]);
                if (i + 1 <= PILE_CNT)
                {
                    p.next = &(piles[i + 1]);
                }
                p.cards.push(Card(s[0], s[1]));
            }
            else // 读取到 hash 符号 #
            {
                return 0;
            }
        }
        solve();
        Pile *cur = head->next;
        vector<int> pile_vec;
        while (cur)
        {
            pile_vec.push_back(cur->cards.size());
            cur = cur->next;
        }
        cout << pile_vec.size() << " pile" << (pile_vec.size() > 1 ? "s" : "") << " remaining:" << pile_vec << '\n';
    }

    return 0;
}
