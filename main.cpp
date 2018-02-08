#include<iostream>
#include<queue>
using namespace std;
int arr[9]={0};
int temparr[9];
int x;
struct NODE
{
    int data;
    int val;
    vector<NODE *> ptr;
    NODE * parent;
}*start;
void set_temp_arr()
{
    for(int i=0;i<9;i++)
    {
        if(arr[i]!=x)
        {
            temparr[i]=0;
        }
        else
        {
            temparr[i]=1;
        }
    }
}
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
    cin>>x;
    switch(x)
    {
        case 0:arr[0]=i;break;
        case 1:arr[1]=i;break;
        case 2:arr[2]=i;break;
        case 3:arr[3]=i;break;
        case 4:arr[4]=i;break;
        case 5:arr[5]=i;break;
        case 6:arr[6]=i;break;
        case 7:arr[7]=i;break;
        case 8:arr[8]=i;break;
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
void treecreate(queue <int> q,NODE *temp )
{
    for(int i=0;q.size()>0;i++)
    {
        NODE *t= new NODE;
        t->data=q.front();
        t->parent=temp;
        temp->ptr.push_back(t);
        q.pop();
    }
    vector <NODE *>::iterator it =temp->ptr.begin();
    while(it!=temp->ptr.end())
    {  cout<<"TEMP : "<<temp->data<<endl;
        cout<<"it : "<<(*it)->data<<endl;
        queue<int> qtemp;
        for(vector <NODE *>::iterator ittemp =temp->ptr.begin();ittemp!=temp->ptr.end();++ittemp)
        {
            if((*it)->data != (*ittemp)->data)
            {
                qtemp.push((*ittemp)->data);
            }
        }
        treecreate(qtemp,*it);
        it++;
    }//agar temp pe calculated value nahi hai to check kar varna mat kar
    while(temp->parent!=NULL)
    {
        temparr[temp->data]=1;
        temp=temp->parent;
    }
    cout<<endl<<"ARRAY : ";
    for(int i=0;i<9;i++)
    {
        cout<<temparr[i]<<" ";
    }
    cout<<endl;
    set_temp_arr();
    //temp=temp->parent;*/
    //cout<<endl<<"//////////////////"<<"\nTEMP : "<<temp->data<<endl<<"//////////////////"<<endl;
    //cout<<endl<<"TEMP : "<<temp->parent->data<<endl;
}
void showtree(NODE * temp)
{
    for(vector <NODE *>::iterator it =temp->ptr.begin();it != temp->ptr.end();++it)
    {
        cout<<(*it)->data<<" P : "<<(*it)->parent->data<<endl;
        showtree(*it);
    }
    cout<<endl;
}

void aiinit()
{
    set_temp_arr();
    queue<int> q;
    NODE *temp=new NODE;
    start=temp;
    start->parent=NULL;
    for(int i=0;i<4;i++)
    {
        if(arr[i]==0)
        {
            q.push(i);
        }
        else
        {
            start->data=i;
        }
    }
    treecreate(q,start);
    showtree(start);
}

int main()
{
    showmap();
    userinput(1);
    aiinit();
    showmap();
    /*for(int i=1;i<3;i++)
    {
        //aiinput();
    }
   // showmap();
    //checkwin();*/
    return 0;
}
