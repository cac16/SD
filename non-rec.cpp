/*******************************************************************
 * Name        : DSFL Assignment 1- Expression Tree(Non-Recursive) *
 * Author      : NEELKAMAL BHARATI (17U131)                        *
 * Date        : 08-03-2019                                        *
 * Version     : 0.0                                               *
 * Description : Expression Tree (Non-Recursive)                   *
 * Output      : Below the code                                    *
 *******************************************************************/

#include <iostream>
#include <stack>
using namespace std;

class treeNode
{
	friend class stack2;

private:
	char exp;
	treeNode *left;
	treeNode *right;

public:
	treeNode()
	{
			exp='0';
			left=right=NULL;
	}

	treeNode* assign(char c, treeNode* l, treeNode* r)
	{
		treeNode *item= new treeNode;
		item->exp=c;
		item->left= l;
		item->right=r;
		return(item);
	}


};

class node
{
	friend class stack2;
private:
	treeNode *data;
	node *link;
};


class stack2
{
private:
	 node *top;
public:
	stack2()
	{
		top=NULL;
	}
	void push(treeNode *x)
	{
		node *stackEntry = new node;
		stackEntry->data = x;
		stackEntry->link = NULL;

		if(top)
		{
			stackEntry->link=top;
			top=stackEntry;
		}
		else
		{
			top=stackEntry;
		}
	}

	void print()
	{

		node *temp = top;
		while(temp)
		{	cout<<"\n";
			cout<<"\t"<<temp->data->left->exp;
			cout<<"\t"<<temp->data->exp;
			cout<<"\t"<<temp->data->right->exp;
			temp=temp->link;
		}
		cout<<"\nInfix Expression is:";
		non_rec_inorder (top->data);
		cout<<"\nPrefix Expression is:";
		non_rec_preorder(top->data);
	}




	void non_rec_inorder(treeNode *root)
	{
		stack <treeNode *> s1;
		treeNode *current = root;

		while (current  || s1.empty() == false)
		{
		     while (current)
		     {
		            s1.push(current);
		            current = current->left;
		     }
	        current = s1.top();
		    s1.pop();

		    cout << current->exp << " ";
		    current = current->right;

		 }

	}


    void non_rec_preorder(treeNode * root)
    {
        stack <treeNode *> s1;
        treeNode *current = root;
      	while (current  || s1.empty() == false)
		{
		     while (current)
		     {
		            s1.push(current);
		            cout << current->exp << " ";
		            current = current->left;
		     }
	        current = s1.top();
		    s1.pop();


		    current = current->right;

		 }

    }


	treeNode* pop()
	{
		//cout<<"\nPop Called";
		node *temp = top;
		top=top->link;
 		treeNode *tn = temp->data;
 		delete(temp);
		return(tn);
	}
};
int main() {
	stack2 s;
	treeNode *l, *r, *tn , t;

    char arr[20];
    cout<<"Enter the expression: ";
    cin>>arr;
    char * ptr = arr;

    while(*ptr!='\0'){
        if(*ptr=='+' || *ptr=='/' || *ptr=='-' || *ptr=='*'){
            r = s.pop();
            l = s.pop();
            tn = t.assign(*ptr,l,r);
            s.push(tn);
        }
        else{
            tn = t.assign(*ptr,NULL,NULL);
            s.push(tn);
        }
        ptr++;
    }


	s.print();
	return 0;
}


/*******************************
 ************OUTPUT*************
 *Enter the expression: ab+    *
 *                             *
 *       a       +       b     *
 * Infix Expression is:a + b   *
 * Prefix Expression is:+ a b  *
 *******************************/
