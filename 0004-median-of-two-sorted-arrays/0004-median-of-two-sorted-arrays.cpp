class Solution {
public:
    double findMedianSortedArrays(vector<int>& a, vector<int>& b) {
        vector<int> v(a.begin(), a.end());
        v.insert(v.end(), b.begin(), b.end());
        sort(v.begin(), v.end());

        int n = v.size();
        return n % 2 ? v[n/2] : (v[n/2-1] + v[n/2]) / 2.0;
    }
};