class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int> > ret;
        //either nums[i] is in the set, or it isn't.
        vector<int> sub;
        mySubsets(nums, sub, 0, ret);
        return ret;
    }
    void mySubsets(vector<int> &nums, vector<int> &sub, int start, vector<vector<int> >&ret){
        if(start == nums.size()){
            ret.push_back(sub);
            return;
        }
        mySubsets(nums, sub, start+1, ret);
        sub.push_back(nums[start]);
        mySubsets(nums, sub, start+1, ret);
        sub.pop_back();
    }
};