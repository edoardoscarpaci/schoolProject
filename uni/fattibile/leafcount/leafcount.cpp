#include <bits/stdc++.h>
using namespace std;

bool pr =false;
void printArray(int* a,int n){ 
	for(int i=0;i<n;i++) cout << "V["<<i<<"]:"<<a[i]<<" ";
	cout<<endl;
}
template <typename T>
class Stack
{
private:
	T* s; 
	int top; 
	int n;
	int current;

public:
	Stack():top(0),n(100),current(0)
	{
		s= new T[100];
	}
	
	Stack(int len):top(0),n(len),current(0){
		s = new T[n];
	}
	
	
	Stack& push(T key)
	{
		if(top < n)
		{
			s[top++] = key;
		}
		
		return *this;
	}
	
	T* pop()
	{
		if(top > 0)
		{

			T* key = &s[--top];
			return key;
		}
		
		return nullptr;
	}
	
	int size() const { return top; }
	
	
	int isEmpty() const { return top == 0;}
	void reset() {current = top-1;}
	
	int hasNext() const{ return current >= 0 ;}
	
	T* next()
	{
		if(!hasNext()) return nullptr;
		
		T* tmp = &s[current--];
		return tmp;	
	}
	
	void erase()
	{
		top = 0;
	}
	
	
	
	static void CopyTo(Stack<T>&a , Stack<T>&b)
	{
		a.reset();
		while(a.hasNext()) b.push(*a.next());
	}
};




template <typename T>
class Queue{
private:
	Stack<T> s1,s2;
	Stack<T> s3;
	
	void _swap(Stack<T>& a,Stack<T>& b)
	{
		while(!a.isEmpty())
		{
			b.push(*a.pop() );
		}
		
	}
	
public:
	Queue():s3(200){}
	Queue(int n):s1(n),s2(n),s3(n*2){}
	
	
	Queue& enqueue(T key)
	{
		s1.push(key);
		return *this;
	}
	
	T* dequeue()
	{
		if(!s2.isEmpty())
		{
			T* tmp = s2.pop();
			return tmp;
		}
		
		if(!s1.isEmpty())
		{
			_swap(s1,s2);
			T* tmp = s2.pop();
			return tmp;		
		}
		
		return nullptr;
	}
	
	int size(){return s1.size() + s2.size();}
	int isEmpty(){return s1.isEmpty() && s2.isEmpty();}
	
	void reset()
	{	
		s3.erase();
		
		Stack<T> c1 = s1;
		Stack<T> c2 = s2;

		_swap(c2,s3);
		_swap(c1,c2);
		_swap(c2,s3);		
		s3.reset();
	}
	
	int hasNext()
	{
		return s3.hasNext();
	}
	
	T* next() {return s3.next();}
};


template <typename U>
	class Node{
		public:
		U key;
		Node<U>* right;
		Node<U>* left;
		Node<U> *parent;
		Node(U _key){
			key = _key;
			right = left = parent=NULL;
		}
		
		
		int degree(){return (right!=nullptr) + (left!=nullptr);}
	};


template<typename T>
class BST
{
	
private:
	
	Node<T>* _search(T key)
	{
		
		Node<T>* tmp = root;
		
		while(tmp != nullptr && tmp->key != key){
			if(tmp->key > key) tmp = tmp->left;
			else tmp = tmp->right;
		}
		
		return tmp;
	}
	
	void _preorder(ostream& os, Node<T>* x){
		if(x){
			 os<< x->key << " ";
			_preorder(os,x->left);
			_preorder(os,x->right);
		}
	}
	
	void _inorder(ostream& os, Node<T>* x){
		if(x){
			_inorder(os,x->left);
			os<< x->key << " ";
			_inorder(os,x->right);
		}
	}
	
	void _postorder(ostream& os, Node<T>* x){
		if(x){
			_postorder(os,x->left);
			_postorder(os,x->right);
			os<< x->key << " ";
		}
	}
	
	
	Node<T>* _min(Node<T> * node)
	{
		
		if(!node->left) return node;
		return _min(node->left);
	}
	
