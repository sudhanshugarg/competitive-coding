typedef class IntervalTree{

    public:
    IntervalTree *left;
    IntervalTree *right;
    int low;
    int high;
    int mid;
    int sum;
    
    void update(int &pos, int diff){
        //check if have to update left or right.
        if(pos <= mid && left != NULL) { //update left subtree.
            left->update(pos, diff);
        }
        else if(right != NULL) { //update right subtree.
            right->update(pos, diff);
        }
        sum += diff;
    }
    
    int getSum(int l, int r){
        if((l == low) && (r == high)) return sum;
        
        if(r <= mid){
            //entirely in left subtree.
            if(left != NULL){
                return left->getSum(l,r);
            }
            else return sum;
        }
        else if (l > mid){
            //entirely in right subtree;
            if(right != NULL){
                return right->getSum(l,r);
            }
            else return sum;
        }
        else{
            //l to mid in left subtree,
            //mid+1 to r in right subtree.
            int total = 0;
            if(left != NULL) total += left->getSum(l, mid);
            if(right != NULL) total += right->getSum(mid+1,r);
            return total;
        }
        return 0;
    }
    
} IntervalTree;

IntervalTree* createTree(vector<int> &nums, int l, int h){

    if(l > h) return NULL;
    IntervalTree* t = new IntervalTree();
    t->low = l;
    t->high = h;
    t->sum = 0;
        
    if (l == h){
        t->sum = nums[l];
        t->left = t->right = NULL;
        return t;
    }

    t->mid = (t->low+t->high)/2;
    t->left = createTree(nums, t->low, t->mid);
    t->right = createTree(nums, t->mid+1, t->high);
    if(t->left != NULL) t->sum += t->left->sum;
    if(t->right != NULL) t->sum += t->right->sum;
        
    return t;
}

class NumArray {
public:
    IntervalTree *root;
    vector<int> *arr;
    NumArray(vector<int> &nums) {
        root = createTree(nums, 0, nums.size()-1);
        arr = &nums;
    }

    void update(int i, int val) {
        //update i in the interval tree.
        root->update(i, val-(*arr)[i]);
        (*arr)[i] = val;
    }

    int sumRange(int i, int j) {
        return root->getSum(i,j);
    }
    
};

// Your NumArray object will be instantiated and called as such:
// NumArray numArray(nums);
// numArray.sumRange(0, 1);
// numArray.update(1, 10);
// numArray.sumRange(1, 2);