import java.util.Scanner;
import java.util.ArrayList;

public class Main{
//public class Self10049{
    public static ArrayList<Integer> sum;
    public static boolean flag = false;
    public static void main(String[] args){
        //Integer abc = new Integer(1);
        sum = new ArrayList<Integer>();
        sum.add(Integer.valueOf(1));
        sum.add(Integer.valueOf(3));
        long largest = 5;
        int next = 4;
        int MAXVAL = 2000000000;
        //int MAXVAL = 15;
        int index;

        for(next = 4;largest <= MAXVAL; next++){
            sum.add(Integer.valueOf((int)largest));
            //find the next value in the list.
            index = find(next);
            largest += (long)index;
        }

        /*
        System.out.println('#');
        for(int i=0;i<sum.size();i++)
            System.out.println(sum.get(i).toString());
        System.out.println('#');
        */

        Scanner input = new Scanner(System.in);
        int n;
        //flag = true;
        while(input.hasNextInt()){
            n = input.nextInt();
            if(n == 0) break;
 //           if(n == 1) System.out.println(1);
 //           else
                System.out.println(find(n));
        }
    }

    public static int find(int n){
        //this function finds the index of the number n via binary search.
        int low = 0;
        int high = sum.size()-1;
        int mid;
        mid = (low+high)/2;

        while(low <= high){
            if(flag)
            System.out.printf("finding %d in low=%d, high=%d, mid=%d\n",n,low,high,mid);
            //search in the left half.
            if(n < sum.get(mid).intValue()){
                high = mid-1;
            }
            else if(n > sum.get(mid).intValue()){
                low = mid+1;
            }
            else return mid+1;

            mid = (low+high)/2;
        }
        return low+1;
    }
}
