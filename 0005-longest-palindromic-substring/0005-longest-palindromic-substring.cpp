class Solution {
public:
    string longestPalindrome(string s) {
        int l=0,r=0,n=s.size();
        for(int i=0;i<n;i++)
            for(int a=i,b=i; a>=0&&b<n&&s[a]==s[b]; a--,b++)
                if(b-a>r-l) l=a,r=b;
        for(int i=0;i<n;i++)
            for(int a=i,b=i+1; a>=0&&b<n&&s[a]==s[b]; a--,b++)
                if(b-a>r-l) l=a,r=b;
        return s.substr(l,r-l+1);
    }
};