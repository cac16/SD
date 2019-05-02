#include<bits/stdc++.h>
#define rep(i,x,y) for(int i=x; i<y; i++)
using namespace std;


int arr[1000];

void heapify(int n){
    for(int i = (n/2)-1;i>=0; i--){

        int maxn = i;
        int leftChild = 2*i+1;
        int rightChild = 2*i+2;


        if(arr[leftChild]>arr[maxn]){
            maxn = leftChild;
        }

        if(arr[rightChild]>arr[maxn]){
            maxn = rightChild;
        }

        if(i!=maxn){
            int temp = arr[i];
            arr[i] = arr[maxn];
            arr[maxn] = temp;
        }
    }
}

void heapsort(int n)
{
    for(int i=n-1;i>0;i--){
            int temp = arr[i];
            arr[i] = arr[0];
            arr[0] = temp;
             rep(i,0,n){
        cout<<arr[i]<<' ';
	}cout<<endl;

            heapify(i-1);
             rep(i,0,n){
        cout<<arr[i]<<' ';
	}cout<<endl<<endl;
    }
}


int main()
{
	ios_base::sync_with_stdio(false);

	//Accept n, no. of elements
	cout<<"Enter the no. of elements: ";
	int n;
	cin>>n;

    //Accept array
    cout<<"Enter Elements:\n";
	for(int k=0;k<n;k++){
        cin>>arr[k];
	}

    //BUILD-HEAP
	for(int k=1;k<=n/2;k++){
            heapify(n);



    }
     rep(i,0,n){
        cout<<arr[i]<<' ';
	}cout<<endl;

    //HEAPSORT
	heapsort(n);

	//Print sorted array
	cout<<"Sorted array: \n";
	 rep(i,0,n){
        cout<<arr[i]<<' ';
	}cout<<endl;


return 0;
}
