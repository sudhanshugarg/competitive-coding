class Solution {
public:
    bool isPerfectSquare(int num) {
        if(num < 2) return true;
        
        //keep doubling
        long long next;
        for(next = 2; next*next <= num; next*=2);
        
        //now we know next*next > num and (next/2)*(next/2) <= num.
        //perform binary search from next-1 to next.
        long long low = next/2;
        long long high = next;
        long long mid;
        while(low <= high){
            mid = (low+high)/2;
            if(mid * mid < num){
                low = mid+1;
            }
            else if (mid * mid > num){
                high = mid-1;
            }
            else{
                return true;
            }
        }
        return false;
        
    }
};