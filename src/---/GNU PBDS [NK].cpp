#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/trie_policy.hpp>
namespace pbds = __gnu_pbds;

// - `find_by_order(i)` to get the `i`-th element (0-indexed)
// - `order_of_key(k)` to get the number of elements/keys strictly smaller than the key `k`
template <class Key,
          class Mapped = pbds::null_type,
          class Cmp_Fn = std::less<Key>>
using Ordered_Map = pbds::tree<Key,
                               Mapped,
                               Cmp_Fn,
                               pbds::rb_tree_tag,
                               pbds::tree_order_statistics_node_update>;
template <class Key,
          class Cmp_Fn = std::less<Key>>
using Ordered_Set = pbds::tree<Key,
                               pbds::null_type,
                               Cmp_Fn,
                               pbds::rb_tree_tag,
                               pbds::tree_order_statistics_node_update>;

template <class Key,
          class Mapped,
          class Hash_Fn = std::hash<Key>,
          class Eq_Fn = std::equal_to<Key>>
using Hash_Map = pbds::gp_hash_table<Key,
                                     Mapped,
                                     Hash_Fn,
                                     Eq_Fn>;
template <class Key,
          class Hash_Fn = std::hash<Key>,
          class Eq_Fn = std::equal_to<Key>>
using Hash_Set = pbds::gp_hash_table<Key,
                                     pbds::null_type,
                                     Hash_Fn,
                                     Eq_Fn>;

// GNU PBDS prefix-search based "PATRICIA" trie:
template <class Key,
          class Mapped,
          class Access_Traits = pbds::trie_string_access_traits<>>
using Trie_Map = pbds::trie<Key,
                            Mapped,
                            Access_Traits,
                            pbds::pat_trie_tag,
                            pbds::trie_prefix_search_node_update>;
template <class Key,
          class Access_Traits = pbds::trie_string_access_traits<>>
using Trie_Set = pbds::trie<Key,
                            pbds::null_type,
                            Access_Traits,
                            pbds::pat_trie_tag,
                            pbds::trie_prefix_search_node_update>;

template <class Int_Type = int>
struct Trie_Bits_Access_Traits {
    // Bit-Access Definitions (not in the docs)
    using bit_const_iterator = std::_Bit_const_iterator;
    using bit_field_type = std::_Bit_type;
    static constexpr int bit_field_size = std::_S_word_bit;

    // Key-Type Definitions
    using size_type = int;
    using key_type = Int_Type;
    using const_key_reference = const key_type&;

    // Element-Type Definitions
    using e_type = bool;
    using const_iterator = bit_const_iterator;
    static constexpr int min_e_val = 0;
    static constexpr int max_e_val = 1;
    static constexpr int max_size = 2;

    // Methods
    static constexpr size_type e_pos(e_type e) { return e; }
    static constexpr const_iterator begin(const_key_reference r_key) {
        return bit_const_iterator((bit_field_type*)(&r_key), 0);
    }
    static constexpr const_iterator end(const_key_reference r_key) {
        return bit_const_iterator((bit_field_type*)(&r_key), bit_field_size - __builtin_clzll(r_key));
    }
};
