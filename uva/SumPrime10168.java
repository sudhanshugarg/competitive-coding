import java.util.Scanner;
import java.util.HashMap;
import java.lang.Math;

//class SumPrime10168 {
class Main {
    static int MAXVAL = 10000001;
    static int x,y;
    static HashMap<Integer, Boolean> hashPrime;
    static int [] primeList;

    public static void main(String[] args){
        hashPrime = new HashMap<Integer, Boolean> ();
        primeList = new int[664579];

        primeList[0] = 2;
        hashPrime.put(Integer.valueOf(2),Boolean.TRUE);
        int next = 1;
        int s,i,j;
        boolean isPrime;
        for(i=3;i<MAXVAL;i+=2){
            isPrime = true;
            s = (int)Math.sqrt(i);
            for(j = 0; primeList[j] <= s; j++)
                if(i % primeList[j] == 0){
                    isPrime = false;
                    break;
                }
            if(isPrime){
                primeList[next++] = i;
                hashPrime.put(Integer.valueOf(i), Boolean.TRUE);
            }
        }
        //taking input.
        int n;
        Scanner input = new Scanner (System.in);
        while(input.hasNextInt()){
            n = input.nextInt();
            if(n < 8){
                System.out.println("Impossible.");
                continue;
            }
            //even
            else if(n%2 == 0){
                GoldBach(n-4);
                System.out.printf("2 2 %d %d\n",x,y);
            }
            //odd
            else{
                GoldBach(n-5);
                System.out.printf("2 3 %d %d\n",x,y);
            }
        }
    }

    static void GoldBach(int n){
        int nextPrime;
        for(int j=0;j<primeList.length && (primeList[j] <= n/2);j++){
            nextPrime = n-primeList[j];
            if(hashPrime.containsKey(nextPrime)){
                x = primeList[j];
                y = nextPrime;
                //System.out.printf("%d = %d+%d\n",n,primeList[j],nextPrime);
                break;
            }
        }
    }
}
