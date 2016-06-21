import java.util.Scanner;
import java.util.ArrayList;
import java.lang.Math;

public class Main {
//public class Factovisors10139 {
    public static ArrayList<Integer> primes;
    public static void main(String[] args){
        Scanner input = new Scanner(System.in);
        int n,m;

        //generate primes from 2 till sqrt(2^31-1);
        int sLargest = (int)Math.sqrt(2147483647);
        primes = new ArrayList<Integer>();

        primes.add(Integer.valueOf(2));
        primes.add(Integer.valueOf(3));
        primes.add(Integer.valueOf(5));
        primes.add(Integer.valueOf(7));

        int i,j;
        for(i=11;i<=sLargest;i+=2){
            for(j=0;j<primes.size();j++)
                if(i % primes.get(j).intValue() == 0) break;
            if(j == primes.size())
                primes.add(Integer.valueOf(i));
        }

        int[] primeFactors = new int[primes.size()];

        while(input.hasNextInt()){
            n = input.nextInt();
            m = input.nextInt();

            if(m == 0){
                System.out.printf("%d does not divide %d!\n",m,n);
                continue;
            }
            else if(n >= m){
                System.out.printf("%d divides %d!\n",m,n);
                continue;
            }
            else if (n == 0){
                if(m == 1)
                    System.out.printf("%d divides %d!\n",m,n);
                else
                    System.out.printf("%d does not divide %d!\n",m,n);
                continue;
            }

            //n < m
            //find the prime factors of m.
            int s = (int)Math.sqrt(m);
            int tmp = m;
            for(i=0;i<primes.size();i++)
                primeFactors[i] = 0;

            for(i=0;primes.get(i).intValue()<=s;i++){
                while(tmp % primes.get(i).intValue() == 0){
                    primeFactors[i]++;
                    tmp /= primes.get(i).intValue();
                }
                if(tmp == 1) break;
            }
            //the final prime factor of m is tmp.

            //found the prime factors of m. now..?
            //now check if n!
            //i.e.
            s = i; //only need to check till this index.
            int index = 0;
            int count = 0;
            int next = 1;
            //boolean isPrime = true;
            for(i=0;i<=s;i++){
                if(primeFactors[i] == 0) continue;
                //isPrime = false;
                //else check the number of these in n!.
                count = 0;
                next = 1;
                index = 1;
                while(next > 0){
                    next = (int)(n/Math.pow(primes.get(i).intValue(),index));
                    count += next;
                    index++;
                }
                if(count < primeFactors[i]){
                    break;
                }
            }
            //if(!isPrime && (i > s)){
            if(i > s && tmp <= n){
                //one final check for tmp divisors.
                System.out.printf("%d divides %d!\n",m,n);
            }
            else
                System.out.printf("%d does not divide %d!\n",m,n);
        }
    }
}
