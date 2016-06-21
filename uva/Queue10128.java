import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;
import java.io.PrintStream;
import java.util.HashMap;
import java.io.IOException;

//public class Queue10128 {
public class Main {
    public static long factorial[];
    public static long arr[][];
    public static PrintStream pr;
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        pr = new PrintStream(System.out);
        int T;
        String thisLine;
        thisLine = in.readLine();
        T = Integer.parseInt(thisLine);
        int N,L,R;

        factorial = new long[14];
        factorial[0] = factorial[1] = 1;
        for(int i=2;i<=13;i++){
            factorial[i] = i*factorial[i-1];
        }

        arr = new long [14][14];
        for(int i=0;i<14;i++)
            for(int j=0;j<14;j++)
                arr[i][j] = -1;

        while(T>0){
            T--;
            thisLine = in.readLine();
            StringTokenizer sToken = new StringTokenizer(thisLine);
            N = Integer.parseInt(sToken.nextToken());
            L = Integer.parseInt(sToken.nextToken());
            R = Integer.parseInt(sToken.nextToken());

            //put the tallest person in position i, and then
            //calculate how many can see to the left and to
            //the right.

            long count = 0;
            for(int i=1;i<=N;i++){
                count += numBlocked(i-1,L-1) * 
                    numBlocked(N-i,R-1) * 
                    choose(N-1,i-1);
            }
            pr.println(count);
        }
    }

    static long numBlocked(int n, int l){
        //the ordering of these statements is
        //important.
        if(n < 0) return 0;
        if(n < l) return 0;
        if(n == l) return 1;

        if(l <= 0) return 0;
        if(l == 1) return factorial[n-1];
        //pr.printf("In numBlocked, n = %d, l=%d\n",n,l);

        if(arr[n][l] != -1){
            return arr[n][l];
        }

        arr[n][l] = 0;
        //put the tallest person in the ith position.
        for(int i=1;i<=n;i++)
            arr[n][l] += numBlocked(i-1,l-1)*choose(n-1,i-1)*factorial[n-i];

        return arr[n][l];

        //the case where there is atleast 1 person, and we need
        //l to the left of him.
        
    }

    static long choose(int n, int k){
        return (factorial[n]/factorial[k])/factorial[n-k];
    }
}
