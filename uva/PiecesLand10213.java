import java.util.Scanner;
import java.math.BigDecimal;

public class PiecesLand10213 {
//changing class name for uva
//submission
//public class Main {
    public static void main(String[] args){
        //tried this, but doesn't work with void arguments.
        //public static void main(void){

        Scanner input = new Scanner(System.in);
        //take in number of test cases.
        int cases = input.nextInt();

        int n;
        BigDecimal out;
        BigDecimal term2;
        BigDecimal two, three, four, twentyFour;
        two = new BigDecimal(2);
        three = new BigDecimal(3);
        twentyFour = new BigDecimal(24);
        four = new BigDecimal(4);

        for(int i=0;i<cases;i++){
            n = input.nextInt();
            BigDecimal b = new BigDecimal(n);
            out = b;
            out = out.multiply(b.subtract(BigDecimal.ONE));
            out = out.multiply(b.subtract(two));
            out = out.multiply(b.subtract(three));
            out = out.divide(twentyFour);
            out = out.add(four);

            term2 = b.subtract(three);
            term2 = term2.multiply(b.add(two));
            term2 = term2.divide(two);

            out = out.add(term2);
            //out = b*(b-1)*(b-2)*(b-3)/24 + (b-3)*(b+2)/2 + 4;
            System.out.println(out.toString());
        }
    }
}
