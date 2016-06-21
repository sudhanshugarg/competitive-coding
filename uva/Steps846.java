import java.util.Scanner;
import java.util.ArrayList;
import java.lang.Math;

//public class Steps846{
public class Main{
    public static void main(String[] args){
        Scanner input = new Scanner (System.in);
        int cases = input.nextInt();
        int x,y,diff,sq;
        for(int i=0;i<cases;i++){
            x = input.nextInt();
            y = input.nextInt();
            if(x == y){
                System.out.println(0);
                continue;
            }
            diff = y-x;
            sq = (int)Math.sqrt(diff);

            if(sq*sq == diff){
                System.out.println(2*sq-1);
            }
            else{
                int left = diff-sq*sq;
                int more = (int)(left/sq);
                if(left%sq != 0) more++;
                System.out.println(2*sq-1+more);
            }

            //System.out.printf("x=%d,y=%d,y-x=%d,sq=%d\n",x,y,diff,sq);
        }
    }
}
