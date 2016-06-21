#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define one ((long long)1)
int n,m;
long long st[40],latter[40];
bool dfs(long long state,int cur,int begin,int maxlength)
{
  int i;
  if(state==(one<<(n))-1)
      return true;
  if(cur==maxlength)
    return false;


  for(i=begin;i<=n;i++)
    {
      if((state|latter[i])!=(one<<(n))-1)
    return false;
      if((state|st[i])==state)continue;
      if(dfs(state|st[i],cur+1,begin+1,maxlength))
    return true;
    }

}

int main()
{

  int i,a,b;
  long long state=0;
   while(scanf("%d%d",&n,&m)&&n)
    {
      memset(st,0,sizeof(st));
      memset(latter,0,sizeof(latter));
      state=0;
      for(i=1;i<=n;i++)
    {
      st[i]=(one<<(i-1));
    }
      for(i=1;i<=m;i++)
    {
      scanf("%d%d",&a,&b);
      st[a]=st[a]|(one<<(b-1));
      st[b]=st[b]|(one<<(a-1));
    }

      latter[n]=st[n];
      for(i=n-1;i>=1;i--)
    {
      latter[i]=st[i]|latter[i+1];
    }

      for(i=1;i<=n;i++)
    {
      if(dfs(state,0,1,i))
        {
          printf("%d\n",i);
          break;
        }
    }
    }
 
 
  return 0;
}
