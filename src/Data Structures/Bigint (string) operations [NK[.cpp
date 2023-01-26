namespace bigint {
    constexpr int base = 10;

    int digit_value(char c) {
        if (c >= '0' && c <= '9') return (int)(c - '0');
        if (c >= 'A' && c <= 'Z') return (int)(c - 'A' + 10);
        if (c >= 'a' && c <= 'z') return (int)(c - 'a' + 36);
        return -1;
    }

    char digit_char(int n) {
        if (n >= 0 && n <= 9) return (char)(n + '0');
        if (n >= 10 && n <= 35) return (char)(n - 10 + 'A');
        if (n >= 36 && n <= 61) return (char)(n - 36 + 'a');
        return ' ';
    }

    string add(const string& a, const string& b) {
        string sum;
        int i = a.length() - 1, j = b.length() - 1, carry = 0;
        while (i >= 0 || j >= 0) {
            int temp = carry +
                       (i < 0 ? 0 : digit_value(a[i--])) +
                       (j < 0 ? 0 : digit_value(b[j--]));
            carry = temp / base;
            sum += digit_char(temp % base);
        }
        if (carry > 0) sum += digit_char(carry);
        while (sum.length() > 1 && sum[sum.length() - 1] == '0') {
            sum.pop_back();
        }
        reverse(sum.begin(), sum.end());
        return sum;
    }

    string multiply(const string& a, const string& b) {
        string prod = "0";
        int shift = 0, carry = 0;
        for (int j = b.length() - 1; j >= 0; j--) {
            string prod_temp(shift++, '0');
            carry = 0;
            for (int i = a.length() - 1; i >= 0; i--) {
                int temp = carry + digit_value(a[i]) * digit_value(b[j]);
                carry = temp / base;
                prod_temp += digit_char(temp % base);
            }
            if (carry > 0) prod_temp += digit_char(carry);
            reverse(prod_temp.begin(), prod_temp.end());
            prod = add(prod, prod_temp);
        }
        while (prod.length() > 1 && prod[prod.length() - 1] == '0') {
            prod.pop_back();
        }
        return prod;
    }

    struct div_result {
        string quot;
        int64_t rem;
    };

    div_result divide(const string& num, int64_t divisor) {
        div_result result;
        int64_t remainder = 0;
        for (int i = 0; i < num.length(); i++) {
            remainder = (remainder * base) + digit_value(num[i]);
            result.quot += digit_char(remainder / divisor);
            remainder %= divisor;
        }
        int clz = 0;
        while (clz < result.quot.length() - 1 && result.quot[clz] == '0') {
            clz++;
        }
        result.quot = result.quot.substr(clz);
        result.rem = remainder;
        return result;
    }
} // namespace bigint