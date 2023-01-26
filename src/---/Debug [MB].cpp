template <typename T, typename C = typename T::value_type>
typename enable_if<!is_same<T, string>::value, ostream&>::type operator<<(ostream& out, const T& c) {
    for (auto it = c.begin(); it != c.end(); it++)
        out << (it == c.begin() ? "{" : ",") << *it;
    return out << (c.empty() ? "{" : "") << "}";
}

template <typename T, typename S>
ostream& operator<<(ostream& out, const pair<T, S>& p) {
    return out << "{" << p.first << ", " << p.second << "}";
}

#define dbg(...) _dbg_print(#__VA_ARGS__, __VA_ARGS__);

template <typename Arg1>
void _dbg_print(const char* name, Arg1&& arg1) {
    if (name[0] == ' ') name++;
    cout << "[" << name << ": " << arg1 << "]\n";
}

template <typename Arg1, typename... Args>
void _dbg_print(const char* names, Arg1&& arg1, Args&&... args) {
    const char* comma = strchr(names + 1, ',');
    cout << "[";
    cout.write(names, comma - names) << ": " << arg1 << "] ";
    _dbg_print(comma + 1, args...);
}