#include<iostream>
using namespace std;
int main ()
{
        int x , y;
        int testCases;
        int min_steps = 0;
        cin>>testCases;
       
        for(int i=0; i<testCases ; i++)
        {
                cin>>x>>y;
                int difference = y - x;
                min_steps = 0;
                if(difference != 0)
                {
                         int sumOfSteps = 0;
                      int z = 2; //divided by 2, it represents the size if the next step
                        while(difference > sumOfSteps)
                        {
                                sumOfSteps += (z / 2); //next step
                                min_steps++;
                                z++;
                        }
                }
               
                cout<<min_steps<<endl;
        }
        return 0;
}
