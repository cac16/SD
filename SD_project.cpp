#include <graphics.h>
#include <iostream>
#include <stack>
#include <vector>
#include <cmath>
#include <queue>
#include <stdlib.h>
#include <string>
#define nullptr NULL
using namespace std;



enum Color {REDn, BLACKn, DOUBLE_BLACKn};

struct Node
{
    int data;
    int color;
    Node *left, *right, *parent;

    explicit Node(int);
};

class RBTree
{
    private:

    protected:
        void rotateLeft(Node *&);
        void rotateRight(Node *&);
        void fixInsertRBTree(Node *&);
        void fixDeleteRBTree(Node *&);
        void inorderBST(Node *&);
        void preorderBST(Node *&);
        int getColor(Node *&);
        void setColor(Node *&, int);
        Node *minValueNode(Node *&);
        Node *maxValueNode(Node *&);
        Node* insertBST(Node *&, Node *&);
        Node* deleteBST(Node *&, int);
        int getBlackHeight(Node *);
    public:
        Node *root;
        RBTree();
        void insertValue(int);
        void deleteValue(int);
        void merge(RBTree);
        void inorder();
        void preorder();
        void draw(int st, int en, int h, int radius, Node* root);

};




Node::Node(int data) {
    this->data = data;
    color = REDn;
    left = right = parent = NULL;
}

RBTree::RBTree() {
    root = nullptr;
}

int RBTree::getColor(Node *&node) {
    if (node == nullptr)
        return BLACKn;

    return node->color;
}

void RBTree::setColor(Node *&node, int color) {
    if (node == nullptr)
        return;

    node->color = color;
}

Node* RBTree::insertBST(Node *&root, Node *&ptr) {
    if (root == nullptr)
        return ptr;

    if (ptr->data < root->data) {
        root->left = insertBST(root->left, ptr);
        root->left->parent = root;
    } else if (ptr->data > root->data) {
        root->right = insertBST(root->right, ptr);
        root->right->parent = root;
    }

    return root;
}

void RBTree::insertValue(int n) {
    Node *node = new Node(n);
    root = insertBST(root, node);
    fixInsertRBTree(node);
}

void RBTree::rotateLeft(Node *&ptr) {
    Node *right_child = ptr->right;
    ptr->right = right_child->left;

    if (ptr->right != nullptr)
        ptr->right->parent = ptr;

    right_child->parent = ptr->parent;

    if (ptr->parent == nullptr)
        root = right_child;
    else if (ptr == ptr->parent->left)
        ptr->parent->left = right_child;
    else
        ptr->parent->right = right_child;

    right_child->left = ptr;
    ptr->parent = right_child;
}

void RBTree::rotateRight(Node *&ptr) {
    Node *left_child = ptr->left;
    ptr->left = left_child->right;

    if (ptr->left != nullptr)
        ptr->left->parent = ptr;

    left_child->parent = ptr->parent;

    if (ptr->parent == nullptr)
        root = left_child;
    else if (ptr == ptr->parent->left)
        ptr->parent->left = left_child;
    else
        ptr->parent->right = left_child;

    left_child->right = ptr;
    ptr->parent = left_child;
}

void RBTree::fixInsertRBTree(Node *&ptr) {
    Node *parent = nullptr;
    Node *grandparent = nullptr;
    while (ptr != root && getColor(ptr) == REDn && getColor(ptr->parent) == REDn) {
        parent = ptr->parent;
        grandparent = parent->parent;
        if (parent == grandparent->left) {
            Node *uncle = grandparent->right;
            if (getColor(uncle) == REDn) {
                setColor(uncle, BLACKn);
                setColor(parent, BLACKn);
                setColor(grandparent, REDn);
                ptr = grandparent;
            } else {
                if (ptr == parent->right) {
                    rotateLeft(parent);
                    ptr = parent;
                    parent = ptr->parent;
                }
                rotateRight(grandparent);
                swap(parent->color, grandparent->color);
                ptr = parent;
            }
        } else {
            Node *uncle = grandparent->left;
            if (getColor(uncle) == REDn) {
                setColor(uncle, BLACKn);
                setColor(parent, BLACKn);
                setColor(grandparent, REDn);
                ptr = grandparent;
            } else {
                if (ptr == parent->left) {
                    rotateRight(parent);
                    ptr = parent;
                    parent = ptr->parent;
                }
                rotateLeft(grandparent);
                swap(parent->color, grandparent->color);
                ptr = parent;
            }
        }
    }
    setColor(root, BLACKn);
}

