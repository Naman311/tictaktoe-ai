#include<iostream>

using namespace std;
int arr[3][3]={0};

int check_plus()
{
    for(int i=0;i<3;i++)
    {
        if(arr[i][0]==arr[i][1] && arr[i][1]==arr[i][2])
        {
            return arr[i][0];
        }
        else if(arr[0][i]==arr[1][i] &&arr[1][i]==arr[2][i])
        {
            return arr[0][i];
        }
    }
    return -1;
}
bool check_x(int ch)
{
    if((arr[0][0]==ch && arr[2][2] ==ch) || (arr[0][2]==ch && arr[2][0]==ch))
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
        case 1:arr[0][0]=i;break;
        case 2:arr[0][1]=i;break;
        case 3:arr[0][2]=i;break;
        case 4:arr[1][0]=i;break;
        case 5:arr[1][1]=i;break;
        case 6:arr[1][2]=i;break;
        case 7:arr[2][0]=i;break;
        case 8:arr[2][1]=i;break;
        case 9:arr[2][2]=i;break;
    }
}
void showmap()
{
    for(int i=0; i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            cout<<arr[i][j]<<" ";
        }
        cout<<endl;
    }
}
void checkwin()
{
    for(int i=0; i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            int ch=arr[1][1];
            if(check_x(ch))
            {
                cout<<"player "<<ch<<" win with x";
                return;
            }
            ch=check_plus();
            if(ch==-1)
                cout<<"DRAW";
            else
                cout<<"player "<<ch<<" wins";
            return ;
        }
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
