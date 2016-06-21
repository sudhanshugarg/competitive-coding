import java.util.Scanner;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;
import java.io.IOException;

import java.io.PrintStream;
import java.io.OutputStreamWriter;

public class Main {
//public class Marbles10090 {
    public static void main(String[] args) throws IOException{
        //Scanner input = new Scanner(System.in);
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        boolean swap = false;
        long n;
        long c1, n1, c2, n2;
        long x=-1,y=-1;
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

            double d1 = (double)c1/(double)n1;
            double d2 = (double)c2/(double)n2;

            long minval = 0;
            long costx1=-1, costx2=-1, costy1=-1, costy2=-1;
            costy1 = minCost2ndBag(n1,n2,n);
            int which = 0;
            if(costy1 != -1){
                which = 1;
                costx1 = (n - n2*costy1)/n1;
                minval = costx1*c1+costy1*c2;
            }
            costy2 = minCost2ndBag(n2,n1,n);
            if(costy2 != -1){
                costx2 = (n - n1*costy2)/n2;
                if(which == 0 || (costx2*c2+costy2*c1 < minval)){
                    minval = costx2*c2+costy2*c1;
                    which = 2;
                }
            }
            
            if(which == 0)
                pr.println("failed");
            else if(which == 1){
                pr.print(costx1);
                pr.print(' ');
                pr.print(costy1);
                pr.println();
            }
            else if(which == 2){
                pr.print(costy2);
                pr.print(' ');
                pr.print(costx2);
                pr.println();
            }
            /*
            //swap = false;
            //better container in a;
            if(d1 > d2){
                swap = true;
                y = minCost2ndBag(n2,n1,n);
            }
            else{
                y = minCost2ndBag(n1,n2,n);
            }
            //System.out.printf("y = %d\n",y);

            if(y != -1){
                if(swap){
                    x = (n - n1*y)/n2;
                    pr.print(y);
                    pr.print(' ');
                    pr.print(x);
                    pr.println();
                }
                else{
                    x = (n - n2*y)/n1;
                    pr.print(x);
                    pr.print(' ');
                    pr.print(y);
                    pr.println();
                }
            }
            else
                pr.println("failed");
            */

        }
        pr.flush();
        pr.close();
    }
    static long minCost2ndBag(long a, long b, long d){
        if(b % a == 0){
            if(d % a != 0)
                return -1;
            return 0;
        }
        if((d%a) % (b%a) != 0)
            return -1;
        return (long)((d%a)/(b%a));
    }
}