void RBTree::fixDeleteRBTree(Node *&node) {
    if (node == nullptr)
        return;

    if (node == root) {
        root = nullptr;
        return;
    }

    if (getColor(node) == REDn || getColor(node->left) == REDn || getColor(node->right) == REDn) {
        Node *child = node->left != nullptr ? node->left : node->right;

        if (node == node->parent->left) {
            node->parent->left = child;
            if (child != nullptr)
                child->parent = node->parent;
            setColor(child, BLACKn);
            delete (node);
        } else {
            node->parent->right = child;
            if (child != nullptr)
                child->parent = node->parent;
            setColor(child, BLACKn);
            delete (node);
        }
    } else {
        Node *sibling = nullptr;
        Node *parent = nullptr;
        Node *ptr = node;
        setColor(ptr, DOUBLE_BLACKn);
        while (ptr != root && getColor(ptr) == DOUBLE_BLACKn) {
            parent = ptr->parent;
            if (ptr == parent->left) {
                sibling = parent->right;
                if (getColor(sibling) == REDn) {
                    setColor(sibling, BLACKn);
                    setColor(parent, REDn);
                    rotateLeft(parent);
                } else {
                    if (getColor(sibling->left) == BLACKn && getColor(sibling->right) == BLACKn) {
                        setColor(sibling, REDn);
                        if(getColor(parent) == REDn)
                            setColor(parent, BLACKn);
                        else
                            setColor(parent, DOUBLE_BLACKn);
                        ptr = parent;
                    } else {
                        if (getColor(sibling->right) == BLACKn) {
                            setColor(sibling->left, BLACKn);
                            setColor(sibling, REDn);
                            rotateRight(sibling);
                            sibling = parent->right;
                        }
                        setColor(sibling, parent->color);
                        setColor(parent, BLACKn);
                        setColor(sibling->right, BLACKn);
                        rotateLeft(parent);
                        break;
                    }
                }
            } else {
                sibling = parent->left;
                if (getColor(sibling) == REDn) {
                    setColor(sibling, BLACKn);
                    setColor(parent, REDn);
                    rotateRight(parent);
                } else {
                    if (getColor(sibling->left) == BLACKn && getColor(sibling->right) == BLACKn) {
                        setColor(sibling, REDn);
                        if (getColor(parent) == REDn)
                            setColor(parent, BLACKn);
                        else
                            setColor(parent, DOUBLE_BLACKn);
                        ptr = parent;
                    } else {
                        if (getColor(sibling->left) == BLACKn) {
                            setColor(sibling->right, BLACKn);
                            setColor(sibling, REDn);
                            rotateLeft(sibling);
                            sibling = parent->left;
                        }
                        setColor(sibling, parent->color);
                        setColor(parent, BLACKn);
                        setColor(sibling->left, BLACKn);
                        rotateRight(parent);
                        break;
                    }
                }
            }
        }
        if (node == node->parent->left)
            node->parent->left = nullptr;
        else
            node->parent->right = nullptr;
        delete(node);
        setColor(root, BLACKn);
    }
}

Node* RBTree::deleteBST(Node *&root, int data) {
    if (root == nullptr)
        return root;

    if (data < root->data)
        return deleteBST(root->left, data);

    if (data > root->data)
        return deleteBST(root->right, data);

    if (root->left == nullptr || root->right == nullptr)
        return root;

    Node *temp = minValueNode(root->right);
    root->data = temp->data;
    return deleteBST(root->right, temp->data);
}

void RBTree::deleteValue(int data) {
    Node *node = deleteBST(root, data);
    fixDeleteRBTree(node);
}

