#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
namespace pbds = __gnu_pbds;

template <class T>
using ordered_set = pbds::tree<T, pbds::null_type, std::less<T>,
                               pbds::rb_tree_tag,
                               pbds::tree_order_statistics_node_update>;
template <class K, class V>
using hash_map = pbds::gp_hash_table<K, V>;
