/**
 * @brief Segment tree with lazy updates.
 * @tparam ValueTp The value type. Must imply a monoid
 * (i.e., have a closed, associative binary operation and a corresponding identity
 * element).
 * @tparam FnCombine A function to combine two values into one. Implements the closed,
 * associative binary operation of the ValueTp monoid.
 * @tparam FnGetDefaultValue A function that returns the default value for any node.
 * The returning value is the identity element of the ValueTp monoid.
 * @tparam ArgTp The type of lazy-update arguments. Must imply a monoid
 * (i.e., have a closed, associative binary operation and a corresponding identity
 * element).
 * @tparam FnCompose A function to compose two lazy-update arguments into one.
 * Implements the closed, associative binary operation of the ArgTp monoid.
 * @tparam FnGetDefaultArg A function that returns the default lazy-update argument
 * for any node. The returning value is the identity element of the ArgTp monoid.
 * @tparam FnApply A function to apply an update on a node's value. Takes the
 * following parameters: the node's value, an update argument, and two indexes
 * indicating the range of the segment covered by the node.
 */
template <class ValueTp,
          ValueTp (*FnCombine)(ValueTp, ValueTp),
          ValueTp (*FnGetDefaultValue)(),
          class ArgTp,
          ArgTp (*FnCompose)(ArgTp, ArgTp),
          ArgTp (*FnGetDefaultArg)(),
          ValueTp (*FnApply)(ValueTp, ArgTp, std::size_t, std::size_t)>
class Lazy_segment_tree {
public:
    using SizeType = std::size_t;
    using ValueType = ValueTp;
    using ArgType = ArgTp;

    static constexpr auto combine = FnCombine;
    static constexpr auto default_value = FnGetDefaultValue;
    static constexpr auto compose = FnCompose;
    static constexpr auto default_arg = FnGetDefaultArg;
    static constexpr auto apply = FnApply;

    /**
     * @brief Default constructor.
     */
    Lazy_segment_tree() {}

    /**
     * @brief Constructs and builds a tree over a default-valued array.
     * @param n Size of the array
     */
    Lazy_segment_tree(SizeType n) { build(n); }

    /**
     * @brief Constructs and builds a tree over a range of values.
     * @tparam InputIterator An input iterator type
     * @param from Iterator pointing to the beginning of the range
     * @param until Iterator pointing to the end (one place past the last) of the range
     */
    template <class InputIterator>
    Lazy_segment_tree(InputIterator from, InputIterator until) { build(from, until); }

    /**
     * @brief Builds the tree over a default-valued array.
     * @param n Size of the array
     */
    void build(SizeType n) {
        log2_n_ = 0;
        while (((SizeType)1 << log2_n_) < n) ++log2_n_;
        n_ = 1 << log2_n_;
        ranges_.resize(n_ << 1);
        for (SizeType i = n_; i < (n_ << 1); ++i) {
            ranges_[i][0] = i - n_, ranges_[i][1] = ranges_[i][0] + 1;
        }
        for (SizeType i = n_ - 1; i; --i) {
            ranges_[i][0] = std::min(ranges_[i << 1][0], ranges_[i << 1 | 1][0]);
            ranges_[i][1] = std::max(ranges_[i << 1][1], ranges_[i << 1 | 1][1]);
        }
        tree_.assign(n_ << 1, default_value());
        args_.assign(n_, default_arg());
    }

    /**
     * @brief Builds the tree over a range of values.
     * @tparam InputIterator An input iterator type
     * @param from Iterator pointing to the beginning of the range
     * @param until Iterator pointing to the end (one past the last element) of the range
     */
    template <class InputIterator>
    void build(InputIterator from, InputIterator until) {
        const std::vector<ValueType> v(from, until);
        build(v.size());
        for (SizeType i = 0; i < v.size(); ++i) {
            tree_[i + n_] = v[i];
        }
        for (SizeType i = n_ - 1; i; --i) {
            tree_[i] = combine(tree_[i << 1], tree_[i << 1 | 1]);
        }
    }

