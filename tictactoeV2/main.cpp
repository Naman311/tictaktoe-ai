#include<iostream>
#include<queue>

using namespace std;
int arr[9]={0};     //live array

struct NODE
{
    int data;
    int val1;
    char turn;
    int arr[9]={0};
    vector<NODE *> ptr;
    NODE * parent;
    NODE()
    {
        parent=NULL;
    }
}*start,*t1;

int userinput() // for taking user input
{
    int x;
    cin>>x;
    arr[x]=1;
    return x;
}

void showmap()  //function to show map
{
    char ch;
    for(int i=0; i<9;i++)
    {
        if(arr[i]==0)
            ch='_';
        else if(arr[i]==1)
            ch='X';
        else
            ch='O';
        (i==2 || i==5)?cout<<ch<<endl:cout<<ch<<" ";
    }
}

int check_plus(int temparr[])   //functions to check win situations
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
        return temparr[4];      //1 if 1 win or 2 if 2 win
    }
    return(check_plus(temparr)); /*1 if 1 win
                                   2 if 2 win
                                   0 if no win
                                   -1 if all 0*/
}
void treecreate(queue <int> q,NODE *temp )
{
    int flag=0;
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
            t->val1=-10;     //cpu

        }
        else if(t->parent->turn=='C')
        {
            t->arr[t->data]=1;
            t->turn='U';
            t->val1=10;
        }
        temp->ptr.push_back(t);   //add this node address in parent node node pointer vector
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
                temp->val1=-10;
            }
            else if(flag==2)
            {
                temp->val1=10;//-(8-temp->ptr.size());
            }
            else
            {
                temp->val1=0;//-(8-temp->ptr.size());
            }

            t1=temp;
            while(t1->parent!=NULL)
            {
                t1=t1->parent;
                if(t1->turn=='C')
                {
                    for(vector <NODE *>::iterator it=t1->ptr.begin();it!=t1->ptr.end();++it)
                    {
                        if((*it)->val1>t1->val1 )
                        {
                            t1->val1=(*it)->val1;
                        }
                    }
                }
                else if(t1->turn=='U')
                {
                    for(vector <NODE *>::iterator it=t1->ptr.begin();it!=t1->ptr.end();++it)
                    {
                        if((*it)->val1<t1->val1 )//&& (*it)->val1!=30)
                        {
                            t1->val1=(*it)->val1;
                        }
                    }
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
void cpu_turn(NODE * temp)
{
    int ma=-9999,I;
    NODE * tempstart=NULL;
    for(vector <NODE *>::iterator it =temp->ptr.begin();it != temp->ptr.end();++it)
    {
        if((*it)->val1>ma)
        {
            ma=(*it)->val1;
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
            q.push(i); //push all available moves in queue
        }
        else
        {
            start->arr[i]=1;        //push the current move in starts local arr
            start->data=i;          //data has the current moves value
        }
    }
    treecreate(q,start);
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
    int check_win;
    showmap();
    userinput(); // take user input and store in live array
    aiinit();
    while(true)
    {
        cout<<endl;
        showmap();
        user_turn();
        cout<<endl;
        check_win=checkwin(arr);
        if(check_win==1 || check_win==2 || check_win==0)
        {
            break;
        }
        cpu_turn(start);
        cout<<endl;
        check_win=checkwin(arr);
        if(check_win==1 || check_win==2 || check_win==0)
        {
            break;
        }
    }
    showmap();
    if(check_win==1)
    {
        cout<<"X won"<<endl;
    }
    else if(check_win==2)
    {
        cout<<"O won"<<endl;
    }
    else if(check_win==0)
    {
        cout<<"Draw"<<endl;
    }
    //checkwin();*/
    return 0;
}
