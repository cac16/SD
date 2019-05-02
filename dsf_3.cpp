/***************************************************************
 * Name        : DSFL Assignment - BINARY SEARCH TREE          *
 * Author      : NEELKAMAL BHARATI (17U131)                    *
 * Date        : 08-03-2019                                    *
 * Version     : 0.0                                           *
 * Description : BINARY SEARCH TREE                            *
 * Output      : Below the code                                *
 ***************************************************************/



#include <iostream>
#include <stack>
using namespace std;
int array[20], z=0;
class treeNode
{
    friend void inorder(treeNode * root);
    friend treeNode * createTree();
    friend void addNode(int a, treeNode *root);
    friend int small(treeNode * root);
    friend int height(treeNode * root);
    friend void mirror(treeNode * root);
    friend treeNode * search(treeNode * root, int val);
private:
	int data;
	treeNode *left;
	treeNode *right;

public:
	treeNode()
	{
		left=NULL; right=NULL;
	}




};

void addNode(int a, treeNode *root){

        if(a>=root->data){
            if(root->right!=NULL){
            addNode(a, root->right);
            }
            else{
                treeNode * nnode = new treeNode;
                nnode->data = a;
                root->right = nnode;
            }
        }
        else{
            if(root->left!=NULL){
            addNode(a, root->left);
            }
            else{
                treeNode * nnode = new treeNode;
                nnode->data = a;
                root->left = nnode;
            }
        }
}





treeNode * createTree(){

    int arr[20], n, i;
    cout<<"Enter no. of elements in the tree: ";
    cin>>n;

    for(i=0;i<n;i++){
        cin>>arr[i];
    }

    treeNode * root = new treeNode;
    treeNode * temp = root;
    root->data = arr[0];

    for(i=1;i<n;i++){
        addNode(arr[i], root);
    }
    return root;


}

int height(treeNode * root){
	if(root==NULL)return 0;
	int r_length = height(root->right);
	int l_length = height(root->left);

	if(r_length > l_length){
		return r_length+1;
	}
	else{
		return l_length+1;
	}
}

int small(treeNode * root){

	treeNode * temp = root;
	while(temp->left!=NULL){
		temp = temp->left;
	}
	return temp->data;
}

void inorder(treeNode *root){
        if(root==NULL){
            return;
        }
       	inorder(root->left);
	array[z]=root->data;
	z++;
	cout<<root->data<<endl;
        inorder(root->right);
	}


void mirror(treeNode * root)
{
    treeNode * current = root;
    treeNode * temp;
    if(current==NULL)
    {
        return;
    }
    else{
        temp = current->left;
        current->left = current->right;
        current->right = temp;
        mirror(current->right);
        mirror(current->left);


    }

}

treeNode * search(treeNode * root, int val)
{

    if(root==NULL){
        cout<<"Element not found!\n";
        return NULL;

    }
    else if(val==root->data){
        cout<<"Element found!\n";
        return root;
    }
    else if(val>root->data){
        search(root->right, val);
    }
    else{
        search(root->left, val);
    }


}



int main()
{	int t;
	treeNode * root;
	while(true){

		cout<<"\n\nMENU:\n\t1.\tCreate tree.\n\t2.\tInsert node.\n\t3.\tHeight.\n\t4.\tSmallest element.\n\t5.\tMirror.\n\t6.\tSearch\nEnter choice: ";
		cin>>t;
		switch(t){
			case 1: root = createTree();
				inorder(root);
				break;

			case 2: cout<<"Enter  element: ";
				cin>>t;
				addNode(t, root);
				cout<<"Inorder: \n";
				inorder(root);
				break;

			case 3: cout<<"Height of the tree is "<<height(root)<<endl;
				break;

			case 4: cout<<"Smallest element in the tree is "<<small(root)<<endl;
				break;

            case 5: cout<<"Mirror inorder is \n";
                    mirror(root);
                    cout<<"Inorder: \n";
                    inorder(root);

            case 6: cout<<"Enter value to find \n";
                    int k;
                    cin>>k;
                    search(root, k);
                    break;
			default: return 0;

		}
	}
}

/***OUTPUT***
MENU:
        1.      Create tree.
        2.      Insert node.
        3.      Height.
        4.      Smallest element.
        5.      Mirror.
        6.      Search
Enter choice: 1
Enter no. of elements in the tree: 6
200
300
100
50
150
250
50
100
150
200
250
300


MENU:
        1.      Create tree.
        2.      Insert node.
        3.      Height.
        4.      Smallest element.
        5.      Mirror.
        6.      Search
Enter choice: 2
Enter  element: 350
Inorder:
50
100
150
200
250
300
350


MENU:
        1.      Create tree.
        2.      Insert node.
        3.      Height.
        4.      Smallest element.
        5.      Mirror.
        6.      Search
Enter choice: 3
Height of the tree is 3


MENU:
        1.      Create tree.
        2.      Insert node.
        3.      Height.
        4.      Smallest element.
        5.      Mirror.
        6.      Search
Enter choice: 4
Smallest element in the tree is 50


MENU:
        1.      Create tree.
        2.      Insert node.
        3.      Height.
        4.      Smallest element.
        5.      Mirror.
        6.      Search
Enter choice: 5
Mirror inorder is
Inorder:
350
300
250
200
150
100
50
*/












