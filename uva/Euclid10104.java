import java.util.Scanner;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;
import java.io.IOException;

import java.io.PrintStream;
import java.io.OutputStreamWriter;

//public class Main {
public class Euclid10104 {
    static long x,y;
    public static void main(String[] args) throws IOException{
        //Scanner input = new Scanner(System.in);
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        long tmp,a,b;
        boolean swap = false;
        long g;
        String thisLine;
        PrintStream pr = new PrintStream(System.out);
        //while(input.hasNextLong()){
        while((thisLine = in.readLine()) != null){
            StringTokenizer longToken = new StringTokenizer(thisLine);
            a = Long.parseLong(longToken.nextToken());
            b = Long.parseLong(longToken.nextToken());

            swap = false;
            //a = input.nextLong();
            //b = input.nextLong();
            //larger value in a;
            if(a<b){
                swap = true;
                tmp = a;
                a = b;
                b = tmp;
            }
            x = -1;
            y = -1;

            g = gcd(a, b);
            //TODO need to swap back before next step.
            if(swap){
                tmp = a;
                a = b;
                b = tmp;

                tmp = x;
                x = y;
                y = tmp;
            }

            //System.out.printf("intermediates for: %d, %d= %d %d %d\n",a,b,x,y,g);
            //print out nonzero values for x and y.

            //need to get the min abs(x)+abs(y)
            long c = -(long)(b/g);
            long d = (long)(a/g);
            //long nextx = x, nexty = y;
            while(x == 0 || y == 0){
            //if(x > 0 && x <= y){
                //System.out.println("In x > 0 term");
                //long min = x + y;
                //while(x <= y){
                  //  if((Math.abs(nextx) + Math.abs(nexty)) < min){
                    //    min = Math.abs(nextx) + Math.abs(nexty);
                      //  x = nextx; y = nexty;
                    //}
                    //else break;
                    x += c;
                    y += d;
                //}
            }
            /*
            else{
                //System.out.println("In other term");
                while(x > y){
                    //System.out.println("In while x > y term");
                    y += d;
                    x += c;
                }
            }
            //System.out.printf("%d %d %d\n",x,y,g);
            */
            pr.print(x);
            pr.print(' ');
            pr.print(y);
            pr.print(' ');
            pr.print(g);
            pr.println();
        }
        pr.flush();
        pr.close();
    }
    static long gcd(long a, long b){
        //assume that a >= b
        //base case
        if(b == 0){
            x = 1;
            y = 0;
            return a;
        }

        long g;
        g = gcd(b, a%b);
        long tmp = x;
        x = y;
        y = tmp - ((long)Math.floor(a/b))*y;
        return g;
    }
}
