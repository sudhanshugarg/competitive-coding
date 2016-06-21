import java.util.Scanner;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;
import java.io.IOException;

import java.io.PrintStream;
import java.io.OutputStreamWriter;

public class Main {
//public class M10090arbles {
    public static long x, y;
    public static void main(String[] args) throws IOException{
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        boolean swap = false;
        long n;
        long c1, n1, c2, n2;
        String thisLine;
        PrintStream pr = new PrintStream(System.out);
        //while(input.hasNextLong()){
        while((thisLine = in.readLine()) != null){
            n = Long.parseLong(thisLine);
            if (n == 0) break;

            thisLine = in.readLine();
            StringTokenizer longToken1 = new StringTokenizer(thisLine);
            c1 = Long.parseLong(longToken1.nextToken());
            n1 = Long.parseLong(longToken1.nextToken());
            thisLine = in.readLine();
            StringTokenizer longToken2 = new StringTokenizer(thisLine);
            c2 = Long.parseLong(longToken2.nextToken());
            n2 = Long.parseLong(longToken2.nextToken());


            //find the gcd of n1 and n2.
            long r, s;
            long g;
            if(n1 >= n2){
                g = gcd(n1,n2);
                r = x;
                s = y;
            }
            else{
                g = gcd(n2,n1);
                r = y;
                s = x;
            }
            //System.out.printf("gcd of %d and %d is %d\n",n1,n2,g);
            //System.out.printf("extended of %d and %d is %d and %d\n",n1,n2,r,s);
            if(n % g != 0){
                pr.println("failed");
                continue;
            }
            long k1, k2;
            k1 = n1/g;
            k2 = n2/g;

            long bx, by;
            bx = (n/g)*r;
            by = (n/g)*s;
            //System.out.printf("n1 = %d, n2 = %d, bx = %d and by = %d\n", n1, n2, bx, by);

            long maxT, minT;
            //now to find limits on t.
            maxT = (long)Math.floor(bx/k2);
            minT = (long)Math.ceil(-by/k1);
            //System.out.printf("maxT = %d and minT = %d\n",maxT, minT);
            //System.out.printf("c1 = %d and c2 = %d\n", c1, c2);

            long cost1 = c1*bx + c2*by + maxT*(c2*k1-c1*k2);
            long cost2 = c1*bx + c2*by + minT*(c2*k1-c1*k2);
            //System.out.printf("cost1 = %d, cost2 = %d\n",cost1, cost2);
            
            if(cost1 <= 0){
                //use cost2, i.e. minT
                bx -= minT*k2;
                by += minT*k1;
            }
            else if(cost2 <= 0){
                //use cost1, i.e. maxT
                bx -= maxT*k2;
                by += maxT*k1;
            }
            else{
                //use min. of both.
                if(cost1 < cost2){
                    bx -= maxT*k2;
                    by += maxT*k1;
                }
                else{
                    bx -= minT*k2;
                    by += minT*k1;
                }
            }

            pr.print(bx);
            pr.print(' ');
            pr.print(by);
            pr.println();

        }
        pr.flush();
        pr.close();
    }

    static long gcd(long a, long b){
        if(b == 0){
            x = 1;
            y = 0;
            return a;
        }

        long g = gcd (b, a%b);
        long tmp = x;
        x = y;
        y = tmp - (long)Math.floor(a/b)*y;
        return g;
    }
}
