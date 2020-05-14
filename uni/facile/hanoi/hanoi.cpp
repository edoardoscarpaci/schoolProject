#include <bits/stdc++.h>
using namespace std;

int c = 1;

void hanoi(int n,int to_print,ostream& out,int a =1,int b=2,int aux=3)
{	
	if(n==0)
	{
		if(c == to_print) {out << a << " " << b <<endl;c++;}
		else c++;
		return; 
	}
	hanoi(n-1,to_print,out,a,aux,b);
	
	if(c == to_print){ out << a << " " <<b <<endl ;c++;}
	else c++;
	
	hanoi(n-1,to_print,out,aux,b,a);
		
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
		int n,m;
		c =1;
		in >>n>>m;
		hanoi(n,m,out);
		
	}
	return 0;
}