void RBTree::inorderBST(Node *&ptr) {
    if (ptr == nullptr)
        return;

    inorderBST(ptr->left);
    cout << ptr->data << " " << ptr->color << endl;
    inorderBST(ptr->right);
}

void RBTree::inorder() {
    inorderBST(root);
}

void RBTree::preorderBST(Node *&ptr) {
    if (ptr == nullptr)
        return;

    cout << ptr->data << " " << ptr->color << endl;
    preorderBST(ptr->left);
    preorderBST(ptr->right);
}

void RBTree::preorder() {
    preorderBST(root);
    cout << "-------" << endl;
}

Node *RBTree::minValueNode(Node *&node) {

    Node *ptr = node;

    while (ptr->left != nullptr)
        ptr = ptr->left;

    return ptr;
}

Node* RBTree::maxValueNode(Node *&node) {
    Node *ptr = node;

    while (ptr->right != nullptr)
        ptr = ptr->right;

    return ptr;
}

int RBTree::getBlackHeight(Node *node) {
    int blackheight = 0;
    while (node != nullptr) {
        if (getColor(node) == BLACK)
            blackheight++;
        node = node->left;
    }
    return blackheight;
}

// Test case 1 : 5 2 9 1 6 8 0 20 30 35 40 50 0
// Test case 2 : 3 0 5 0
// Test case 3 : 2 1 3 0 8 9 4 5 0

void RBTree::merge(RBTree rbTree2) {
    int temp;
    Node *c, *temp_ptr;
    Node *root1 = root;
    Node *root2 = rbTree2.root;
    int initialblackheight1 = getBlackHeight(root1);
    int initialblackheight2 = getBlackHeight(root2);
    if (initialblackheight1 > initialblackheight2) {
        c = maxValueNode(root1);
        temp = c->data;
        deleteValue(c->data);
        root1 = root;
    }
    else if (initialblackheight2 > initialblackheight1) {
        c = minValueNode(root2);
        temp = c->data;
        rbTree2.deleteValue(c->data);
        root2 = rbTree2.root;
    }
    else {
        c = minValueNode(root2);
        temp = c->data;
        rbTree2.deleteValue(c->data);
        root2 = rbTree2.root;
        if (initialblackheight1 != getBlackHeight(root2)) {
            rbTree2.insertValue(c->data);
            root2 = rbTree2.root;
            c = maxValueNode(root1);
            temp = c->data;
            deleteValue(c->data);
            root1 = root;
        }
    }
    setColor(c,REDn);
    int finalblackheight1 = getBlackHeight(root1);
    int finalblackheight2 = getBlackHeight(root2);
    if (finalblackheight1 == finalblackheight2) {
        c->left = root1;
        root1->parent = c;
        c->right = root2;
        root2->parent = c;
        setColor(c,BLACKn);
        c->data = temp;
        root = c;
    }
    else if (finalblackheight2 > finalblackheight1) {
        Node *ptr = root2;
        while (finalblackheight1 != getBlackHeight(ptr)) {
            temp_ptr = ptr;
            ptr = ptr->left;
        }
        Node *ptr_parent;
        if (ptr == nullptr)
            ptr_parent = temp_ptr;
        else
            ptr_parent = ptr->parent;
        c->left = root1;
        if (root1 != nullptr)
            root1->parent = c;
        c->right = ptr;
        if (ptr != nullptr)
            ptr->parent = c;
        ptr_parent->left = c;
        c->parent = ptr_parent;
        if (getColor(ptr_parent) == REDn) {
            fixInsertRBTree(c);
        }
        else if (getColor(ptr) == REDn){
            fixInsertRBTree(ptr);
        }
        c->data = temp;
        root = root2;
    }
    else {
        Node *ptr = root1;
        while (finalblackheight2 != getBlackHeight(ptr)) {
            ptr = ptr->right;
        }
        Node *ptr_parent = ptr->parent;
        c->right = root2;
        root2->parent = c;
        c->left = ptr;
        ptr->parent = c;
        ptr_parent->right = c;
        c->parent = ptr_parent;
        if (getColor(ptr_parent) == REDn) {
            fixInsertRBTree(c);
        }
        else if (getColor(ptr) == REDn) {
            fixInsertRBTree(ptr);
        }
        c->data = temp;
        root = root1;
    }
    return;
}

