#include <iostream>
#define MAX 99999
using namespace std;

class graph
{
    //int arr[20][20], numOfVertices, i, j;

public:
    int arr[20][20], numOfVertices, i, j;
    void create(){
        char choice;
        cout<<"Enter no. cities: ";
        cin>>numOfVertices;

        for(i=0;i<numOfVertices;i++){
            for(j=0;j<numOfVertices;j++){
                arr[i][j]=0;
            }
        }

        choice = 'y';
        while(choice!='n'){
            cout<<"Enter 1st city: ";
            cin>>i;
            cout<<"Enter 2nd city: ";
            cin>>j;
            cout<<"Enter distance: ";
            cin>>arr[i][j];
            arr[j][i]=arr[i][j];
            cout<<"do you want to add more edges (y/n): ";
            cin>>choice;

        }
    }

    void showMatrix(){
        for(i=0;i<numOfVertices;i++){
            for(j=0;j<numOfVertices;j++){
                cout<<arr[i][j]<<' ';
            }
            cout<<'\n';
        }
    }



    void dijkstra(int numOfVertices1)
    {
        int visited[numOfVertices1], parent[numOfVertices1], key[numOfVertices1], u;
 int k;
       for(i=0;i<numOfVertices1;i++){
            visited[i]=0;
            key[i]=MAX;
        }

        key[0] = 0;

        for(i=0;i<numOfVertices1-1;i++){
            u = minkey(visited, key, numOfVertices1);
                cout<<"minkey "<<u<<endl;
           visited[u]=1;




           for(j=0;j<numOfVertices1;j++){
                if(arr[u][j]!=0 && visited[j]==0 && arr[u][j]+key[u]<key[j]){
                    key[j] = arr[u][j]+key[u];
                    parent[j] = u;
                }
           }

        }


        for(k=1;k<numOfVertices1;k++){
            cout<<parent[k]<<" - "<<k<<" "<<key[k]<<endl;
        }
        cout<<endl<<endl;
        k=numOfVertices1-1;
        cout<<"Min distance: "<<key[k]<<endl;
        cout<<"Shortest path: ";
        while(true){


            cout<<' '<<k<<' ';
            k = parent[k];
            if(k==0){cout<<" 0 "<<endl; return;}
        }

        //cout<<numOfVertices<<' '<<key[k];

    }



    int minkey(int visited[], int key[], int numOfVertices1){
        int mi = MAX;
        int idx;
        int e;
        for(e=0;e<numOfVertices1;e++){
            if(visited[e]==0 && key[e]<mi){
                mi = key[e];
                idx = e;
            }
        }
        return idx;
    }


};
int main()
{
    graph g;
    int choice;

    g.create();
    while(true){

        cout<<"1. Show matrix.\n2. Dijkstra's\nEnter Choice: ";
        cin>>choice;
        switch(choice){
            case 1: g.showMatrix();
                    break;

            case 2:

                g.dijkstra(g.numOfVertices);
                    break;
            default:return 0;
        }
    }
}
