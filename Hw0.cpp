#include<iostream>
#include<vector>
using namespace std;




int main()
{
  int n,a,b,c;
  cin>>n;
  cin>>a>>b>>c;
  int**k=new int*[n];
  int num=0;
    for(int i=0;i<n;i++)
    {
        k[i]=new int[n];
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            cin>>num;
            if(i==j){
                k[i][j]=0;
            }
            else if(num==0){
                k[i][j]=a;

            }
            else if(num==1){
                k[i][j]=b;
            }
            else if(num==2){
                k[i][j]=c;
            }
            
        }
    }
    for(int i=0;i<n;i++)
    {
        int all=0;
        for(int j=0;j<n;j++)
        {
            all+=k[i][j];
            
        }
        i!=n-1?cout<<all<<" ":cout<<all;
      
    }
   for(int i=0;i<n;i++)
   {
       delete[] k[i];
   }
   delete[] k;
    return 0;

}