void flood_fill(int x, int y, int f_color, int b_color)
{
if(getpixel(x,y) == b_color)
{
putpixel(x, y, f_color);
flood_fill(x+1, y , f_color, b_color);
flood_fill(x , y+1, f_color, b_color);
flood_fill(x-1, y , f_color, b_color);
flood_fill(x , y-1, f_color, b_color);
}
}


void bound_fill(int x, int y, int f_color, int b_color)
{
if(getpixel(x,y)!=b_color && getpixel(x,y)!=f_color)
{
putpixel(x, y, f_color);
bound_fill(x+1, y , f_color, b_color);
bound_fill(x , y+1, f_color, b_color);
bound_fill(x-1, y , f_color, b_color);
bound_fill(x , y-1, f_color, b_color);
}
}

stack < pair <int , int> >stk;

void RBTree::draw(int st, int en, int h, int radius, Node* root){


    int mid=(en+st)/2 ;
    char arr[10];


    if(!stk.empty()){
            setcolor(BLACK);
            line(stk.top().first, stk.top().second, mid, h);
            stk.pop();
    }
    int flag=0;
    if(getColor(root)==BLACKn){setcolor(BLACK);flag=1;}
    else setcolor(RED);
    circle(mid,h,radius);
    circle(mid,h,radius+5);
    circle(mid,h,radius+10);
    delay(200);
    setcolor(WHITE);
    circle(mid,h,radius+10);


    if(flag==0) {  bound_fill(mid+10,h+10,RED,RED);bound_fill(mid-10,h-10,RED,RED);}
    else{bound_fill(mid+10,h+10,BLACK,BLACK);bound_fill(mid-10,h-10,BLACK,BLACK);}

    //stk.push(make_pair(mid,h));
    if(root->left!=NULL) stk.push(make_pair(mid,h));
    if(root->right!=NULL) stk.push(make_pair(mid,h));



    setcolor(WHITE);
    outtextxy(mid-5, h-5, itoa(root->data, arr, 10));
    //co_ods.push_back(make_pair(mid,h));

    if(root->left!=NULL){
    delay(500);

    draw(st, mid, h+70, radius,root->left);
    }

    if(root->right!=NULL){
    delay(500);

    draw(mid, en, h+70, radius, root->right);
    }





}



void dda(float xi,float yi,float xf,float yf)
{
   	float x1=xi,x2=xf,y1=yi,y2=yf,x,y;
   	float dx,dy,length;
   	dx=abs(x2-x1);
   	dy=abs(y2-y1);
   	if(dx>=dy)
   		length=dx;
   	else
   		length=dy;
   	dx=(x2-x1)/length;
   	dy=(y2-y1)/length;
   	x=x1;
   	y=y1;
   	for (int i = 0; i <= length; i++)
    {
        putpixel (x,y,RED);
        x += dx;
        y += dy;
    }
}
int sign(float x)
{
	if(x>0)
		return 1;
	else
		return 0;
}
void bres(int x1,int x2,int y1,int y2)
{
    int dx=abs(x2-x1),dy=abs(y2-y1);
    int p=2*dy-dx;
    int x, y, xend;
    if(x1>x2)
    {
        x=x2,y=y2,xend=x1;
    }
    else
    {
        x=x1,y=y1,xend=x2;
    }
    putpixel(x,y,2);
    while(x<xend)
    {
        x++;
        if(p<0)
            p+=2*dy;
        else
            y++;
            p+=2*(dy-dx);
    }
    putpixel(x,y,2);
}
void circl(float r,float x1,float y1)
{
 float d;

  d=3-(2*r);
  float x=0,y=r;

  do
  {
    putpixel(x1+x,y1+y,RED);
    putpixel(x1-x,y1+y,RED);
    putpixel(x1+x,y1-y,RED);
    putpixel(x1-x,y1-y,RED);
    putpixel(x1-y,y1+x,RED);
    putpixel(x1+y,y1-x,RED);
    putpixel(x1-y,y1-x,RED);
    putpixel(x1+y,y1+x,RED);
    //delay(500);
    if(d<0)
    {
      d=d+(4*x)+6;
    }
    else
    {
      d=d+(4*x)-(4*y)+10;
      y=y-1;
    }
    x=x+1;
  }while(x<y);
}
void translation(int x1, int y1, int x2, int y2, int x3, int y3, int tx, int ty) {
		x1 = x1 + tx;
		x2 = x2 + tx;
		x3 = x3 + tx;
		y1 = y1 + ty;
		y2 = y2 + ty;
		y3 = y3 + ty;
		setcolor(RED);
		//printf("TRANSLATION\n");
		line(x1, y1, x2, y2);
		line(x2, y2, x3, y3);
		line(x3, y3, x1, y1);
		getch();
}
void scaling(int x1, int y1, int x2, int y2, int x3, int y3, int Sx, int Sy) {
		x1 = x1 * Sx;
		x2 = x2 * Sx;
		x3 = x3 * Sx;
		y1 = y1 * Sy;
		y2 = y2 * Sy;
		y3 = y3 * Sy;

		setcolor(RED);
		line(x1, y1, x2, y2);
		line(x2, y2, x3, y3);
		line(x3, y3, x1, y1);
		getch();
}





