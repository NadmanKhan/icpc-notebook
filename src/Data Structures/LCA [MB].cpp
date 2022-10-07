struct LCA
{
private:
	int n, lg;
	std::vector<int> depth;
	std::vector<std::vector<int>> up;
	std::vector<std::vector<int>> g;

public:
	LCA() : n(0), lg(0) {}

	LCA(int _n)
	{
		this->n = _n;
		lg = (int)log2(n) + 2;
		depth.resize(n + 5, 0);
		up.resize(n + 5, std::vector<int>(lg, 0));
		g.resize(n + 1);
	}

	LCA(std::vector<std::vector<int>> &graph) : LCA((int)graph.size())
	{
		for (int i = 0; i < (int)graph.size(); i++)
			g[i] = graph[i];

		dfs(1, 0);
	}

	void dfs(int curr, int p)
	{
		up[curr][0] = p;
		for (int next : g[curr])
		{
			if (next == p)
				continue;
			depth[next] = depth[curr] + 1;
			up[next][0] = curr;
			for (int j = 1; j < lg; j++)
				up[next][j] = up[up[next][j - 1]][j - 1];
			dfs(next, curr);
		}
	}

	void clear_v(int a)
	{
		g[a].clear();
	}

	void clear(int n_ = -1)
	{
		if (n_ == -1)
			n_ = ((int)(g.size())) - 1;

		for (int i = 0; i <= n_; i++)
		{
			g[i].clear();
		}
	}

	void add(int a, int b)
	{
		g[a].push_back(b);
	}

	int par(int a)
	{
		return up[a][0];
	}

	int get_lca(int a, int b)
	{
		if (depth[a] < depth[b])
			std::swap(a, b);

		int k = depth[a] - depth[b];
		for (int j = lg - 1; j >= 0; j--)
		{
			if (k & (1 << j))
				a = up[a][j];
		}

		if (a == b)
			return a;

		for (int j = lg - 1; j >= 0; j--)
			if (up[a][j] != up[b][j])
			{
				a = up[a][j];
				b = up[b][j];
			}

		return up[a][0];
	}

	int get_dist(int a, int b)
	{
		return depth[a] + depth[b] - 2 * depth[get_lca(a, b)];
	}
};