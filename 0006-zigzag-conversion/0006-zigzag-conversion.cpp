class Solution {
public:
    string convert(string s, int r) {
        if(r==1||r>=s.size()) return s;
        vector<string> v(r);
        int i=0,d=1;

        for(char c:s){
            v[i]+=c;
            if(i==0) d=1;
            else if(i==r-1) d=-1;
            i+=d;
        }

        string ans;
        for(auto &x:v) ans+=x;
        return ans;
    }
};