	Node<T>* _max(Node<T> * node)
	{
		if(!node->right) return node;
		return _max(node->right);
	}
	
	
	Node<T>* _getSuccessor(Node<T>* node){
		
		if(node->right != nullptr){
			return _min(node->right);
		}

		
		Node<T>*tmp = node->parent; 
		while(tmp != nullptr && tmp->key <= node->key)
		{
			tmp = tmp->parent;
		}
		return tmp;
	}
	
	Node<T>* _getPredecessor(Node<T>* node){
		
		
		if(node->left!= nullptr) return _max(node->left);
		
		Node<T>* tmp = node->parent;
		while(tmp != nullptr && tmp->key > node->key)
		{
			tmp = tmp->parent;
		
		}
		return tmp;
	}
	
	
	
	int _rprof(Node<T>* x){
		if(!x) return 0;
		return 1+std::max(_rprof(x->right),_rprof(x->left)); 
		
	}
	
	int _prof(Node<T>* x,T key )
	{
		if(!x) return -1;
		if(x->key == key) return 0;
		if(x->key <= key) return 1 + prof(x->left,key);
		return 1+ _prof(x->right,key);
	}
	
	
	int _leafcount(Node<T>*x){
		if(!x) return 0;
		
		if(!x->right && !x->left) return 1;
		
		int sum=0;
		
		sum += _leafcount(x->right);
		sum += _leafcount(x->left);
		
		return sum;
	}
	
	T _weightCount(Node<T>*x){
		if(!x) return 0;
		if(!x->right && !x->left) return x->key;
		
		
		
		return _weightCount(x->right) + _weightCount(x->left);
	}
private:	
	Node<T>* root;
	int n;
	Node<T>* current;

public:

	BST()
	{
	  n =0;
	  root = nullptr;
	  current = nullptr; 
	}
	
	
	BST& insert(T key)
	{	
		Node<T>* tmp = root;
		Node<T>* x = new Node<T>(key);
		Node<T>* parent = NULL;
		n++;
		
		while(tmp != nullptr){
			parent = tmp;
			if(key <= tmp->key)
				tmp = tmp->left;
			else{
				tmp = tmp->right;
			}
		}
		
		if(!parent){ 
			root = x;
			return *this;
		}
		
		if(key <= parent->key)
			parent->left = x;
		else 
			parent->right = x;
		
		x->parent = parent;
	
		return *this;
	}
	
	
	BST& erase(T key)
	{
		if(pr)
			cout <<*this<<endl;
			
		Node<T>* x = _search(key);
		
		if(x == nullptr) return *this;
		n--;
		
		
		if(x->right != nullptr  && x->left !=nullptr)
		{
			Node<T>* s = _getSuccessor(x);
			
			if(pr)
				cout <<"S:" << s->key <<" D:"<<s->degree()<<endl;
			
			
			x->key = s->key;
			s->key = key;
			
			x = s;
		}
			
		Node<T>* p = x->parent;
		
		
		//if(p && pr) cout << "K_p: "<< p->key <<" D_p: "<< p->degree() <<" K_x: "<< x->key << " D_x:"<<x->degree()<<endl;
	
		
		Node<T>* y = x->left;	
		if(!y) y = x->right;
		
		//if(y && pr) cout << "K_y: "<<y->key<<" D_y: "<<y->degree()<<endl;
		
		if(!y && p){
			if(p->left){
				if(x->key == p->left->key) p->left = nullptr;
				else p->right = nullptr;
			}
			else p->right = nullptr;
		}
		
		else if(p){						
			
			if(y->key <= p->key) p->left = y;
			else p->right = y;	
		}
		
		else root = y;		
		
		if(y){
			if(pr && p)
				cout << p->key <<" "<<y->key<<endl;
			 y->parent = p;
			}
			 
		
		if(pr){
			cout <<*this<<endl<<endl;
		}
		
		return *this;
	}
	
	T* min()
	{
		Node<T>* m = _min(root);
		if( m!= nullptr ) return m->key;
		return nullptr; 
	}
	
	T* max()
	{
		Node<T>* m= _max(root);
		
		if(m!= nullptr ) return m->key;
		return nullptr; 
	}
		 
	int search(T* key)
	{
		return _search(key) != nullptr;
	}
	
	
	
