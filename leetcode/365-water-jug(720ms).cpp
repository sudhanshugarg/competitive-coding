class Solution {
public:
    bool canMeasureWater(int x, int y, int z) {
        if(z == 0) return true;
        if(z > x+y) return false;
        
        //z <= x+y
        if(x == y){
            if(z == x || z == 2*x) return true;
            return false;
        }
        
        //assertained that x != y.
        //put the smaller value in x;
        if(x>y){
            int tmp = x;
            x = y;
            y = tmp;
        }
        
        //the case where x = 0.
        if (x == 0){
            return y == z;
        }
        
        //now, x ne 0, and x ne y, and z ne 0.
        //create a map, that contains all possible remainders of x.
        map<int, bool> remainders;
        int next = 0;
        while(remainders.find(next) == remainders.end()){
            remainders[next] = true;
            if((z % x) == next)
                return true;
            next = x-(y-next)%x;
        }
        return false;
    }
};