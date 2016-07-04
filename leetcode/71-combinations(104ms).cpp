class Solution {
public:
    map<pair<int, int>, vector<vector<int> > > store;
    vector<vector<int>> combine(int n, int k) {
        // n c k = n-1 c k-1 + n-1 c k.
        vector<vector<int> > ret;
        vector<int> tmp;
        myComb(1,n,k,tmp,ret);
        return ret;
    }
    
    void myComb(int start, int n, int k, vector<int> &sol, vector<vector<int> > &ret){
        if(k == 0) {
            ret.push_back(sol);
            return;
        }
        
        for(int i=start;i<=n-k+1; i++){
            sol.push_back(i);
            //cout << "pushed " << i << endl;
            myComb(i+1, n, k-1, sol, ret);
            sol.pop_back();
        }
    }
};