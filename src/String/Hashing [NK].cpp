// Primes suitable for use as the constant base in a polynomial rolling hash function.
constexpr std::array<int, 10>
    prime_bases = {257, 263, 269, 271, 277, 281, 283, 293, 307, 311};
// Primes suitable for use as modulus.
constexpr std::array<int, 10>
    prime_moduli = {1000000007, 1000000009, 1000000021, 1000000033, 1000000087,
                    1000000093, 1000000097, 1000000103, 1000000123, 1000000181};

/**
 * @brief A data structure for computing polynomial hashes of sequence keys.
 * For a given key defined as an integral sequence of n elements S[0], S[1], ...,
 * S[n - 1], this structure builds and stores for each prefix S[0...i] the hash value
 * H(i) = S[0] * B^i + S[1] * B^(i - 1) + ... + S[i] * B^0, modulo M.
 * @tparam Base The base B. Should be a prime to reduce chances of collision.
 * @tparam Modulus The modulus M. Should be a prime to reduce chances of collision.
 */
template <std::uint64_t Base, std::uint64_t Modulus>
class Polynomial_hasher {
public:
    using int_type = std::uint64_t;
    using value_type = int_type;
    using size_type = std::size_t;

    static constexpr int_type B = Base;
    static constexpr int_type M = Modulus;

protected:
    // Base power
    static std::vector<int_type> bpow_;
    // Prefix hash
    std::vector<int_type> pref_hash_;
    // Suffix hash
    std::vector<int_type> suff_hash_;
    // Flag for hashing bidirectionally
    bool bidir_ = false;

public:
    /**
     * @brief Default constructor
     */
    Polynomial_hasher() {}

    /**
     * @brief Constructors and builds the hash from a range (a "key").
     * @tparam InputIter Type of the iterator of the range
     * @param from Iterator pointing to the start of the range
     * @param until Iterator pointing to the end (one past the last element) of the range
     * @param bidir Flag for hashing bidirectionally
     */
    template <class InputIter>
    Polynomial_hasher(InputIter from, InputIter until, bool bidir = false) {
        build_hash(from, until, bidir);
    }

    /**
     * @brief Builds the hash from a range (a "key").
     * @tparam InputIter Type of the iterator of the range
     * @param from Iterator pointing to the start of the range
     * @param until Iterator pointing to the end (one past the last element) of
     * the range
     * @param bidir Flag for hashing bidirectionally
     */
    template <class InputIter>
    void build_hash(InputIter from, InputIter until, bool bidir = false) {
        const auto n = std::distance(from, until);
        while (bpow_.size() < n) {
            bpow_.push_back((bpow_.back() * B) % M);
        }
        // Build forward hash
        {
            pref_hash_.resize(n + 1);
            pref_hash_[0] = 0;
            auto it = from;
            for (size_type i = 0; i < n; ++i) {
                pref_hash_[i + 1] =
                    (((pref_hash_[i] * B) % M) + static_cast<int_type>(*it)) % M;
                ++it;
            }
        }
        // Set and test flag, and build reverse hash
        bidir_ = bidir;
        if (bidir_) {
            suff_hash_.resize(n + 1);
            suff_hash_[n] = 0;
            auto it = prev(until);
            for (size_type i = n; i; --i) {
                suff_hash_[i - 1] =
                    (((suff_hash_[i] * B) % M) + static_cast<int_type>(*it)) % M;
                --it;
            }
        }
    }

    /**
     * @brief Returns the polynomial hash value of the subsegment S[i], S[i + 1], ...,
     * S[i + n - 1], which is the value S[i] * B^(n - 1) + S[i + 1] * B^(n - 2) +
     * ... + S[i + n - 1] * B^0, modulo M.
     * @param i Starting index/position of the subsegment
     * @param n Length of the subsegment
     */
    value_type get(size_type i = 0,
                   size_type n = std::numeric_limits<size_type>::max()) const {
        assert(i < pref_hash_.size());
        n = std::min(n, pref_hash_.size() - 1 - i);
        return (pref_hash_[i + n] - ((pref_hash_[i] * bpow_[n]) % M) + M) % M;
    }

    /**
     * @brief Returns the polynomial hash value of the subsegment S[i], S[i + 1], ...,
     * S[i + n - 1] in reverse order, which is the value S[i] * B^i + S[i + 1] *
     * B^(i + 1) + ... + S[i + n - 1] * B^(i + n - 1), modulo M.
     * @param i Starting index/position of the subsegment
     * @param n Length of the subsegment
     */
    value_type get_rev(size_type i = 0,
                       size_type n = std::numeric_limits<size_type>::max()) const {
        assert(bidir_);
        assert(i < suff_hash_.size());
        n = std::min(n, suff_hash_.size() - 1 - i);
        return (suff_hash_[i] - ((suff_hash_[i + n] * bpow_[n]) % M) + M) % M;
    }

    /**
     * @brief Erases hash values of all prefixes (and suffixes if hashed
     * bidirectionally) calling `clear()` on the internal vector(s). Resets
     * bidirectional flag.
     */
    void clear() {
        pref_hash_.clear();
        suff_hash_.clear();
        bidir_ = false;
    }

    /**
     * @brief Number of elements in the hashed key.
     */
    size_type size() const { return pref_hash_.size() ? pref_hash_.size() - 1 : 0; }

    /**
     * @brief Returns true if no hash values are stored.
     */
    bool empty() const { return pref_hash_.empty(); }

    /**
     * @brief Returns true if the stored hash value is bidirectional (i.e., both
     * `hash` and `hash_rev` can be called).
     */
    bool bidirectional() const { return bidir_; }
};

template <std::uint64_t Base, std::uint64_t Modulus>
std::vector<std::uint64_t> Polynomial_hasher<Base, Modulus>::bpow_ = {1ULL};

using Hasher0 = Polynomial_hasher<prime_bases[0], prime_moduli[0]>;
using Hasher1 = Polynomial_hasher<prime_bases[1], prime_moduli[1]>;
