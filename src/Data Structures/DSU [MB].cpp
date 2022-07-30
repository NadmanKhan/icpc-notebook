#include <bits/stdc++.h>

// O based
class DSU
{
	std::vector<int> p, csz;

public:
	DSU() {}

	//0 based
	DSU(int mx_size)
	{
		//Default empty
		p.resize(mx_size, 0), csz.resize(mx_size, 0);

		init(mx_size);
	}

	void init(int n)
	{
		// n = size
		for (int i = 0; i < n; i++)
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
	int get_comp_size(int component) { return csz[get(component)]; }
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