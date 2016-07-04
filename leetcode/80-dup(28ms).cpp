class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int len = nums.size();
        
        bool twice = false;
        int next = 0;
        int lastShifted = 0;
        
        for(int i=1;i<len;i++){
            if(nums[i] == nums[i-1]){
                //seen it twice.

                if(!twice){
                    twice = true;
                }
                else{
                    //first move these elements to their earlier place.
                    //find first next element.
                    lastShifted = nums[i];
                    if(!next)
                        next = i;
                    else{
                        nums[next] = nums[i];
                        nums[next+1] = nums[i];
                        next+=2;
                    }
                    while(i+1 < len && nums[i] == nums[i+1]) i++;
                    twice = false;
                    //now, put these two values, at the last known swap location.
                }
            }//end if
            else {
                //check if a number needs to be shifted.
                if(!next) {
                    twice = false;
                    continue;
                }
                
                //1 or 2 numbers need to be shifted.
                if(twice) {
                    //no need to check.
                    nums[next] = nums[next+1] = nums[i-1];
                    next+=2;
                    lastShifted = nums[i-1];
                }
                else if(lastShifted != nums[i-1]){
                    nums[next] = nums[i-1];
                    next++;
                    lastShifted = nums[i-1];
                }
                twice = false;
            }//end else
        }
        
        if(!next) return len;
        if(twice) {
            //no need to check.
            nums[next] = nums[next+1] = nums[len-1];
            next+=2;
            lastShifted = nums[len-1];
        }
        else if(lastShifted != nums[len-1]){
            nums[next] = nums[len-1];
            next++;
            lastShifted = nums[len-1];
        }
        return next;
    }
};