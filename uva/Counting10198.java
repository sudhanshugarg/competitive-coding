import java.util.Scanner;
import java.lang.Math;
import java.math.BigInteger;

public class Main {
//public class Counting10198 {
    public static int MAXVAL = 1000;
    public static void main(String[] args){
        Scanner input = new Scanner(System.in);
        int n;
        BigInteger [][][] arr3d = new BigInteger[MAXVAL+1][MAXVAL+1][4];
        //i is the number trying to reach.
        //j is the number of digits.
        //k is the value of the last digit.
        for(int i=0;i<MAXVAL+1;i++)
            for(int j=0;j<MAXVAL+1;j++)
                for(int k=1;k<4;k++){
                    arr3d[i][j][k] = BigInteger.ZERO;
                }

        BigInteger two = BigInteger.ONE;
        two = two.multiply(BigInteger.valueOf(2));

        for(int i=1;i<MAXVAL+1;i++)
            arr3d[i][i][1] = two.pow(i);

        arr3d[2][1][2] = BigInteger.valueOf(1);
        arr3d[3][1][3] = BigInteger.valueOf(1);
        arr3d[3][2][1] = BigInteger.valueOf(2);
        arr3d[3][2][2] = BigInteger.valueOf(2);

        //starting with n=4 till 1000;
        BigInteger store;
        for(int i=4;i<MAXVAL+1;i++)
            for(int j=1;j<i;j++){
                //when last digit is a 1/4.
                //arr3d[i][j][1] = 2*(arr3d[i-1][j-1][1] + arr3d[i-1][j-1][2] + arr3d[i-1][j-1][3]);
                store = arr3d[i-1][j-1][1];
                store = store.add(arr3d[i-1][j-1][2]);
                store = store.add(arr3d[i-1][j-1][3]);
                arr3d[i][j][1] = store.multiply(two);

                for(int k=2;k<4;k++){
                    //arr3d[i][j][k] = (arr3d[i-k][j-1][1] + arr3d[i-k][j-1][2] + arr3d[i-k][j-1][3]);
                    store = arr3d[i-k][j-1][1];
                    store = store.add(arr3d[i-k][j-1][2]);
                    arr3d[i][j][k] = store.add(arr3d[i-k][j-1][3]);
                }
            }

        int out;
        while(input.hasNextInt()){
            n = input.nextInt();
            store = BigInteger.ZERO;
            for(int i=1;i<n+1;i++){
                store = store.add(arr3d[n][i][1]);
                store = store.add(arr3d[n][i][2]);
                store = store.add(arr3d[n][i][3]);
                //out += arr3d[n][i][1]+arr3d[n][i][2] + arr3d[n][i][3];
            }
            System.out.println(store.toString());
        }
    }
}
