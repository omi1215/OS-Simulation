#include<iostream>
using namespace std;
class node
{
public:
    node *next;
    int data;
    
    node()
    {
        next=NULL;
      
    }
};
class ADT
{
public:
    node *top;
    int count=-1;
   ADT()
    {
       top = NULL;
    }
    
    void push(int element)
    {
        if(isfull()==true)
        {
            return;
        }
        if(top==NULL)
        {
            node *new_node = new node;
            new_node->data=element;
            top = new_node;
            new_node->next=NULL;
            count++;
        }
        else
        {
            node *new_node = new node;
            new_node->data = element;
            new_node->next = top;
            top = new_node;
            count++;
        }
    }
    bool isempty()
    {
        if(top==NULL)
        {
            return true;
        }
        return false;
    }
    void display()
    {
        node *current = top;
        while(current!=NULL)
        {
            cout<<current->data<<endl;
            current = current->next;
        }
    }
    
    int pop()
    {
        int var;
        if(top==NULL)
        {
            cout<<"stack is underflow"<<endl;
        }
        else
        {
            var = top->data;
            node *p = top;
            top = top->next;
            delete p;
            p=NULL;
            count--;
        }
        return var;
    }
    
    int Top()
    {
        int var ;
        if(top==NULL)
        {
            return -1;
        }
        var = top->data;
        return var;
    }
    
    bool isfull()
    {
        if(count==4)
        {
            return true;
        }
        return false;
    }
    
    
};
void diskmoves(ADT &l1 , ADT &l2)
{
    if(l1.isempty()!=true && l2.isfull()!=true)
    {
        if(l2.isempty()==true)
        {
            l2.push(l1.Top());
            l1.pop();
            
        }
        else
        {
            if(l1.Top()<l2.Top() && l1.Top()!=-1)
            {
                l2.push(l1.Top());
                l1.pop();
            }
            
        }
    }
    else
    {
        return;
    }
}
void display_if(ADT &l1 , ADT &l2 , ADT &l3)
{
    cout<<endl;
    cout<<"first cupboard:"<<endl;
    l1.display();
    cout<<endl;
    cout<<"second cupboard:"<<endl;
    l2.display();
    cout<<endl;
    cout<<"third cupboard:"<<endl;
    l3.display();
    cout<<endl;
}
bool game_solve(ADT &l1)
{
    if(l1.isfull()==true)
    {
        return true;
    }
    return false;
}

int min_moves_to_win()
{
    int count = 5;
    int n = 1;
    for(int i=0;i<count;i++)
    {
        n = n * 2;
    }
    n = n -1;
    return n;
}

// check that
void initialize(ADT &l1,ADT &l2,ADT &l3)
{
    for(int i=5;i>0;i--)
    {
        l1.push(i);
    }
    
}
int main()
{
    ADT l1;
    int count1  = 0;
    ADT l2,l3;
    int choice = 0;
    int mn = 0;
    cout<<"-----------------------------"<<endl;
    cout<<"|||||    THE TOWER OF HENOI    |||||"<<endl;
    cout<<"-----------------------------"<<endl;
    cout<<"1.playing game"<<endl;
    cout<<"2.exit the game"<<endl;
    cin>>choice;
    if(choice==1)
    {
        initialize(l1,l2,l3);
        while(true)
        {
            display_if(l1, l2, l3);
            cout<<"1. move from 1 to 2"<<endl;
            cout<<"2. move from 1 to 3"<<endl;
            cout<<"3. move from 2 to 1"<<endl;
            cout<<"4. move from 2 to 3"<<endl;
            cout<<"5. move from 3 to 1"<<endl;
            cout<<"6. move from 3 to 2"<<endl;
            cin>>mn;
            if(mn==1)
            {
                diskmoves(l1, l2);
                count1++;
            }
            else if(mn==2)
            {
                diskmoves(l1, l3);
                count1++;
            }
            else if(mn==3)
            {
                diskmoves(l2, l1);
                count1++;
            }
            else if(mn==4)
            {
                diskmoves(l2, l3);
                count1++;
            }
            else if(mn==5)
            {
                diskmoves(l3, l1);
                count1++;
            }
            else if(mn==6)
            {
                diskmoves(l3, l2);
                count1++;
            }
            else
            {
                cout<<"you enter the wrong number"<<endl;
            }
            if(game_solve(l3)==true)
            {
                cout<<"solve game successfully"<<endl;
                display_if(l1, l2, l3);
                int mov = min_moves_to_win();
                cout<<endl;
                cout<<"minimum moves to win:"<<mov<<endl;
                if(count1==mov)
                {
                    cout<<"your moves:"<<count1<<endl;
                    cout<<"you complete the game in minimum number of moves"<<endl;
                }
                else
                {
                    cout<<"your moves:"<<count1<<endl;
                    cout<<"you cannot win the game in using minimum number of moves"<<endl;
                }
                exit(1);
            }
            
        }
    }
    else
    {    // Compile the deallocate resource file before running it
    system("g++ -o deallocate dealloc_resource.cpp");
    // Run the deallocate resource file with an argument CALCULATOR
    system("./deallocate TOWEROFHANOI");
        return 0;
    }
 // Compile the deallocate resource file before running it
    system("g++ -o deallocate dealloc_resource.cpp");
    // Run the deallocate resource file with an argument CALCULATOR
    system("./deallocate TOWEROFHANOI");
    return 0;
}


