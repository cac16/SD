/***************************************************************
 * Name        : DSFL Assignment - DEPTH FIRST SEARCH          *
 * Author      : NEELKAMAL BHARATI (17U131)                    *
 * Date        : 08-03-2019                                    *
 * Version     : 0.0                                           *
 * Description : DFS using Adjacency Matrix                    *
 * Output      : Below the code                                *
 ***************************************************************/

#include <iostream>
#include <stack>

using namespace std;

class graph{
    int adjMat[20][20], visited[20], i, j, numOfNodes, u;
    stack <int> s;


public:
    graph(int num){
        numOfNodes = num;
        for(i =0; i<numOfNodes; i++){
            for(j=0; j<numOfNodes; j++){
                adjMat[i][j] = 0;
            }
        }
    }

    void addEdge(int p, int q){
        if(p>=numOfNodes || q>=numOfNodes){
            cout<<"Invalid node!\n";
            return;
        }
        adjMat[p][q] = 1;
        adjMat[q][p] = 1;
    }

    void printAdjMat(){
        for(i =0; i<numOfNodes; i++){
            for(j=0; j<numOfNodes; j++){
                cout<<adjMat[i][j]<<' ';
            }
            cout<<endl;
        }
    }
    void setVisited(){
        for(i=0;i<numOfNodes;i++){
            visited[i] = 0;
        }
    }
    void dfs(){


        s.push(0);

        while(!s.empty()){
            u = s.top();
            visited[u]=1;
            cout<<u<<"  ";
            s.pop();
            for(i=0;i<numOfNodes;i++){
                if(adjMat[u][i]==1 && visited[i]!=1){
                    s.push(i);
                    visited[i] = 1;
                }
            }
        }
    }
};

int main()
{
    int choice, n, firstNode, secondNode;
    cout<<"Enter no of nodes in the graph: ";
    cin>>n;
    graph g(n);
    while(true){
        cout<<"\n1. Add Edge \n2. Print Adjacency Matrix \n3. Print DFS\n Enter choice: ";
        cin>>choice;

        switch(choice){
            case 1:
                cout<<"Enter the First vertex: ";
                cin>>firstNode;
                cout<<"Enter the Second vertex: ";
                cin>>secondNode;
                g.addEdge(firstNode, secondNode);
                break;
            case 2:
                g.printAdjMat();
                break;
            case 3:
                g.dfs();
                break;
            default:
                return 0;
        }
    }
}



/**OUTPUT**
Enter no of nodes in the graph: 5

1. Add Edge
2. Print Adjacency Matrix
3. Print DFS
 Enter choice: 1
Enter the First vertex: 0
Enter the Second vertex: 1

1. Add Edge
2. Print Adjacency Matrix
3. Print DFS
 Enter choice: 1
Enter the First vertex: 1
Enter the Second vertex: 3

1. Add Edge
2. Print Adjacency Matrix
3. Print DFS
 Enter choice: 1
Enter the First vertex: 1
Enter the Second vertex: 4

1. Add Edge
2. Print Adjacency Matrix
3. Print DFS
 Enter choice: 1
Enter the First vertex: 0
Enter the Second vertex: 2

1. Add Edge
2. Print Adjacency Matrix
3. Print DFS
 Enter choice: 2
0 1 1 0 0
1 0 0 1 1
1 0 0 0 0
0 1 0 0 0
0 1 0 0 0

1. Add Edge
2. Print Adjacency Matrix
3. Print DFS
 Enter choice: 3
0  2  1  4  3

*/
