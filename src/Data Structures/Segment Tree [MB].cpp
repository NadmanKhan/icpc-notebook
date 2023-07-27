template <typename T, T(*op)(T, T)>
struct SegTree
{
private:
	std::vector<T> segt;
	int n;
	T e;
	int left(int si) { return si * 2; }
	int right(int si) { return si * 2 + 1; }
	int midpoint(int ss, int se) { return (ss + (se - ss) / 2); }
	T query(int ss, int se, int qs, int qe, int si)
	{
		if (se < qs || qe < ss)
			return e;
		if (qs <= ss && qe >= se)
			return segt[si];
		int mid = midpoint(ss, se);
		return op(query(ss, mid, qs, qe, left(si)), query(mid + 1, se, qs, qe, right(si)));
	}
	void update(int ss, int se, int key, int si, T val)
	{
		if (ss == se)
		{
			segt[si] = val;
			return;
		}
		int mid = midpoint(ss, se);
		if (key > mid)
			update(mid + 1, se, key, right(si), val);
		else
			update(ss, mid, key, left(si), val);
		segt[si] = op(segt[left(si)], segt[right(si)]);
	}
	void build(const std::vector<T> &a, int si, int ss, int se)
	{
		if (ss == se)
		{
			segt[si] = a[ss];
			return;
		}
		int mid = midpoint(ss, se);
		build(a, left(si), ss, mid);
		build(a, right(si), mid + 1, se);
		segt[si] = op(segt[left(si)], segt[right(si)]);
	}
public:
	SegTree() : n(0) {}
	SegTree(int sz, T _e)
	{
		this->e = _e;
		this->n = sz;
		segt.resize(n * 4 + 5, _e);
	}
	SegTree(const std::vector<T> &arr, T _e) : SegTree((int)arr.size(), _e) { init(arr); }
	void init(const std::vector<T> &arr) { this->n = (int)(arr.size());build(arr, 1, 0, n - 1); }
	T get(int qs, int qe) { return query(0, n - 1, qs, qe, 1); }
	void set(int key, T val) { update(0, n - 1, key, 1, val); }
};
int op(int a, int b)
{
	return min(a, b);
}