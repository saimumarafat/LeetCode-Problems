
class Solution {
public:
    unordered_map<int, unordered_map<int, int>> kFactorCounts = {
        {0, {}},
        {1, {}},
        {2, {{2, 1}}},
        {3, {{3, 1}}},
        {4, {{2, 2}}},
        {5, {{5, 1}}},
        {6, {{2, 1}, {3, 1}}},
        {7, {{7, 1}}},
        {8, {{2, 3}}},
        {9, {{3, 2}}}
    };

    string smallestNumber(string num, long long t) {
        auto [primeCount, ok] = getPrimeCount(t);
        if (!ok) return "-1";

        auto factorCount = getFactorCount(primeCount);
        if (sumValues(factorCount) > (int)num.size())
            return construct(factorCount);

        auto primeCountPrefix = getPrimeCountFromString(num);

        int firstZeroIndex = num.find('0');
        if (firstZeroIndex == string::npos) {
            firstZeroIndex = num.size();
            if (isSubset(primeCount, primeCountPrefix))
                return num;
        }

        for (int i = (int)num.size() - 1; i >= 0; i--) {
            int d = num[i] - '0';
            primeCountPrefix = subtract(primeCountPrefix, kFactorCounts[d]);

            int spaceAfterThisDigit = (int)num.size() - 1 - i;

            if (i > firstZeroIndex)
                continue;

            for (int biggerDigit = d + 1; biggerDigit <= 9; biggerDigit++) {
                auto need = subtract(
                    subtract(primeCount, primeCountPrefix),
                    kFactorCounts[biggerDigit]);

                auto factorsAfterReplacement = getFactorCount(need);

                if (sumValues(factorsAfterReplacement) <= spaceAfterThisDigit) {
                    int fillOnes =
                        spaceAfterThisDigit - sumValues(factorsAfterReplacement);

                    return num.substr(0, i) +
                           char('0' + biggerDigit) +
                           string(fillOnes, '1') +
                           construct(factorsAfterReplacement);
                }
            }
        }

        auto factorsAfterExtension = getFactorCount(primeCount);
        return string((int)num.size() + 1 - sumValues(factorsAfterExtension), '1') +
               construct(factorsAfterExtension);
    }

private:
    pair<unordered_map<int, int>, bool> getPrimeCount(long long t) {
        unordered_map<int, int> cnt = {
            {2, 0}, {3, 0}, {5, 0}, {7, 0}
        };

        for (int p : {2, 3, 5, 7}) {
            while (t % p == 0) {
                t /= p;
                cnt[p]++;
            }
        }

        return {cnt, t == 1};
    }

    unordered_map<int, int> getPrimeCountFromString(const string &num) {
        unordered_map<int, int> cnt = {
            {2, 0}, {3, 0}, {5, 0}, {7, 0}
        };

        for (char c : num) {
            int d = c - '0';
            for (auto &[p, f] : kFactorCounts[d])
                cnt[p] += f;
        }

        return cnt;
    }

    unordered_map<int, int> getFactorCount(unordered_map<int, int> cnt) {
        unordered_map<int, int> res;

        int count8 = cnt[2] / 3;
        int remaining2 = cnt[2] % 3;

        int count9 = cnt[3] / 2;
        int count3 = cnt[3] % 2;

        int count4 = remaining2 / 2;
        int count2 = remaining2 % 2;

        int count6 = 0;

        if (count2 == 1 && count3 == 1) {
            count2 = 0;
            count3 = 0;
            count6 = 1;
        }

        if (count3 == 1 && count4 == 1) {
            count2 = 1;
            count6 = 1;
            count3 = 0;
            count4 = 0;
        }

        res[2] = count2;
        res[3] = count3;
        res[4] = count4;
        res[5] = cnt[5];
        res[6] = count6;
        res[7] = cnt[7];
        res[8] = count8;
        res[9] = count9;

        return res;
    }

    string construct(const unordered_map<int, int> &factors) {
        string res;

        for (int d = 2; d <= 9; d++) {
            auto it = factors.find(d);
            if (it != factors.end())
                res.append(it->second, char('0' + d));
        }

        return res;
    }

    bool isSubset(const unordered_map<int, int> &a,
                  const unordered_map<int, int> &b) {
        for (auto &[k, v] : a) {
            auto it = b.find(k);
            if (it == b.end() || it->second < v)
                return false;
        }
        return true;
    }

    unordered_map<int, int> subtract(const unordered_map<int, int> &a,
                                     const unordered_map<int, int> &b) {
        unordered_map<int, int> res = a;

        for (auto &[k, v] : b)
            res[k] = max(0, res[k] - v);

        return res;
    }

    int sumValues(const unordered_map<int, int> &cnt) {
        int sum = 0;
        for (auto &[k, v] : cnt)
            sum += v;
        return sum;
    }
};