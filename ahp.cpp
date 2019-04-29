#include<iostream>
using namespace std;
struct comb
{
    int h;
    float p;
};

struct cp
{
    struct comb f[3][2];
    float checkpoint[3][3];

};
void combination(int arr[],struct cp point[4],float h[3][4],int no_of_checkpoints);// function to compare the houses pairwise
void set_priority(int m,int n,int x,int y,float h[3][4],struct cp point[4] ,int checkpoint_no);// compares the priorities pairwise and assign them in a table
void col_row(float col[4][3],float row[3][4],struct cp point[4]);
int final_priority(float row[3][4],int priority[4]);

int main()

{
int no_of_checkpoints=4;
struct cp point[4];//array which stores the pairwise comparison tables of all the checkpoints
int priority[no_of_checkpoints];// array to store the priorities input by the user
cout<<"1=school"<<endl<<"2=office"<<endl<<"3=hospital"<<endl<<"4=market"<<endl;
cout<<"enter priority of checkpoints"<<endl;
for(int i=0;i<no_of_checkpoints;i++)
{
    cout<<"priority of "<<i<<"th checkpoint=";
    cin>>priority[i];
}
    int arr[3]={0,1,2};
//struct comb f[3][2];

    float h[3][4]={{100,300,200,400},
                {200,500,100,300},
                {200,100,400,300}};

    combination(arr,point,h,no_of_checkpoints);

    for(int z=0;z<4;z++)
    {cout<<endl<<"first table of"<<z+1<<"th priority"<<endl;
        for(int i=0;i<3;i++)
    {
        for(int j=0;j<2;j++)
        {
            cout<<point[z].f[i][j].h<<" "<<point[z].f[i][j].p<<"  ";
        }
        cout<<endl;
    }   }

for(int z=0;z<no_of_checkpoints;z++)
{
    for(int i=0,k=-1;i<3;i++)
{k++;
    for(int j=0;j<3;j++)
    {
        if(i==j)
        {
            point[z].checkpoint[i][j]=1;
        }
        if(i<j)
        {
            point[z].checkpoint[i][j]=(point[z].f[k][0].p/point[z].f[j-1][1].p);
            k++;
        }
        if(i>j)
        {
            point[z].checkpoint[i][j]=(1/point[z].checkpoint[j][i]);
            k--;
        }
    }
}
}

cout<<endl<<"second table "<<endl;
for(int z=0;z<4;z++)
{ cout<<endl<<z<<"th priority"<<endl;
    for(int i=0,k=-1;i<3;i++)
{
    for(int j=0;j<3;j++)
    {
        cout<<point[z].checkpoint[i][j]<<" ";
    }
    cout<<endl;
}}

float col[4][3],row[3][4];
col_row (col , row,point );
//final_priority(row,priority);
cout<<endl<<"preferred house is"<<final_priority(row,priority);

}

void set_priority(int m,int n,int x,int y,float h[3][4],struct cp point[4],int checkpoint_no)
{
    if(h[m][checkpoint_no]==h[n][checkpoint_no])
    {
        point[checkpoint_no].f[x][y-1].p=1;
        point[checkpoint_no].f[x][y].p=1;
    }
    if(h[m][checkpoint_no]>h[n][checkpoint_no])
    {
        point[checkpoint_no].f[x][y-1].p=1;
        point[checkpoint_no].f[x][y].p=(h[m][checkpoint_no]/h[n][checkpoint_no]);
    }
    else if(h[m][checkpoint_no]<h[n][checkpoint_no])
    {
        point[checkpoint_no].f[x][y].p=1;
        point[checkpoint_no].f[x][y-1].p=(h[n][checkpoint_no]/h[m][checkpoint_no]);
    }
}

void combination(int arr[],struct cp point[4],float h[3][4],int no_of_checkpoints)
{int x=0,y;
for(int z=0;z<no_of_checkpoints;z++)
        {x=0;
            for(int i = 0; i<2; i++)
            {for(int j = i+1; j<3; j++)
                {   y=0;
                    point[z].f[x][y].h=arr[i];
                    y++;
                    point[z].f[x][y].h=arr[j];
                    for(int k=0;k< no_of_checkpoints;k++ )
                    {set_priority(arr[i],arr[j],x,y,h,point,k);}
                    x++;
                    }
                        }
                            }
}

void col_row(float col[4][3],float row[3][4],struct cp point[4])//function to calculate sum of columns and weight criteria(i.e. (all values/col sum) and then avg of the rows
{

for(int z=0;z<4;z++)
{for(int i=0;i<4;i++)
{
    col[z][i]=0;
    row[i][z]=0;
}
}
for(int z=0;z<4;z++)
{for(int i=0;i<3;i++)
{
    for(int j=0;j<3;j++)
    {
        col[z][i]=col[z][i]+point[z].checkpoint[j][i];
    }

}}
cout<<endl<<"col sum"<<endl;
for(int z=0;z<4;z++)
{cout<<endl<<"col sum of"<<z<<"th priority"<<endl;
    for(int i=0;i<3;i++)
{
    cout<<col[z][i]<<endl;
}}

for(int z=0;z<4;z++)
{for(int i=0;i<3;i++)
{
    for(int j=0;j<3;j++)
    {
        point[z].checkpoint[i][j]=(point[z].checkpoint[i][j]/col[z][j]);
        row[i][z]=row[i][z]+point[z].checkpoint[i][j];
    }
    row[i][z]=row[i][z]/3;
}}
for(int z=0;z<4;z++)
{cout<<endl<<"third table of "<<z<<"th priority"<<endl;
    for(int i=0;i<3;i++)
{
    for(int j=0;j<3;j++)
    {
        cout<<point[z].checkpoint[i][j]<<" ";
    }
    cout<<endl;
}}
cout<<endl<<"row sum average"<<endl;
for(int z=0;z<4;z++)
{cout<<endl<<"row sum of"<<z<<"th priority"<<endl;
    for(int i=0;i<3;i++)
{
    cout<<row[i][z]<<" ";
}
cout<<endl;
}
}

int final_priority(float row[3][4],int priority[4])
{ float arr[3][4];
float sum[3]={0,0,0};
for(int z=0;z<4;z++)
{
    for(int i=0;i<3;i++)
    {
        arr[i][z]=priority[z]*row[i][z];
       //cout<<arr[i][z]<<" ";
    }

    //cout<<endl;
}

//cout<<endl<<"sum"<<endl;
float max_val=0,val=0;
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<4;j++)
        {
            sum[i]=sum[i]+arr[i][j];

        }
        //cout<<sum[i]<<" ";
        if(sum[i]>max_val)
            {max_val=sum[i];
                val=i;}
    }
    //cout<<max_val;
  return (val);

}
