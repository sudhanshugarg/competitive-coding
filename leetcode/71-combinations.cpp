class Solution {
public:
    map<pair<int, int>, vector<vector<int> > > store;
    vector<vector<int>> combine(int n, int k) {
        // n c k = n-1 c k-1 + n-1 c k.
        vector<vector<int> > ret;
        if(k == 0 || n < k) return ret;
        //find in map
        pair<int,int> p(n,k);
        if(store.find(p) != store.end()) return store[p];
        
        if(k == 1){
            for(int i=1;i<=n;i++){
                vector<int> next{i};
                ret.push_back(next);
            }
            store[p] = ret;
            return ret;
        }
        
        if(n == k){
            //put in all the numbers from 1 to n into the list.
            vector<int> next;
            for(int i=1;i<=n;i++)
                next.push_back(i);
            ret.push_back(next);
            store[p] = ret;
            return ret;
        }
        
        //n > k
        vector<vector<int> > ret2;
        ret = combine(n-1, k-1);
        ret2 = combine(n-1, k);
        for(int i=0;i<ret.size();i++){
            ret[i].push_back(n);
        }
        for(int i=0;i<ret2.size();i++)
        ret.push_back(ret2[i]);
        
        store[p] = ret;
        return ret;
    }
};