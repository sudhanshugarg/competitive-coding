import java.util.Scanner;
import java.math.BigInteger;
import java.lang.Math;
import java.util.HashMap;

public class Main {
//public class Priest10254HashMap {
    public final static int MAXVAL = 10000;
    public static HashMap<Integer, BigInteger> moves;
    public static BigInteger arr1d[];
    public static BigInteger two;

    public static void main(String[] args){
        int n;
        Scanner input = new Scanner(System.in);
        
        //first argument is number of disks, second is
        //moves using 1 spare disk or 2 spare disks.
        arr1d = new BigInteger [MAXVAL+1];
        two = BigInteger.valueOf(2);

        arr1d[0] = BigInteger.ZERO;
        BigInteger previousPower = BigInteger.ONE;
        for(int i=1;i<MAXVAL+1;i++){
            previousPower = previousPower.multiply(two);
            arr1d[i] = previousPower.subtract(BigInteger.ONE);
            //arr2d[i][1] = BigInteger.ZERO;
        }

        //moves = new HashMap<Integer,BigInteger>();
        moves = new HashMap<Integer, BigInteger>(MAXVAL, 0.75f);
        moves.put(0,BigInteger.ZERO);
        moves.put(1,BigInteger.ONE);

        BigInteger ret;
        while(input.hasNextInt()){
            n = input.nextInt();
            ret = getValue(n);
            System.out.println(ret.toString());
        }
    }

    public static BigInteger getValue(int n){
        //System.out.printf("here to find value of n=%d\n",n);
        if(moves.containsKey(n))
            return moves.get(n);
        //arr2d[0][1] = BigInteger.ZERO;
        //arr2d[1][1] = BigInteger.ONE;
        BigInteger store,store2,minval;

        minval = two.add(arr1d[n-1]);
        //doubling
        int j;
        for(j=2;j<n;j*=2){
            //store = arr2d[j][1];
            //System.out.printf("trying to get value of %d for %d\n",j,n);
            store = getValue(j);
            //System.out.printf("got value of %d=" + store.toString() + " for %d\n",j,n);
            store = store.multiply(two);
            store = store.add(arr1d[n-j]);
            //if the value of this new j is greater than
            //the previous value, then we need to stop.
            if(store.compareTo(minval) >= 0){
                break;
            }
            //this check is to ensure you haven't
            //surreptitiously veered into enemy territory.
            //store2 is the immediately next value, and
            //if it is decreasing, then no worries, else you
            //break again.
            else{
                if((j+1) == n) break;
                //System.out.printf("followed by trying to get value of %d for %d\n",j+1,n);
                store2 = getValue(j+1);
                //System.out.printf("got value of %d=" + store2.toString() + " for %d\n",j+1,n);
                store2 = store2.multiply(two);
                store2 = store2.add(arr1d[n-j-1]);
                if(store2.compareTo(store) >= 0){
                    break;
                }
            }
            minval = store;
        }
        int low,high;
        //reached the end of the loop
        low = j/2;
        if(j >= n){
            high = n-1;
        }
        else{
            high = j;
        }
        //System.out.printf("for n = %d, low = %d, high = %d\n",n,low,high);

        //do binary search on low to high, both included.
        //lets start with regular search on that interval - iterative.
        minval = two.multiply(getValue(low));
        minval = minval.add(arr1d[n-low]);
            //System.out.printf("for n = %d, low = %d, minval = " + minval.toString() + "\n", n, low);
        for(int i=low+1; i<=high; i++){
            store = getValue(i);
            store = store.multiply(two);
            store = store.add(arr1d[n-i]);
            //System.out.printf("for n = %d, i = %d, store = " + store.toString() + "\n", n, i);
            if(store.compareTo(minval) >= 0){
                break;
            }
            minval = store;
        }
        moves.put(n,minval);
        return minval;
    }

    public static BigInteger doubling(int v){
        return BigInteger.ONE;
    }
}
