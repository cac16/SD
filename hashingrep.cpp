/*********************************************************
* AUTHOR    : NEELKAMAL BHARATI                          *
* ROLL NO.  : 221012                                     *
* GR. NO.   : 17U131                                     *
* TITLE     : LP II Submission- Hashing with replacement *
**********************************************************/




#include<bits/stdc++.h>
#include<vector>
#include<utility>
using namespace std;

vector < int >arr, chain;
int n;

void insert(int val, int i=0, int oldi=0){

    if(arr[val%(n-1)+i]==0){
        chain[val%(n-1)+oldi] = val%(n-1)+i;
        arr[val%(n-1)+i]=val;
    }
    else{
        if(val%(n-1)!=arr[val%(n-1)]%(n-1)){
            oldi=i;
            while(arr[val%(n-1)+i]!=0){
                i++;
            }
            insert(arr[val%(n-1)],i,oldi);
            arr[val%(n-1)]=val;

        }

        else if(arr[val%(n-1)]!=0){
            //oldi=i;
            i++;
            insert(val,i,oldi);
        }





    }
}

int main()
{
	cout<<"Enter size of table: ";

	cin>>n;
	for(int j=0;j<n;j++){
        arr.push_back(0);
        chain.push_back(0);
	}
	int val=1;
	while(val!=0){
        cout<<"Enter value / '0' to exit: ";
        cin>>val;
        insert(val);
	}
    cout<<"\nFinal state of table: \n\nIndex Value Chain\n";
	for(int j=0;j<n;j++){
        cout<<j<<"      "<<arr[j]<<"     "<<chain[j]<<endl;
	}


return 0;
}




/************************************
* OUTPUT:                           *
* Enter size of table: 11           *
* Enter value / '0' to exit: 5      *
* Enter value / '0' to exit: 15     *
* Enter value / '0' to exit: 16     *
* Enter value / '0' to exit: 0      *
*                                   *
* Final state of table:             *
*                                   *
* Index Value Chain                 *
* 0      0     0                    *
* 1      0     0                    *
* 2      0     0                    *
* 3      0     0                    *
* 4      0     0                    *
* 5      5     7                    *
* 6      16     0                   *
* 7      15     0                   *
* 8      0     0                    *
* 9      0     0                    *
* 10      0     0                   *
************************************/
