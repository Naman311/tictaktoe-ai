#include<iostream>
#include<queue>
using namespace std;
int arr[9]={0};
struct NODE
{
    int data;
    int val1;
    int val2;
    char turn;
    int arr[9]={0};
    vector<NODE *> ptr;
    NODE * parent;
    NODE()
    {
        val2=0;
        parent=NULL;
    }
}*start,*t1;
int userinput()
{
    int x;
    cin>>x;
    arr[x]=1;
    return x;
}
void showmap()
{
    for(int i=0; i<9;i++)
    {
        (i==2 || i==5)?cout<<arr[i]<<endl:cout<<arr[i]<<" ";
    }
}
int check_plus(int temparr[])
{
    for(int i=0,j=0;i<3;i++,j=j+3)
    {
        if((temparr[0+i]==1 && temparr[3+i]==1 && temparr[6+i]==1)||(temparr[0+j]==1 && temparr[1+j]==1 && temparr[2+j]==1))
        {
            return 1;
        }
        else if((temparr[0+i]==2 && temparr[3+i]==2 && temparr[6+i]==2)||(temparr[0+j]==2 && temparr[1+j]==2 && temparr[2+j]==2))
        {
            return 2;
        }
    }
    if(temparr[0]==0||temparr[1]==0||temparr[2]==0||temparr[3]==0||temparr[4]==0||temparr[5]==0||temparr[6]==0||temparr[7]==0||temparr[8]==0)
        return -1;
    else
        return 0;
}
bool check_x(int temparr[])
{
    if((temparr[0]==temparr[4] && temparr[4]==temparr[8]) || (temparr[2]==temparr[4] && temparr[4]==temparr[6]))
        return true;
    else
        return false;
}
int checkwin(int temparr[])
{
    if(check_x(temparr))
    {
        return temparr[4];
    }
    return(check_plus(temparr));
}
void treecreate(queue <int> q,NODE *temp )
{
    int flag=-1;
    for(int i=0;q.size()>0;i++)
    {
        NODE *t= new NODE;
        t->data=q.front();
        t->parent=temp;
        copy(temp->arr,temp->arr+9,t->arr);
        if(t->parent->turn=='U')
        {
            t->arr[t->data]=2;
            t->turn='C';
            t->val1=30;
        }
        else if(t->parent->turn=='C')
        {
            t->arr[t->data]=1;
            t->turn='U';
            t->val1=-10;
        }
        temp->ptr.push_back(t);
        q.pop();
    }
    if(temp->ptr.size()<5)
    {
        flag=checkwin(temp->arr);
        if(flag!=-1)
        {//1 for user 2 for cpu 0 for draw
            temp->ptr.clear();
            if(flag==1)
            {
                temp->val1=0;
                temp->val2=-1;
            }
            else if(flag==2)
            {
                temp->val1=20;
                temp->val2=1;
            }
            else
            {
                temp->val1=10;
                temp->val2=0;
            }
            t1=temp;
            while(t1->parent!=NULL)
            {
                t1=t1->parent;
                if(t1->turn=='C')
                {
                    for(vector <NODE *>::iterator it=t1->ptr.begin();it!=t1->ptr.end();++it)
                    {
                        if((*it)->val1<t1->val1 && (*it)->val1!=-10)
                        {
                            //cout<<(*it)->val<<"  "<<t1->val<<"   ";
                            t1->val1=(*it)->val1;
                            //cout<<(*it)->val<<"  "<<t1->val<<endl;
                        }
                    }
                }
                else if(t1->turn=='U')
                {
                    for(vector <NODE *>::iterator it=t1->ptr.begin();it!=t1->ptr.end();++it)
                    {
                        if((*it)->val1>t1->val1 && (*it)->val1!=30)
                        {
                            t1->val1=(*it)->val1;
                        }
                    }
                }
                if(flag==2)
                {
                    (t1->val2)++;
                }
                else if(flag==1)
                {
                    (t1->val2)--;
                }
            }
        }
    }
    if(flag==-1)
    {
        vector <NODE *>::iterator it =temp->ptr.begin();
        while(it!=temp->ptr.end())
        {
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
        }
    }
}
    /*cout<<endl<<"ARRAY : ";
    for(int i=0;i<9;i++)
    {
        cout<<temparr[i]<<" ";
    }
    cout<<endl;
}
/*void showtree(NODE * temp)
{
    for(vector <NODE *>::iterator it =temp->ptr.begin();it != temp->ptr.end();++it)
    {
        cout<<(*it)->data<<" P : "<<(*it)->parent->data<<" Value : "<<(*it)->val<<endl;
        showtree(*it);
    }
    //cout<<endl;
}*/

void pathcheck(NODE * temp)  //first choice path
{
    if(temp->ptr.size()!=0)
    {
        vector <NODE *>::iterator it;
        cout<<"P : "<<temp->data<<" TURN : "<<temp->turn<<endl;
        for(it =temp->ptr.begin();it != temp->ptr.end();++it)
        {
            cout<<"D:"<<(*it)->data<<" V:"<<(*it)->val1<<endl;
        }
        it=temp->ptr.begin();
        cout<<endl<<endl;
        pathcheck(*it);
    }
}
void showtree(NODE * temp)      //all moves at this point
{
    for(vector <NODE *>::iterator it =temp->ptr.begin();it != temp->ptr.end();++it)
    {
        cout<<(*it)->data<<" P : "<<(*it)->parent->data<<" Value1 : "<<(*it)->val1<<" Value2 : "<<(*it)->val2<<" TURN : "<<(*it)->turn<<endl;
        //showtree(*it);
    }
}
void cpu_turn(NODE * temp)
{
    int ma1=-9999,ma2=-9999,I;
    NODE * tempstart=NULL;
    for(vector <NODE *>::iterator it =temp->ptr.begin();it != temp->ptr.end();++it)
    {
        if((*it)->val1>ma1)
        {
            ma1=(*it)->val1;
            ma2=(*it)->val2;
            I=(*it)->data;
            tempstart=*it;
        }
        else if((*it)->val1==ma1 && (*it)->val2>ma2)
        {
            ma1=(*it)->val1;
            ma2=(*it)->val2;
            I=(*it)->data;
            tempstart=*it;
        }
    }
    arr[I]=2;
    start=tempstart;
}
void aiinit()
{
    queue<int> q;
    NODE *temp=new NODE;
    start=temp;
    start->turn='U';
    start->val1=-10;
    for(int i=0;i<9;i++)
    {
        if(arr[i]==0)
        {
            q.push(i);
        }
        else
        {
            start->arr[i]=1;
            start->data=i;
        }
    }
    treecreate(q,start);
    showtree(start);
    cout<<endl;
    cpu_turn(start);
}
void user_turn()
{
    int x=userinput();
    for(vector <NODE *>::iterator it =start->ptr.begin();it != start->ptr.end();++it)
    {
        if((*it)->data==x)
        {
            start=*it;
            break;
        }
    }
}
int main()
{
    showmap();
    userinput();
    aiinit();
    //pathcheck(start);

    for(int i=0;i<3;i++)
    {
        cout<<endl;
        showmap();
        user_turn();
        cout<<endl;
        showtree(start);
        cpu_turn(start);
        cout<<endl;
        showtree(start);
    }
    showmap();
    //checkwin();*/
    return 0;
}
