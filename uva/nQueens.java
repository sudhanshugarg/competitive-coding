import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;
import java.io.IOException;
import java.io.PrintStream;

public class nQueens{
    static int[] rowsUsed;
    static int[] colsUsed;
    static int n;
    static int MAXBOARD = 100;
    static int count;
    static PrintStream pr;

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        pr = new PrintStream(System.out);
        String thisLine;
        //assume n < MAXBOARD
        rowsUsed = new int [MAXBOARD];
        colsUsed = new int [MAXBOARD];
        while((thisLine = in.readLine()) != null){
            n = Integer.parseInt(thisLine);
            count = 1;
            for(int i=0;i<n;i++){
                rowsUsed[i] = colsUsed[i] = -1;
            }
            backtrack(0);
        }
    }

    static void backtrack(int row){
        //pr.printf("Currently checking in row %d\n",row);
        if(row == n){
            //print solution.
            pr.printf("Solution Number: %d\n", count);
            for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                    if(rowsUsed[i] != -1 && (rowsUsed[i] == j)){
                        pr.print('#');
                    }
                    else pr.print('.');
                }
                pr.println();
            }
            count++;
            return;
        }

        //construct candidates.
        //currently at row
        //for this row, try to place a queen at some col.
        boolean flag = true;
        for(int col=0;col<n;col++){
            flag = true;
            if(colsUsed[col] != -1){
                flag = false;
            }
            else{
                //go through rows 0 to row-1.
                for(int r = 0; r<row;r++){
                    //check if any of the rows interferes
                    //with this location [row][col].
                    if( ((col-row) == (rowsUsed[r]-r)) ||
                        ((col+row) == (rowsUsed[r]+r)) ){
                        flag = false;
                        break;
                    }
                }
            }
            if(!flag) continue;

            rowsUsed[row] = col;
            colsUsed[col] = row;
            //pr.printf("For row %d, set col %d\n", row, col);
            backtrack(row+1);
            rowsUsed[row] = -1;
            colsUsed[col] = -1;
        }
        return;
    }
}
