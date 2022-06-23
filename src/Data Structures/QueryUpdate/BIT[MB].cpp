struct BIT
{
private:
	std::vector<long long> mArray;

public:
	BIT(int sz) // Max size of the array
	{
		mArray.resize(sz + 1, 0);
	}

	void build(const std::vector<long long> &list)
	{
		for (int i = 1; i <= list.size(); i++)
		{
			mArray[i] = list[i];
		}

		for (int ind = 1; ind <= mArray.size(); ind++)
		{
			int ind2 = ind + (ind & -ind);
			if (ind2 <= mArray.size())
			{
				mArray[ind2] += mArray[ind];
			}
		}
	}

	long long prefix_query(int ind)
	{
		int res = 0;
		for (; ind > 0; ind -= (ind & -ind))
		{
			res += mArray[ind];
		}
		return res;
	}

	long long range_query(int from, int to)
	{
		return prefix_query(to) - prefix_query(from - 1);
	}

	void add(int ind, long long add)
	{
		for (; ind < mArray.size(); ind += (ind & -ind))
		{
			mArray[ind] += add;
		}
	}
};