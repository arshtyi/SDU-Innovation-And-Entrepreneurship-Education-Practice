#include <bits/stdc++.h>
using namespace std;
struct card
{
    int dx = 0, hs = 0;
    card() {}
    card(int d, int h) : dx(d), hs(h) {}
    bool operator==(const card &c) const { return dx == c.dx; }
    bool operator<(const card &c) const { return dx < c.dx; }
    card operator+(const int &c) const { return card(dx + c, hs); }
};

int f1 = 0, f2 = 0, f3 = 0, f4 = 0, f5 = 0, f6 = 0, f7 = 0, f8 = 0, f9 = 0;
card cs[5];
vector<card> v;

bool zhadan() { return ((cs[0] == cs[1] && cs[1] == cs[2] && cs[2] == cs[3]) || (cs[1] == cs[2] && cs[2] == cs[3] && cs[3] == cs[4])); }
bool tonghua() { return cs[0].hs == cs[1].hs && cs[1].hs == cs[2].hs && cs[2].hs == cs[3].hs && cs[3].hs == cs[4].hs; }
bool sandaier()
{
    if (cs[1] == cs[2])
        return cs[0] == cs[1] && cs[3] == cs[4];
    if (cs[2] == cs[3])
        return cs[0] == cs[1] && cs[3] == cs[4];
    return false;
}
bool sunzi()
{
    if (cs[0] + 1 == cs[1])
        if (cs[1] + 1 == cs[2])
            if (cs[2] + 1 == cs[3])
                if (cs[3] + 1 == cs[4])
                    return true;
    return false;
}
bool santiao() { return (cs[0] == cs[1] && cs[1] == cs[2]) || (cs[1] == cs[2] && cs[2] == cs[3]) || (cs[2] == cs[3] && cs[3] == cs[4]); }
bool liangdui() { return (cs[0] == cs[1] && (cs[2] == cs[3] || cs[3] == cs[4])) || (cs[1] == cs[2] && cs[3] == cs[4]); }
bool yidui() { return cs[0] == cs[1] || cs[1] == cs[2] || cs[2] == cs[3] || cs[3] == cs[4]; }
bool tonghuasun() { return tonghua() && sunzi(); }
void pandaun()
{
    sort(cs, cs + 5);
    if (tonghuasun())
        f1++;
    else if (zhadan())
        f2++;
    else if (sandaier())
        f3++;
    else if (tonghua())
        f4++;
    else if (sunzi())
        f5++;
    else if (santiao())
        f6++;
    else if (liangdui())
        f7++;
    else if (yidui())
        f8++;
    else
        f9++;
}

int main()
{
    int da, db, ta1, tb1, ta2, tb2;
    cin >> da >> db >> ta1 >> tb1 >> ta2 >> tb2;
    for (int i = 0; i < da; ++i)
        for (int j = 0; j < db; ++j)
            if (!((i == ta1 && j == tb1) || (i == ta2 && j == tb2)))
                v.emplace_back(i, j);
    int n = da * db - 2;
    card ka1(ta1, tb1), ka2(ta2, tb2);
    for (int i = 0; i < n - 2; ++i)
        for (int j = i + 1; j < n - 1; ++j)
            for (int k = j + 1; k < n; ++k)
            {
                cs[0] = ka1, cs[1] = ka2, cs[2] = v[i], cs[3] = v[j], cs[4] = v[k];
                pandaun();
            }
    cout << f1 << ' ' << f2 << ' ' << f3 << ' ' << f4 << ' ' << f5 << ' ' << f6 << ' ' << f7 << ' ' << f8 << ' ' << f9 << ' ';
    return 0;
}