    /**
     * @brief Performs a point-update (update at a single position) on the segment tree.
     * @param p Index of the element to update
     * @param arg Argument of the update
     */
    void update(SizeType p, ArgType arg) {
        assert(0 <= p && p < n_);
        apply_update(p + n_, arg);
        build_update(p + n_);
    }

    /**
     * @brief Performs a lazy range-update on the segment tree.
     * @param l Index pointing to the begining of the range
     * @param r Index pointing to the end (one past the last element) of the range
     * @param arg Argument of the update
     */
    void update(SizeType l, SizeType r, ArgType arg) {
        assert(0 <= l && l <= r && r <= n_);
        l += n_, r += n_;
        const auto l0 = l, r0 = r;
        propagate_update(l0), propagate_update(r0 - 1);
        while (l < r) {
            if (l & 1) {
                apply_update(l++, arg);
            }
            if (r & 1) {
                apply_update(--r, arg);
            }
            l >>= 1, r >>= 1;
        }
        build_update(l0), build_update(r0 - 1);
    }

    /**
     * @brief Returns the value of a segment.
     * @param l Index pointing to the begining of the range
     * @param r Index pointing to the end (one past the last element) of the range
     * @return ValueType
     */
    ValueType operator()(SizeType l, SizeType r) {
        assert(0 <= l && l <= r && r <= n_);
        ValueType result = default_value();
        l += n_, r += n_;
        propagate_update(l), propagate_update(r - 1);
        while (l < r) {
            if (l & 1) {
                result = combine(result, tree_[l++]);
            }
            if (r & 1) {
                result = combine(result, tree_[--r]);
            }
            l >>= 1, r >>= 1;
        }
        return result;
    }

    /**
     * @brief Returns the segment tree.
     * @return std::vector<ValueType>
     */
    std::vector<ValueType> tree() const { return tree_; }

    /**
     * @brief Returns the lazy-update arguments.
     * @return std::vector<ArgType>
     */
    std::vector<ArgType> args() const { return args_; }

    /**
     * @brief Returns the ranges covered by tree nodes. Each range is an
     * array of two indexes, the first one being the beginning, the second
     * one being the end (one past the last index).
     * @return std::vector<std::array<SizeType, 2>>
     */
    std::vector<std::array<SizeType, 2>> ranges() const { return ranges_; }

private:
    SizeType n_ = 0;
    int log2_n_ = 0;
    std::vector<ValueTp> tree_;
    std::vector<ArgTp> args_;
    std::vector<std::array<SizeType, 2>> ranges_;

    void apply_update(SizeType i, const ArgTp& arg) {
        tree_[i] = apply(tree_[i], arg, ranges_[i][0], ranges_[i][1]);
        if (i < n_) args_[i] = compose(args_[i], arg);
    }

    void propagate_update(SizeType i) {
        assert(n_ <= i && i < (n_ << 1));
        for (int h = log2_n_; h; --h) {
            auto j = (i >> h);
            apply_update(j << 1, args_[j]);
            apply_update(j << 1 | 1, args_[j]);
            args_[j] = default_arg();
        }
    }

    void build_update(SizeType i) {
        assert(n_ <= i && i < (n_ << 1));
        while (i >>= 1) {
            tree_[i] = apply(combine(tree_[i << 1], tree_[i << 1 | 1]),
                             args_[i],
                             ranges_[i][0],
                             ranges_[i][1]);
        }
    }
};

using Val_t = int64_t;
constexpr Val_t combine(Val_t x, Val_t y) { return x + y; }
constexpr Val_t defval() { return 0; }

using Arg_t = int64_t;
constexpr Arg_t compose(Arg_t p, Arg_t q) { return p + q; }
constexpr Arg_t defarg() { return 0; }

constexpr Val_t apply(Val_t val, Arg_t arg, size_t l, size_t r) {
    return val + (arg * (r - l));
}

using Segtree =
    Lazy_segment_tree<Val_t, combine, defval, Arg_t, compose, defarg, apply>;
