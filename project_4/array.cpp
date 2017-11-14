#include <iostream>
#include <string>
#include <cassert>

using namespace std;

int appendToAll(string a[], int n, string value){
	if (n<0)
		return -1;        //nothing special for n=0 here
	for(int k=0; k<n; k++)
		a[k]+=value;
	return n;
}

int lookup(const string a[], int n, string target){
	if (n<0)
		return -1;
	for(int k=0; k<n;k++){
		if(a[k]==target)
			return k;     //returns position of the first target it finds
	}
	return -1;
}

int positionOfMax(const string a[], int n){
	if (n<=0)
		return -1;
	int maxPosition = 0;
	for(int k=0;k<n;k++)
		if(a[k]>a[maxPosition])  //replaces maxPosition if the curent string is bigger
			maxPosition = k;     
	return maxPosition;
}

int rotateLeft(string a[], int n, int pos){
	if (n<=0)
		return -1;
	if (pos<0 || pos>=n)
		return -1;
	string posCopy = a[pos]; //copy of the value at pos before it is deleted
	for(int k = pos;k<n-1;k++)
		a[k]= a[k+1];
	a[n-1]=posCopy;           //puts the deleted value into the last space of the array
	return pos;
}

int rotateRight(string a[], int n, int pos){
	if (n<=0)
		return -1;
	if (pos<0 || pos>=n)
		return -1;
	string posCopy = a[pos];//copy of the position before it is deleted
	for(int k=pos;k>0;k--)
		a[k]=a[k-1];
	a[0]=posCopy;          //puts the deleted position in the first space of array
	return pos;

}

int flip(string a[], int n){
	if (n<0)
		return -1;
	if (n==0)                    //since flip does nothing in this case, return n
		return 0;
	string copyZero = a[0];      //makes a copy of first element
	for(int k=0; k<n-1; k++){
		a[k]=a[n-1];
		for(int i=n-1;i!=k;i--)
			a[i]=a[i-1];
	}
	a[n-1]=copyZero;   //places copy in the last space
	return n;
}

int differ(const string a1[], int n1, const string a2[], int n2){
	if (n1<0 || n2<0)
		return -1;
	for(int k=0; k<n1 && k<n2;)
		if(a1[k]==a2[k])       //counts until there is a difference
			k++;
		else 
			return k;         //returns the differing position
	if(n1>n2)        //if one of the arrays runs out 
		return n2;
	else
		return n1;
}

int subsequence(const string a1[], int n1, const string a2[], int n2){
	if (n1<0 || n2<0)
		return -1;
	int position;
	int f;
	for(int k =0; k<n1; k++){
		f=0;                      //allows a2 to repeatedly be checked
		if(a1[k]==a2[f] && n2==1) //if it is a one element array
			return k;
		if(a1[k]==a2[f]){
			position = k;         //saves the position of the first element that is the same, to return later
			for(;f<n2&&k<n1;f++){
				if(a1[k]==a2[f]){
					if(a1[k]==a2[n2-1])
						return position;
					k++;
				}
				else             //breaks the second loop, and starts over checking for the sequence
					break;
			}
		}
	}
	return -1;
}
int lookupAny(const string a1[], int n1, const string a2[], int n2){
	if (n1<0 || n2<0)
		return -1;
	for(int a1pos=0;a1pos<n1;a1pos++){
	for(int a2pos=0;a2pos<n2;a2pos++) //compares all elements of the second array with the element of the first array before incrementing the first arrays position
		if(a1[a1pos]==a2[a2pos])
			return a1pos;             //returns the position of the first matchup
	}
	return -1;
}

int partition(string a[], int n, string separator){
	if (n<=0)
		return -1;
	int count = 0; 
	int countseparate= 0;
	for(int c = 0; c < n; c++) //counts the number of elements less than separator to return later
		if(a[c] < separator)
			count ++;
	for(int k = 0; k!=count;)
		if(a[k]>separator||a[k]==separator)
			rotateLeft(a,n,k);           //uses rotateleft to rearrange the array
		else if (a[k]<separator)
			k++;
	for(int b = 0; b<n; b++)   //counts the number of elements equal to separator
		if (a[b]==separator)
			countseparate++;
	for(int j = count; j!=count+countseparate;) //puts separator between the elements less than and greater than it
		if(a[j]>separator)
			rotateLeft(a,n,j);
		else if (a[j]==separator)
			j++;
	return count; //since separator is an element that is not < separator
}


int main(){
	
string bs[4] ={"b","b","b","b"};
assert(partition(letters, -1, "b") == -1);// n is negative
assert(partition(letters, 7, "b") == 3);//normal inputs and separator equals elements
assert(partition(letters, 0, "b") == -1);//n is 0
assert(partition(bs,4,"c")==4);//all elements less than separator
assert(partition(bs,4,"a")==0);//all elements are greater or equal to separator

}