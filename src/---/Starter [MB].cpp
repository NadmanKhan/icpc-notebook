#if defined LOCAL && !defined ONLINE_JUDGE
#include "debug.cpp"
#else
#include <bits/stdc++.h>
using namespace std;
#define dbg(...) ;
#endif

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

#define mem(x, n) memset(x, n, sizeof(x))
#define all(x) x.begin(), x.end()
#define sz(x) ((int)(x).size())
#define vec vector

inline bool read(auto&... a) { return (((cin >> a) ? true : false) && ...); }

inline void print(const auto&... a) { ((cout << a), ...); }
inline void println(const auto&... a) { print(a..., '\n'); }

void run_case([[maybe_unused]] const int& TC) {}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(0);

    int tt = 1;
    read(tt);

    for (int tc = 1; tc <= tt; tc++)
        run_case(tc);

    return 0;
}