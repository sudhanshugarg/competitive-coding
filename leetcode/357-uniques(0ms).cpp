class Solution {
public:
    int countNumbersWithUniqueDigits(int n) {
        if(n<0 || n >= 11) return 0;
        int count[11];
        memset(count, 0, sizeof(count));
        count[0] = 1;
        int fact[11];
        memset(fact, 0, sizeof(fact));
        fact[0] = 1;
        for(int i=1;i<=10;i++){
            fact[i] = fact[i-1]*i;
        }

        return countUnique(n,count,fact);
    }
    
    int countUnique(int n, int count[], int fact[]) {
        if(count[n] != 0) return count[n];

        //the only cases are 1 to 10.
        //e.g, for n = 5, the numbers have to be <= 99999
        //all the numbers in n=4,3,2,1 are counted.
        //thus f[n] = f[0]+f[1]+...+f[n-1], and then some.
        //in the case of n = 5, the numbers start from 10000-99999.
        //so the answer is, choose 5 digits
        
        //if the first digit is a 0, remove those from the count.
        //i.e. 10 choose 5 - 9 choose 5.
        count[n] = countUnique(n-1, count, fact) + (fact[9]*9)/(fact[10-n]);
        return count[n];
    }
};