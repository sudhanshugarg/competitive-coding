import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.io.IOException;
import java.util.StringTokenizer;

//public class Bishops861 {
public class Main {
    static int n,k;
    static int n2;
    static long count;
    static boolean[] downLeft;
    static boolean[] downRight;
    static PrintStream pr;

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        pr = new PrintStream(System.out);
        String thisLine;
        downRight = new boolean[25];
        downLeft = new boolean[25];

        while((thisLine = in.readLine()) != null){
            StringTokenizer st = new StringTokenizer(thisLine);
            n = Integer.parseInt(st.nextToken());
            k = Integer.parseInt(st.nextToken());
            if(n == 0 && k == 0) break;
            if(k >= 2*n-1){
                pr.println(0);
                continue;
            }

            for(int i=0;i<25;i++){
                downRight[i] = false;
                downLeft[i] = false;
            }

            count = 0;
            n2 = n*n;

            //backtrack from 1 to n^2.
            backtrack(0,k,n2);
            pr.println(count);
        }
    }

    static void backtrack(int pos, int bishops, int valid){
        int row,col;

        if(bishops == 0){
            count += 1;
            return;
        }
        else if(bishops == 1){
            //count the number of valid spaces *after* pos, that
            //are left.
            int spaces = 0;
            for(int i=pos;i<n2;i++){
                row = (int)(i/n);
                col = i%n;
                if(!downLeft[row+col] && !downRight[row-col+n]){
                    spaces++;
                }
            }
            count += (long)spaces;
            return;
        }
        //see if number of valid positions left are less than
        //the number of bishops.
        if(valid < bishops) return;

        //number of valid positions left.

        //bishops >= 2.
        int c,r;
        int invalidate;

        for(int i=pos;i<n2-bishops+1;i++){
            row = (int)(i/n);
            col = i%n;
            if(!downLeft[row+col] && !downRight[row-col+n]){
                //just set.
                downLeft[row+col] = true;
                downRight[row-col+n] = true;

                //figure out how many of the spots became invalid.
                //proceed downLeft.
                invalidate = 0;
                for(c = col-1, r=row+1; (c>=0) && (r<n); c--, r++){
                    if(!downRight[r-c+n])
                        invalidate++;
                }
                for(c = col+1, r=row+1; (c<n) && (r<n); c++, r++){
                    if(!downLeft[r+c])
                        invalidate++;
                }

                //recurse
                backtrack(i+1, bishops-1, valid-invalidate-1);

                //unset candidate.
                downLeft[row+col] = false;
                downRight[row-col+n] = false;
            }
        }
        return;

        //move from pos
    }
    static boolean validSpot(int pos){
        int r = (int)(pos/n);
        int c = pos%n;
        if(downLeft[r+c] || downRight[r-c+n]){
            return false;
        }
        return true;
    }
}
