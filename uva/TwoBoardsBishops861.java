import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.io.IOException;
import java.util.StringTokenizer;

//public class TwoBoardsBishops861 {
public class Main {
    static int n,k;
    static int n2;
    static int count;
    static boolean[] downLeft;
    static boolean[] downRight;
    static PrintStream pr;
    static boolean isWhiteBoard;

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        pr = new PrintStream(System.out);
        String thisLine;
        downRight = new boolean[25];
        downLeft = new boolean[25];
        int [] whiteBoard = new int[40];
        int [] blackBoard = new int[40];

        while((thisLine = in.readLine()) != null){
            StringTokenizer st = new StringTokenizer(thisLine);
            n = Integer.parseInt(st.nextToken());
            k = Integer.parseInt(st.nextToken());
            if(n == 0 && k == 0) break;
            if(n == 1){
                pr.println(1);
                continue;
            }

            if(k >= 2*n-1){
                pr.println(0);
                continue;
            }

            for(int i=0;i<40;i++){
                blackBoard[i] = 0;
                whiteBoard[i] = 0;
            }

            n2 = n*n;

            //divide into two boards, black and white.
            //backtrack from 1 to n^2.
            //count from 0 to
            for(int i=0;i<=k;i++){
                count = 0;
                for(int j=0;j<25;j++){
                    downRight[j] = false;
                    downLeft[j] = false;
                }
                isWhiteBoard = true;
                backtrack(0,0,i);
                whiteBoard[i] = count;

                count = 0;
                for(int j=0;j<25;j++){
                    downRight[j] = false;
                    downLeft[j] = false;
                }
                isWhiteBoard = false;
                backtrack(0,1,i);
                blackBoard[i] = count;
            }
            int total = 0;
            for(int i=0;i<=k;i++)
                total += whiteBoard[i]*blackBoard[k-i];
                
            pr.println(total);
        }
    }

    static void backtrack(int row, int col, int bishops){

        if(bishops == 0){
            count += 1;
            return;
        }
        else if(bishops == 1){
            //count the number of valid spaces *after* pos, that
            //are left.
            int spaces = 0;
            int r,c = col;
            for(r=row;r<n;r++){
                if(r!=row){
                    if(isWhiteBoard){
                        if(r%2 == 0) c = 0;
                        else c = 1;
                    }
                    else {
                        //is blackboard
                        if(r%2 == 0) c = 1;
                        else c = 0;
                    }
                }
                for(;c<n;c+=2){
                    if(!downLeft[r+c] && !downRight[r-c+n])
                    spaces++;
                }
            }
            count += spaces;
            return;
        }

        //bishops >= 2.
        int c = col,r;

        //for(int i=pos;i<n2-bishops+1;i++)
        for(r=row; r<n;r++){
            if(r!=row){
                if(isWhiteBoard){
                    if(r%2 == 0) c = 0;
                    else c = 1;
                }
                else {
                    //is blackboard
                    if(r%2 == 0) c = 1;
                    else c = 0;
                }
            }
            for(;c<n;c+=2){
                if(!downLeft[r+c] && !downRight[r-c+n]){
                    //just set.
                    downLeft[r+c] = true;
                    downRight[r-c+n] = true;

                    //recurse
                    backtrack(r, c, bishops-1);

                    //unset candidate.
                    downLeft[r+c] = false;
                    downRight[r-c+n] = false;
                }
            }
        }
        return;
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
