#include<iostream>

using namespace std;
int arr[9]={0};
int check_plus()
{
    for(int i=0,j=0;i<3;i++,j=j+3)
    {
        if((arr[0+i]+arr[3+i]+arr[6+i]==3) || arr[0+j]+arr[1+j]+arr[2+j]==3)
        {
            return 1;
        }
        else if(arr[0+i]+arr[3+i]+arr[6+i]==0 || arr[0+j]+arr[1+j]+arr[2+j]==0)
        {
            return 0;
        }
    }
    return -1;
}
bool check_x()
{
    if((arr[0]==arr[4] && arr[4]==arr[8]) || (arr[2]==arr[4]&& arr[4]==arr[6]))
        return true;
    else
        return false;
}
void userinput(int i)
{
    int x;
    cin>>x;
    switch(x)
    {
        case 1:arr[0]=i;break;
        case 2:arr[1]=i;break;
        case 3:arr[2]=i;break;
        case 4:arr[3]=i;break;
        case 5:arr[4]=i;break;
        case 6:arr[5]=i;break;
        case 7:arr[6]=i;break;
        case 8:arr[7]=i;break;
        case 9:arr[8]=i;break;
    }
}
void showmap()
{
    for(int i=0; i<9;i++)
    {
        (i==2 || i==5)?cout<<arr[i]<<endl:cout<<arr[i]<<" ";
    }
}
void checkwin()
{
    for(int i=0; i<9;i++)
    {
        if(check_x())
        {
            cout<<"player "<<arr[4]<<" win with x";
            return;
        }
        int ch=check_plus();
        if(ch==-1)
            cout<<"DRAW";
        else
            cout<<"player "<<ch<<" wins";
        return ;
    }
}
int main()
{
    int x,ch;
    showmap();
    for(int i=1;i<10;i++)
    {
        userinput(i%2);

    }
    showmap();
    checkwin();
    return 0;
}
