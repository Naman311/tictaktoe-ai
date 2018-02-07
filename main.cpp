#include<iostream>
#include<queue>
using namespace std;
int arr[9]={0};

struct NODE
{
    int data;
    int val;
    vector<NODE *> ptr;
};
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
//void treecreate_down(queue <int> q,NODE *temp);
/*void treecreate_side(queue <int> q,NODE *temp)
{
    //cout<<"SIZE = "<<q.size()<<endl;
    if(q.size()>0)
    {
        NODE *t= new NODE;
        t->right=temp;
        temp->left=t;
        t->data=q.front();
        treecreate_down(q,t);
        q.pop();
        //cout<<t->data<<" (side of "<<temp->data<<" )\n";
        treecreate_side(q,t);

    }
}
void treecreate_down(queue <int> q,NODE *temp)
{
    if(!q.empty())
    {
     NODE *t= new NODE;
     temp->down=t;
     t->up=temp;
     t->data=q.front();
     q.pop();
     //cout<<t->data<<" (down "<<temp->data<<" )\n";
     treecreate_side(q,t);
     treecreate_down(q,t);
    }
}*/
void treecreate(queue <int> q,NODE *temp )
{
    for(int i=0;q.size()>0;i++)
    {
        //cout<<q.front()<<" ";
        NODE *t= new NODE;
        t->data=q.front();
        //cout<<"  YOV : "<<t->data<<endl;
        q.pop();
       // treecreate(q,t);

        temp->ptr.push_back(t);
    }
}
/*void treecreate_down(queue <int> q,NODE *temp)
{
    if(q.empty())
    {
        NODE *t= new NODE;
        temp->down=t;
        t->up=temp;
        t->data=q.front();
        q.pop();
        treecreate_side(q,t);
    }
        else
        {
            while(temp->right!=NULL)
            {
                temp=temp->right;
            }
            temp->right=t;
            t->left=temp;
            t->data=q.front();
            cout<<t->data<<"->";
            q.pop();
            treecreate(q,t,si);
            //treecreate(q,t,si-1);
        }
        cout<<endl;

    }
    else
    {
        return;
    }
}*/
void showtree(NODE * temp)
{
    for(vector <NODE *>::iterator it =temp->ptr.begin();it != temp->ptr.end();++it)
    {
        cout<<(*it)->data<<" ";
    }
    cout<<endl;
}
void aiinit()
{
    queue<int> q;
    NODE *start=new NODE;
    for(int i=0;i<4;i++)
    {
        if(arr[i]==0)
        {
            q.push(i);
            //cout<<"Pushing = "<<i<<endl;
        }
        else
        {
            start->data=i;
        }
    }
    //cout<<"size ="<<q.size()<<endl;
    treecreate(q,start);
    showtree(start);
   /* showtree(start->ptr[0],2);
    showtree(start->ptr[1],2);
    showtree(start->ptr[2],2);*/
}

int main()
{
    showmap();
    userinput(1);
    aiinit();
    /*for(int i=1;i<3;i++)
    {
        //aiinput();
    }
   // showmap();
    //checkwin();*/
    return 0;
}
