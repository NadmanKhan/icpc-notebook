#include<bits/stdc++.h>

/* 
	tested by ac 
	submission: https://codeforces.com/contest/432/submission/145953901
	problem: https://codeforces.com/contest/432/problem/D
*/ 
std::vector<int> z_function(const std::string &s)
{
	int n = (int)s.size();
	std::vector<int> z(n, 0);
	for (int i = 1, l = 0, r = 0; i < n; i++)
	{
		if (i <= r)
			z[i] = std::min(r - i + 1, z[i - l]);
		while (i + z[i] < n && s[z[i]] == s[i + z[i]])
			z[i]++;
		if (i + z[i] - 1 > r)
			l = i, r = i + z[i] - 1;
	}
	return z;
}