int main() {
    int data;
    RBTree rbTree1, rbTree2;

    data=1;


    //rbTree1.preorder();

    int heightt=800, width=1200, radius=25;
    initwindow(width,heightt);
    outtextxy(390,50,"WECLOME!");

    outtextxy(390,80,"PROJECT TITLE :    VISUALIZATION OF RED BLACK TREES.");
    outtextxy(390,110,"SUBJECT           :    SKILL DEVELOPMENT LAB II");


    outtextxy(390,200,"THIS PROJECT IS MADE BY:");
    outtextxy(390,250,"NEELKAMAL BHARATI");
    outtextxy(390,270,"MOHIT CHARKHA");
    outtextxy(390,290,"CHAITANYA CHAUDHARI");
    outtextxy(390,310,"MAYANK BHALE");
    outtextxy(390,330,"ATHARV BENDE");
    outtextxy(390,360,"UNDER THE GUIDANCE OF PROF. S. R. RATHI");

    outtextxy(390,400,"USING THIS TOOL YOU CAN:");
    outtextxy(390,455,"1. CREATE A RED BLACK TREE");
    outtextxy(390,475,"2. INSERT NEW ELEMENTS");
    outtextxy(390,495,"3. DELETE ELEMENTS");
    outtextxy(390,425,"VISUALIZE THE FOLLOWING PROCESSES ON A RED BLACK TREE");
    outtextxy(390,515,"PLEASE USE CONSOLE FOR INPUT OF THE COMMANDS!");
    system("pause");
    cleardevice();

    rectangle(20,20,1180,780);
    setfillstyle(SOLID_FILL, WHITE);
    floodfill(22,22,WHITE);






    /*rbTree1.draw(0, width, 100, radius, rbTree1.root);
    system("pause");*/

    data=1;
    while (true)
    {
        cout<<"1. Insert value\n2. Delete value\n3. Display Tree\n";
        int choice;
        cin>>choice;
        switch(choice){
        case 1:
            cout<<"Enter value to insert: ";
            cin >> data;
            rbTree1.insertValue(data);
            system("cls");
            break;

        case 2:
            cout<<"Enter data to be deleted:\n";
            cin >> data;
            rbTree1.deleteValue(data);
            system("cls");
            cleardevice();
            rectangle(20,20,1180,780);
            setfillstyle(SOLID_FILL, WHITE);
            floodfill(22,22,WHITE);


        case 3:
            //cleardevice();
            outtextxy( 425,25,"Visualizing Red black tree" );
            rbTree1.draw(0, width, 100, radius, rbTree1.root);
            system("pause");
            system("cls");

        }
    }



    return 0;
}
