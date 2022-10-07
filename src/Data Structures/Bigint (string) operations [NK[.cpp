string add(const string& a, const string& b) {
    string sum;
    int i = a.length() - 1, j = b.length() - 1, carry = 0;
    while (i >= 0 || j >= 0) {
        int temp = carry;
        if (i >= 0) {
            temp += (int)(a[i--] - '0');
        }
        if (j >= 0) {
            temp += (int)(b[j--] - '0');
        }
        carry = temp / 10;
        sum += (char)((temp % 10) + '0');
    }
    if (carry > 0) {
        sum += (char)(carry + '0');
    }
    for (int k = sum.length() - 1; k > 0 && sum[k] == '0'; k--) {
        sum.pop_back();
    }
    reverse(sum.begin(), sum.end());
    return sum;
}

string multiply(const string& a, const string& b) {
    if (a.length() == 0 || b.length() == 0) {
        return "0";
    }
    string prod = "0";
    int shift = 0, carry = 0;
    for (int j = b.length() - 1; j >= 0; j--) {
        string prod_temp;
        for (int i = 0; i < shift; i++) {
            prod_temp += '0';
        }
        shift++;
        carry = 0;
        for (int i = a.length() - 1; i >= 0; i--) {
            int temp = ((int)(a[i] - '0') * (int)(b[j] - '0')) + carry;
            carry = temp / 10;
            prod_temp += (char)((temp % 10) + '0');
        }
        if (carry > 0) {
            prod_temp += (char)(carry + '0');
        }
        reverse(prod_temp.begin(), prod_temp.end());
        prod = add(prod, prod_temp);
    }
    return prod;
}

struct division_t {
    string quot;
    int64_t rem;
};

division_t divide(const string& num, int64_t divisor) {
    string quot;
    int idx = 0;
    int64_t temp = num[idx++] - '0';
    while (temp < divisor && idx < num.length()) {
        temp = (temp * 10) + (int)(num[idx++] - '0');
    }
    quot += (char)((temp / divisor) + '0');
    while (idx < num.length()) {
        temp = ((temp % divisor) * 10) + (int)(num[idx++] - '0');
        quot += (char)((temp / divisor) + '0');
    }
    int cnt = 0;
    while (cnt < quot.length() - 1 && quot[cnt] == '0') {
        cnt++;
    }
    quot = quot.substr(cnt);
    return (division_t){quot, temp % divisor};
}
