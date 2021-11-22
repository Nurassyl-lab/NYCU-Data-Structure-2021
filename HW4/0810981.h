#include <iostream>
#include <queue>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct node{
    int value;
    node *parent, *left, *right;

    node(int val)
    {
        value = val;
        left = NULL;
        right = NULL;
        parent = NULL;
    }
};

int n = 1;//size of BT

struct MaxHeap{
    node* root;

    MaxHeap(){
       	root = NULL;
    }

    bool isEmpty(){
       	if(root == NULL) return true;
       	else return false;
    }

	//locate last parent to add a new node
    node* endParent(){
		queue<node*> tempQ;
		tempQ.push(root);
		node* temp;
		while(!tempQ.empty()){
			temp = tempQ.front();
			tempQ.pop();

			if(temp->left && temp->right){
				tempQ.push(temp->left);
				tempQ.push(temp->right);
			}
			else break;
		}
		//cout<<"Temp = "<<temp->value<<endl;
		return temp;
	}

	//when we insert new node in function "push" from the end of the tree
	//and moving up by level comparing with parents above
	//if no parent above it will become a new root
    void HeapUp(node* temp){
        if(temp->parent == NULL) return;
    	if(temp->parent->value < temp->value){
				//swap current node and its parent
        		swap(temp->parent->value,temp->value);
        		HeapUp(temp->parent);
    	}
	}

	//heap down used to remove node from a tree
	//I explain it more in function "DELETE" below
    void HeapDown(node* head){
        node* largest = head;

        if(head->left && head->left->value > largest->value) largest = head->left;

        if(head->right && head->right->value > largest->value) largest = head->right;

        if(largest != head){
            swap(largest->value,head->value);
            HeapDown(largest);
        }
    }


    void push(int value){
		node* a = new node(value);
		if(root == NULL){//if no root make new node a root
            	root = a;
            	return;
        }

		//will be added to the right of the last parent
        node* rParent = endParent();

        if(rParent->right == NULL){
            	rParent->right = a;
            	a->parent = rParent;
        }
        else{
            	rParent->left = a;
            	a->parent = rParent;
        }
        HeapUp(a);
		n++;
    }

    void inorder (node* head, ofstream& file){
        if(head){
			inorder(head->left, file);
			file<<head->value<<" ";
			inorder(head->right, file);
		}
    }

	void levelorder(node* head, ofstream& file){
		queue<node*> q;
		q.push(head);
		for(int i = 0 ; i < n; i++){
			//cout<<q.front()->value<<" ";
			file<<q.front()->value<<" ";
			if(q.front()->left) q.push(q.front()->left);
			if(q.front()->right) q.push(q.front()->right);
			q.pop();
		}	
	}

	void preorder(node *head, ofstream& file){
		if(head){
			file<<head->value<<" ";
			preorder(head->left, file);
			preorder(head->right, file);
		}
	}

	void postorder(node *head, ofstream& file){
		if(head){
			postorder(head->left, file);
			postorder(head->right, file);
			file<<head->value<<" ";
		}
	}

    void print(int n, ofstream& file){
       	node* temp = root;
       	switch(n){
		case 2:
			levelorder(temp, file);
			file<<"\n";
			break;
		case 3:
			preorder(temp, file);
			file<<"\n";
			break;
		case 4:
			inorder(temp, file);
			file<<"\n";
			break;
		case 5:
			postorder(temp, file);
			file<<"\n";
			break;
		default:
			cout<<"There is no such input format --> "<<n<<endl;
			exit(EXIT_FAILURE);
			break;
		}
       	//cout<<"Output was successfully added to output file!"<<endl; 
    }
    
	//locate end node 
	node* END(){
        	queue<node*> temp;
        	temp.push(root);
        	node* prev;
        	while(!temp.empty()){
            	prev = temp.front();
            	temp.pop();
            	if(prev->left) temp.push(prev->left);
            	if(prev->right) temp.push(prev->right);
        	}
		//cout<<prev->value<<endl;
        return prev;
	}
		
	//To remove an element code swaps the last and top nodes
	//then deletes last element and HeapDown top element
    void DELETE(){
        if(isEmpty()){
            cout<<"Nothing to delete!"<<endl;
           	return;
        }

        node* prev = END();
        
		if(prev == root){
        	delete prev;
        	root = NULL;
      		return;
		}
		//cout<<"swap r = "<<root->value<<" prev = "<<prev->value<<endl; 
       	swap(root->value, prev->value);
        node* pr = prev->parent;

        if(pr->left == prev){
         	delete prev;
          	pr->left = NULL;
        }
        else{
          	delete prev;
      		pr->right = NULL;
        }
        HeapDown(root);
		n--;
    }
};
