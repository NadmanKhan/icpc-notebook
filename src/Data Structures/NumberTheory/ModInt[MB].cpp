#include <bits/stdc++.h>
// Tested By Ac
// submission : https://atcoder.jp/contests/abc238/submissions/29247261
// problem : https://atcoder.jp/contests/abc238/tasks/abc238_c

template <const int MOD>
struct ModInt
{
	int val;
	ModInt() { val = 0; }
	ModInt(long long v) { v += (v < 0 ? MOD : 0), val = (int)(v % MOD); }
	ModInt &operator+=(const ModInt &rhs)
	{
		val += rhs.val, val -= (val >= MOD ? MOD : 0);
		return *this;
	}
	ModInt &operator-=(const ModInt &rhs)
	{
		val -= rhs.val, val += (val < 0 ? MOD : 0);
		return *this;
	}
	ModInt &operator*=(const ModInt &rhs)
	{
		val = (int)((val * 1ULL * rhs.val) % MOD);
		return *this;
	}
	ModInt pow(long long n) const
	{
		ModInt x = *this, r = 1;
		while (n)
			r = ((n & 1) ? r * x : r), x = (x * x), n >>= 1;
		return r;
	}
	ModInt inv() const { return this->pow(MOD - 2); }
	ModInt &operator/=(const ModInt &rhs) { return *this = *this * rhs.inv(); }
	friend ModInt operator+(const ModInt &lhs, const ModInt &rhs) { return ModInt(lhs) += rhs; }
	friend ModInt operator-(const ModInt &lhs, const ModInt &rhs) { return ModInt(lhs) -= rhs; }
	friend ModInt operator*(const ModInt &lhs, const ModInt &rhs) { return ModInt(lhs) *= rhs; }
	friend ModInt operator/(const ModInt &lhs, const ModInt &rhs) { return ModInt(lhs) /= rhs; }
	friend bool operator==(const ModInt &lhs, const ModInt &rhs) { return lhs.val == rhs.val; }
	friend bool operator!=(const ModInt &lhs, const ModInt &rhs) { return lhs.val != rhs.val; }
	friend std::ostream &operator<<(std::ostream &out, const ModInt &m) { return out << m.val; }
	friend std::istream &operator>>(std::istream &in, ModInt &m) { return in >> m.val; }
	operator int() const { return val; }
};

const int MOD = 1e9 + 7;
using mint = ModInt<MOD>;