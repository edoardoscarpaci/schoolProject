#include <bits/stdc++.h>
using namespace std;

void printArray(int* a,int n){ for(int i=0;i<n;i++) cout << "V["<<i<<"]:"<<a[i]<<" ";cout<<endl; }
void merge(int* a,int n,int m)
{
	
	int b[n];
	int j=m;
	int i=0;
	int k = 0;
	while(i<m&& j<n)
	{
		if(a[i] <= a[j]) 
		{
			b[k++] = a[i++]; 
		}
		else
		{
			b[k++] = a[j++];
		}
	}
	while(i<m) b[k++] = a[i++];
	while(j<n) b[k++] = a[j++];
	
	for(i=0;i<n;i++)
	{
		a[i] = b[i];
	}
};

int mergesort (int* a, int n)
{
	//printArray(a,n);
	int tmp = 0;
	
	if(n<=1) return 0;
	if(n==2) return a[0];
	
	int m = (n/2)+ n%2;

	tmp+=a[0];
	tmp+= mergesort(a,m);
	tmp+= mergesort(a+m,n-m);
		
	merge(a,n,m);	
	return tmp;
}



int main(){
	ifstream in("input.txt");
	ofstream out("output.txt");
	
	
	if(!in.is_open() && !out.is_open()) {
		cerr <<"Non è stato possibile aprire il file di input o output"<<endl;
		return 1;
	}
	
	
	for(int l=0;l<100;l++)
	{
		int n;
		in >>n;
		int a[n];
		
		for(int i=0;i<n;i++) in >> a[i];
		out <<mergesort(a,n)<<endl;
		
	}
	return 0;
}
