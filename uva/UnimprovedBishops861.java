import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.io.IOException;
import java.util.StringTokenizer;

public class Bishops861 {
//public class Main {
    static int n,k;
    static int n2;
    static long count;
    static int[][] board;
    static boolean[] downLeft;
    static boolean[] downRight;
    static PrintStream pr;

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        pr = new PrintStream(System.out);
        String thisLine;
        board = new int[8][8];
        downRight = new boolean[25];
        downLeft = new boolean[25];

        while((thisLine = in.readLine()) != null){
            StringTokenizer st = new StringTokenizer(thisLine);
            n = Integer.parseInt(st.nextToken());
            k = Integer.parseInt(st.nextToken());
            if(n == 0 && k == 0) break;

            for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                board[i][j] = 0;

            for(int i=0;i<25;i++){
                downRight[i] = false;
                downLeft[i] = false;
            }

            count = 0;
            n2 = n*n;

            //backtrack from 1 to n^2.
            backtrack(0,k);
            pr.println(count);
        }
    }

    static void backtrack(int pos, int bishops){
        if(bishops == 0){
            count += 1;
            return;
        }
        else if(bishops == 1){
            //count the number of valid spaces *after* pos, that
            //are left.
            int spaces = 0;
            for(int i=pos;i<n2;i++){
                if(validSpot(i)) {
                    //pr.printf("%d ",i);
                    spaces++;
                }
                /*
                else{
                    pr.printf("%d is not a valid spot, row=%d,col=%d\n",i, (int)(i/n),i%n);
                }
                */
            }
    //        pr.println();
            count += (long)spaces;

            /*
            pr.print("Count = ");
            pr.println(spaces);
             * Printing the result.
            for(int a=0;a<n;a++){
                for(int b=0;b<n;b++){
                    pr.print(board[a][b]);
                    pr.print('.');
                }
                pr.println();
            }
            pr.println();
             */
            return;
        }
        //bishops >= 2.
        int row,col;
        for(int i=pos;i<n2-bishops+1;i++){
            row = (int)(i/n);
            col = i%n;
            //if(!diagonalsUsed[row+col+n] && !diagonalsUsed[row-col+n]){
            if(!downLeft[row+col] && !downRight[row-col+n]){
                board[row][col] = k-bishops+1;
            //if(validSpot(i)){
                //set candidate.
                //current bishop = k-bishops+1;
                /*
                for(int j=col+1;(j<n) && ((row+j-col) < n);j++){
                    if(board[row+j-col][j] == 0)
                        board[row+j-col][j] = -(k-bishops+1);
                }
                for(int j=col-1;(j>=0) && ((col+row-j) < n);j--){
                    if(board[col+row-j][j] == 0)
                        board[col+row-j][j] = -(k-bishops+1);
                }
                //just set.
                pr.print("Just set the candidates for pos=");
                pr.println(i);
                for(int a=0;a<n;a++){
                    for(int b=0;b<n;b++){
                        pr.print(board[a][b]);
                        pr.print('.');
                    }
                    pr.println();
                }
                pr.println();
                */
        //        pr.printf("Set %d, %d\n", row+col+n, row-col+n);
                downLeft[row+col] = true;
                downRight[row-col+n] = true;

                //recurse
                backtrack(i+1, bishops-1);

                //unset candidate.
                /*
                for(int j=col+1;(j<n) && ((row+j-col) < n);j++){
                    if(board[row+j-col][j] == -(k-bishops+1))
                        board[row+j-col][j] = 0;
                }
                for(int j=col-1;(j>=0) && ((col+row-j) < n);j--){
                    if(board[col+row-j][j] == -(k-bishops+1))
                        board[col+row-j][j] = 0;
                }
                */
          //      board[row][col] = 0;
         //       pr.printf("Unset %d, %d\n", row+col+n, row-col+n);
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
     //   pr.print("Testing for ");
     //   pr.println(pos);
        if(downLeft[r+c] || downRight[r-c+n]){
     //       pr.print(downLeft[r+c]);
     //       pr.println(downRight[r-c+n]);
            return false;
        }
        //if(board[(int)(pos/n)][pos%n] != 0)
        //    return false;
        return true;
    }
}
