#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define var(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "
#define mem(x, n) memset(x, n, sizeof(x))
#define all(x) x.begin(), x.end()
#define sz(x) ((int)x.size())
#define vec vector
#define endl "\n"

class DSU
{
	std::vector<int> p, csz;

public:
	DSU() {}

	DSU(int dsz) // Max size
	{
		//Default empty
		p.resize(dsz + 5, 0), csz.resize(dsz + 5, 0);

		init(dsz);
	}

	void init(int n)
	{
		// n = size
		for (int i = 0; i <= n; i++)
		{
			p[i] = i, csz[i] = 1;
		}
	}

	//Return parent Recursively
	int get(int x)
	{
		if (p[x] != x)
			p[x] = get(p[x]);

		return p[x];
	}

	// Return Size
	int getSize(int x) { return csz[get(x)]; }
	// Return if Union created Succesffully or false if they are already in Union
	bool merge(int x, int y)
	{
		x = get(x), y = get(y);
		if (x == y)
			return false;

		if (csz[x] > csz[y])
			std::swap(x, y);

		p[x] = y;
		csz[y] += csz[x];

		return true;
	}
};

void runCase([[maybe_unused]] const int &TC)
{
	int n, m;
	cin >> n >> m;

	auto g = vec(n + 1, set<int>());

	auto dsu = DSU(n + 1);

	for (int i = 0; i < m; i++)
	{
		int u, v;
		cin >> u >> v;

		g[u].insert(v);
		g[v].insert(u);
	}

	set<int> elligible;

	for (int i = 1; i <= n; i++)
	{
		elligible.insert(i);
	}

	int i = 1;
	int cnt = 0;

	while (sz(elligible))
	{
		cnt++;
		queue<int> q;
		q.push(*elligible.begin());
		elligible.erase(elligible.begin());

		while (sz(q))
		{
			int fr = q.front();
			q.pop();

			auto v = elligible.begin();

			while (v != elligible.end())
			{
				if (g[fr].find(*v) == g[fr].end())
				{
					q.push(*v);
					v = elligible.erase(v);
				}
				else
				{
					v++;
				}
			}
		}
	}

	cout << cnt - 1 << endl;
}

int main()
{
	ios_base::sync_with_stdio(false), cin.tie(0);

	int t = 1;
	//cin >> t;

	for (int tc = 1; tc <= t; tc++)
		runCase(tc);

	return 0;
}