#include <bits/stdc++.h>

using namespace std;

const int N = 3e4 + 5;
const int blck = sqrt(N) + 1;

struct Query
{
	int l, r, i;
	bool operator<(const Query q) const
	{
		if (this->l / blck == q.l / blck)
			return this->r < q.r;
		return this->l / blck < q.l / blck;
	}
};

vector<int> mos_alogorithm(vector<Query> &queries, vector<int> &a)
{
	vector<int> answers(queries.size());
	sort(queries.begin(), queries.end());

	int sza = 1e6 + 5;
	vector<int> freq(sza);

	int cnt = 0;

	auto add = [&](int x) -> void
	{
		freq[x]++;
		if (freq[x] == 1)
			cnt++;
	};

	auto remove = [&](int x) -> void
	{
		freq[x]--;
		if (freq[x] == 0)
			cnt--;
	};

	int l = 0;
	int r = -1;
	for (Query q : queries)
	{
		while (l > q.l)
		{
			l--;
			add(a[l]);
		}
		while (r < q.r)
		{
			r++;
			add(a[r]);
		}
		while (l < q.l)
		{
			remove(a[l]);
			l++;
		}
		while (r > q.r)
		{
			remove(a[r]);
			r--;
		}
		answers[q.i] = cnt;
	}
	return answers;
}

int main()
{
	int n;
	cin >> n;

	vector<int> a(n);
	for (int i = 0; i < n; i++)
		cin >> a[i];

	int q;
	cin >> q;

	vector<Query> qr(q);

	for (int i = 0; i < q; i++)
	{
		int l, r;
		cin >> l >> r;

		l--, r--;
		qr[i].l = l, qr[i].r = r, qr[i].i = i;
	}

	vector<int> res = mos_alogorithm(qr, a);

	for (int i = 0; i < q; i++)
		cout << res[i] << endl;

	return 0;
}