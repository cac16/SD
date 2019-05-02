/*********************************************************
* AUTHOR    : NEELKAMAL BHARATI                          *
* ROLL NO.  : 221012                                     *
* GR. NO.   : 17U131                                     *
* TITLE     : LP II Submission- Hashing with chaining    *
**********************************************************/

#include <iostream>

using namespace std;
struct node
{
    int data;
    node *next;
} ;

class lpwc
{
public:

    void addvalue(node *a[],int n)
    {
        node *temp;
        temp=new node;
        cout<<" enter the value to store "<<endl;
        cin>>temp->data;
        int key=temp->data%n;
        node *head=a[key];
        temp->next=head;
        head=temp;
        a[key]=temp;

    }

void print(node *a[],int n)
{
    cout<<" in the print function "<<endl;
 for (int i=0;i<n;i++)
 {
     node *temp=a[i];
     while(temp!=NULL)
     {


        cout<<i<<"  " <<temp->data<<endl;
        temp=temp->next;
     }

 }
}

 int search(node *a[],int n,int svalue)
 {
    int key = svalue%n;
    node *temp=a[key];
    while(temp->data!=svalue && temp->next!=NULL)
    {
        temp=temp->next;
    }
    if (temp->data ==svalue)
        return key;
    else
        return -1;



 }
 void deletev( node *a[],int n,int dvalue  )
 {
     int key=dvalue%n;

     node *temp=a[key],*temp2=temp;
     while(temp->data!=dvalue && temp->next!=NULL)
     {  cout<<" in the while "<<endl;
         temp2=temp;
         temp=temp->next;
     }

     if (temp->data==dvalue)

     {
         cout<<" in the if "<<endl;
      if (temp->data==a[key]->data)
       {

        a[key]=temp->next;
        delete temp;
       }
        else
            temp2->next=temp->next;
        delete temp;

     }
     else
     {
         cout<<" No member found to delete "<<endl;
     }


 }

};



int main()
{
    int n;
    lpwc l;
    cout<<"enter the size of hashtable "<<endl;
    cin>>n;
    node  *a[n];
    for (int i=0;i<n;i++)
        {

        a[i]=new node;
        a[i]=NULL;
        }
char cont='y';
while(cont=='y')
{

 int ch;
 cout<<"................... MENU .....................  "<<endl;
 cout<<" enter 1 to add value into the hash table "<<endl;
 cout<<" Enter 2 to search value in the hash table "<<endl;
 cout<<" Enter 3 to delete value from the table "<<endl;
 cout<<" Enter 4 to print the hash table "<<endl;
 cout<<" Enter 5 to exit "<<endl;

 cin>>ch;
 switch(ch)
 {

 case 1:
     {


     char c='y';
     while(c=='y')
        {
        l.addvalue(a,n);
        cout<<" want to add more "<<endl;
        cin>>c;

        }
        break;
     }

 case 2:
     {
     cout<<" enter the value to be search "<<endl;
     int svalue;
     cin>>svalue;
      if (l.search(a,n,svalue)!=-1)
              cout<<" given value is in the hashtable with key "<<l.search(a,n,svalue)<<endl;
      else
                cout<<" given value is not in the table "<<endl;
       break;
     }
 case 3:
         cout<<" enter the value to delete "<<endl;
         int dvalue;
         cin>>dvalue;
        l.deletev(a,n,dvalue);

   break;

    case 4:
        l.print(a,n);
        break;
    case 5:
        cont='n';

 }


}

    //cout << "Hello world!" << endl;
    return 0;
}

/***************************************************

enter the size of hashtable
100
................... MENU .....................
 enter 1 to add value into the hash table
 Enter 2 to search value in the hash table
 Enter 3 to delete value from the table
 Enter 4 to print the hash table
 Enter 5 to exit
1
 enter the value to store
26
 want to add more
y
 enter the value to store
226
 want to add more
y
 enter the value to store
126
 want to add more
y
 enter the value to store
27
 want to add more
y
 enter the value to store
127
 want to add more
y
 enter the value to store
11
 want to add more
n
................... MENU .....................
 enter 1 to add value into the hash table
 Enter 2 to search value in the hash table
 Enter 3 to delete value from the table
 Enter 4 to print the hash table
 Enter 5 to exit
4
 in the print function
11  11
26  126
26  226
26  26
27  127
27  27
................... MENU .....................
 enter 1 to add value into the hash table
 Enter 2 to search value in the hash table
 Enter 3 to delete value from the table
 Enter 4 to print the hash table
 Enter 5 to exit
3
 enter the value to delete
226
 in the while
 in the if
................... MENU .....................
 enter 1 to add value into the hash table
 Enter 2 to search value in the hash table
 Enter 3 to delete value from the table
 Enter 4 to print the hash table
 Enter 5 to exit
4
 in the print function
11  11
26  126
26  26
27  127
27  27
................... MENU .....................
 enter 1 to add value into the hash table
 Enter 2 to search value in the hash table
 Enter 3 to delete value from the table
 Enter 4 to print the hash table
 Enter 5 to exit
2
 enter the value to be search
126
 given value is in the hashtable with key 26
................... MENU .....................
 enter 1 to add value into the hash table
 Enter 2 to search value in the hash table
 Enter 3 to delete value from the table
 Enter 4 to print the hash table
 Enter 5 to exit






********************************************************/
