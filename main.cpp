#include<iostream>
#include<queue>
using namespace std;
int arr[9]={0};
int temparr[9];
struct NODE
{
    int data;
    int val;
    char turn;
    vector<NODE *> ptr;
    NODE * parent;
    NODE()
    {
        val=0;
        parent=NULL;
    }
}*start,*t1;
void set_temp_arr()
{
    for(int i=0;i<9;i++)
    {
        if(arr[i]==0)
        {
            temparr[i]=0;
        }
        else
        {
            temparr[i]=1;
        }
    }
}
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
int check_plus()
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
bool check_x()
{
    if((temparr[0]==temparr[4] && temparr[4]==temparr[8]) || (temparr[2]==temparr[4] && temparr[4]==temparr[6]))
        return true;
    else
        return false;
}
int checkwin()
{
    if(check_x())
    {//cout<<temparr[4]<<" "<<arr[4]<<endl;
        return temparr[4];
    }
    return(check_plus());
}
void treecreate(queue <int> q,NODE *temp )
{
    int flag=-1;
    for(int i=0;q.size()>0;i++)
    {
        NODE *t= new NODE;
        t->data=q.front();
        t->parent=temp;
        if(t->parent->turn=='U')
        {
            t->turn='C';
        }
        else if(t->parent->turn=='C')
        {
            t->turn='U';
        }
        temp->ptr.push_back(t);
        q.pop();
    }
    //cout<<" TEMP : "<<temp->data<<endl;
    if(temp->ptr.size()<=3)
    {//cout<<" TEMP : "<<temp->data<<endl;
        t1=temp;
        while(t1->parent!=NULL)
        {
            if(t1->turn=='U')
            {
                temparr[t1->data]=1;
            }
            else if(t1->turn=='C')
            {
                temparr[t1->data]=2;
            }
            t1=t1->parent;
        }
        //cout<<" TEMP : "<<temp->data<<endl;
        /*cout<<"ARRAY : ";
                for(int i=0;i<9;i++)
                {
                    cout<<temparr[i]<<" ";
                }
                cout<<endl<<endl;*/
        flag=checkwin();
        //cout<<"FLAG = "<<flag<<endl;
        if(flag==0)
        {
            //cout<<"DRAW";
        }
        else if(flag!=-1)
        {
            t1=temp;
            while(t1->parent!=NULL)
            {
                if(flag==2)
                {
                    (t1->val)++;
                }
                else if(flag==1)
                {
                    (t1->val)--;
                }
                t1=t1->parent;
            }
            set_temp_arr();
        }
    }
    if(flag==-1)
    {
        vector <NODE *>::iterator it =temp->ptr.begin();
        while(it!=temp->ptr.end())
        {  //cout<<"TEMP : "<<temp->data<<endl;
            //cout<<"it : "<<(*it)->data<<endl;
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
    /*cout<<endl<<"ARRAY : ";
    for(int i=0;i<9;i++)
    {
        cout<<temparr[i]<<" ";
    }
    cout<<endl;*/
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
/*
void showtree(NODE * temp)  //first choice path
{
    if(temp->ptr.size()!=0)
    {
    vector <NODE *>::iterator it =temp->ptr.begin();
    cout<<(*it)->data<<" P : "<<(*it)->parent->data<<" Value : "<<(*it)->val<<" TURN : "<<(*it)->turn<<endl;
    showtree(*it);
    cout<<endl;
    }
}*/
void showtree(NODE * temp)      //all moves at this point
{
    for(vector <NODE *>::iterator it =temp->ptr.begin();it != temp->ptr.end();++it)
    {
        cout<<(*it)->data<<" P : "<<(*it)->parent->data<<" Value : "<<(*it)->val<<" TURN : "<<(*it)->turn<<endl;
        //showtree(*it);
    }
}
void cpu_turn(NODE * temp)
{
    int ma=-9999,I;
    NODE * tempstart=NULL;
    for(vector <NODE *>::iterator it =temp->ptr.begin();it != temp->ptr.end();++it)
    {
        if((*it)->val>ma)
        {
            ma=(*it)->val;
            I=(*it)->data;
            tempstart=*it;
        }
    }
    arr[I]=2;
    start=tempstart;
}
void aiinit()
{
    set_temp_arr();
    queue<int> q;
    NODE *temp=new NODE;
    start=temp;
    start->turn='U';
    for(int i=0;i<9;i++)
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
    for(int i=0;i<3;i++)
    {
        cout<<endl;
        showmap();
        user_turn();
        cout<<endl;
        showtree(start);
        cpu_turn(start);
    }
   // showmap();
    //checkwin();*/
    return 0;
}
/*problems -
1.everytime stops after 6 input_iterator_tag
2. in _ 1 0 1 0 1 0 1 _ it doent stop on win of 0
*/
