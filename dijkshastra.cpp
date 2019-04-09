#include<iostream>
#include<bits/stdc++.h>
using namespace std;
void print(int key[], int n)
{
    for(int i=0;i<n;++i)
       {  
        cout<<key[i]<<" ";
       }
       cout<<"\n";

}
void dijkshastra( int** graph,int n , int u)
{  int* p=new int[n];
  int* key=new int[n];
priority_queue<int, vector<int> , greater<int> > pq;
for(int i=0;i<n;++i)
  {
      if(graph[u][i])
          { p[i]=u;
           key[i]=graph[u][i];
          }
          else
            {
                p[i]=-1;
                key[i]=INT_MAX;

            }


  }
  key[u]=0;
for(int i=0;i<n;++i)
  {
      pq.push(key[i]);
  }
while(!pq.empty())
{   
      int t=pq.top();
      pq.pop();
    for(int i=0;i<n;++i)          
         {

             if(graph[t][i])
                {
                     if((graph[t][i]+key[i])<key[i])
                       {
                           key[i]=graph[t][i]+key[i];
                           p[i]=t;

                       }

                }
                

          }
  
    


}
print(key,n);
}


int main()
{
  int n=4, u ;
  int** graph=new int*[n];
    for (int i=0;i<n;++i)
    { 
        for(int j=0;j<n;++j)
             cin>>graph[i][j];

    }
    cin>>u;
    dijkshastra(graph,n,u);
    
        return 0;
}