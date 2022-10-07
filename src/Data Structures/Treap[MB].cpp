#include <bits/stdc++.h>

#define mem(x, n) memset(x, n, sizeof(x))
#define all(x) x.begin(), x.end()
#define endl "\n"

#include <ext/pb_ds/assoc_container.hpp> // Common file

// using namespace __gnu_pbds;

// https://codeforces.com/blog/entry/11080
//cout<<*X.find_by_order(4)<<endl; // 16
// cout<<(end(X)==X.find_by_order(6))<<endl; // true
// cout<<X.order_of_key(-5)<<endl;  // 0
template <typename T, typename order = std::less<T>>
using ordered_set = __gnu_pbds::tree<T, __gnu_pbds::null_type, order, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;

int main()
{
	ordered_set<int> X;

	std::cout << *X.find_by_order(4) << endl;									// 16
	std::cout << (std::end(X) == X.find_by_order(6)) << endl; // true
	std::cout << X.order_of_key(-5) << endl;									// 0

	return 0;
}