	int getAltezza(T key)
	{
		Node<T>* tmp = _search(key);
		int altezza = 0; 
		
		if(!tmp) return 0;
		tmp = tmp->parent;
		while(tmp){
			tmp = tmp->parent;
			altezza++;
		}
		
		
		return altezza;
	}
	
	int profondita(){return _rprof(root);}
	
	int leafcount(){return _leafcount(root);}
	
	
	T weightCount(T key){
		Node<T> * tmp = _search(key);
		if(!tmp) return T();
		return _weightCount(tmp);
	}
	
	Node<T>* successore(T value) {
		Node<T>*tmp = _search(value);
		if(!tmp) return nullptr;
		
		return _getSuccessor(tmp);
	}
	
	Node<T>* predecessore(T value) {
		Node<T>*tmp = _search(value);
		if(!tmp) return nullptr;
		
		return _getPredecessor(tmp);
	}
	
	
	void preorder(ostream& out) {_preorder(out,root);}
	void inorder(ostream& out) {_inorder(out,root);}
	void postorder(ostream& out) {_postorder(out,root);}	
	
	
	void reset(){
		current = _min(root);
	}
	
	int hasNext(){
		return current != nullptr;
	};
	
	T* next()
	{
		if(hasNext())
		{
			T* tmp = new T(&current->key);
			current = _getSuccessor(current);
			return tmp;
		}
		return nullptr;
	}
};

template<typename T>
ostream& operator<< (ostream& out,const BST<T>& bts)
{
	BST<T> y = bts;
	out << "{";
	y.preorder(out);
	out << "}";
	return out;
}

template<typename T>
ostream& operator<< (ostream& out,const Stack<T>& s)
{
	Stack<T> y = s;
	
	y.reset();
	out << "{ ";
	while(y.hasNext())
	{
		T* e =y.next();
		out << *e<< " "; 
	}
	out << "}";
	
	return out;
}


template<typename T>
ostream& operator<< (ostream& out,const Queue<T>& s)
{
	Queue<T> y = s;
	y.reset();
	out << "{ ";
	

	while(y.hasNext())
	{
		T* e = y.next();
		out << *e<< " "; 
	}
	out << "}";
	
	return out;
}



template<typename T>
void PrintListOrder(ostream& out,string order,BST<T>& bst){
	
	if(order =="preorder")bst.preorder(out);
	else if (order =="postorder")bst.postorder(out);
	else bst.inorder(out);	
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
		string type,tmp;
		int n;
		in>> type>> n;

		
		if(type == "int"){
			BST<int> bst;
			int b = 0;
			for(int i=0;i<n;i++){
				in >> tmp;
				int index = tmp.find(":");
				if(tmp.substr(0,index) == "ins"){					
					bst.insert(stoi(tmp.substr(index+1)));
				}
				
				else{
					bst.erase(stoi(tmp.substr(index+1)));
				}
			}	
			out <<bst.leafcount();
		}
		if(type == "bool"){
			BST<int> bst;
			int b;
			
			for(int i=0;i<n;i++){
				in >> tmp;
				int index = tmp.find(":");
				if(tmp.substr(0,index) == "ins"){					
					bst.insert(stoi(tmp.substr(index+1)));
				}
				
				else{
					bst.erase(stoi(tmp.substr(index+1)));
				}
			}
			out <<bst.leafcount();
		}
		if(type == "double"){
			BST<double> bst;
			double b = 0;
			for(int i=0;i<n;i++){
				in >> tmp;
				int index = tmp.find(":");
				if(tmp.substr(0,index) == "ins"){					
					bst.insert(stod(tmp.substr(index+1)));
				}
				
				else{
					bst.erase(stod(tmp.substr(index+1)));
				}
			}
			out <<bst.leafcount();
		}	
		if(type == "char"){
			BST<char> bst;
			char b;
			for(int i=0;i<n;i++){
				in >> tmp;
				int index = tmp.find(":");
				if(tmp.substr(0,index) == "ins"){					
					bst.insert(tmp[index+1]);
				}
				
				else{
					bst.erase(tmp[index+1]);
				}
			}
			out <<bst.leafcount();
		}
	
	out << endl;
	}				
	
	return 0;

}
