import java.util.Scanner;
import java.math.BigInteger;
import java.lang.Math;

//public class Main {
public class Priest10254 {
    public final static int MAXVAL = 10000;
    public static void main(String[] args){
        int n;
        Scanner input = new Scanner(System.in);
        
        //first argument is number of disks, second is
        //moves using 1 spare disk or 2 spare disks.
        BigInteger arr2d[][] = new BigInteger [MAXVAL+1][2];
        BigInteger previousPower = BigInteger.ONE;
        BigInteger two = BigInteger.valueOf(2);
        for(int i=1;i<MAXVAL+1;i++){
            previousPower = previousPower.multiply(two);
            arr2d[i][0] = previousPower.subtract(BigInteger.ONE);
            //arr2d[i][1] = BigInteger.ZERO;
        }

        arr2d[0][0] = BigInteger.ZERO;
        arr2d[0][1] = BigInteger.ZERO;
        arr2d[1][1] = BigInteger.ONE;
        BigInteger store;

        for(int i=2;i<MAXVAL+1;i++){
            arr2d[i][1] = two.add(arr2d[i-1][0]);
            for(int j=2;j<i;j++){
                store = arr2d[j][1];
                store = store.multiply(BigInteger.valueOf(2));
                store = store.add(arr2d[i-j][0]);
                arr2d[i][1] = arr2d[i][1].min(store);
                System.out.printf("for n=%d,j=%d, store=%d\n",i,j,store);
                //arr2d[i][1] = Math.min(arr2d[i][1], 2*arr2d[j][1]+arr2d[i-j][0]);
            }
            System.out.println();
        }

        while(input.hasNextInt()){
            n = input.nextInt();
            System.out.println(arr2d[n][1].toString());
        }
    }
}
