#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

struct node{
	int term;
	float coef;
	int x_exp;
	int y_exp;
	int z_exp;

	node* link;
};

//this function can be used to print polynomial
//just if you want to print it in terminal
void show(struct node* ptr){
	cout<<"Number of terms "<<ptr->term<<endl;
	while(ptr != NULL){
		cout<<ptr->coef;
		cout<<"x^"<<ptr->x_exp;
		cout<<"y^"<<ptr->y_exp;
		if(ptr->link != NULL) cout<<"z^"<<ptr->z_exp<<" + ";
		else  cout<<"z^"<<ptr->z_exp;	
		ptr = ptr->link;
	}
	cout<<"\n================="<<endl;
}



node* createNode(vector<int> vec, node* NODE){
	NODE->coef = vec[0];
	NODE->x_exp = vec[1];
	NODE->y_exp = vec[2];
	NODE->z_exp = vec[3];

	return NODE;
}

//attach to the back
void attach(float c, int x_e, int y_e, int z_e, node** ptr){
	node* temp;
	temp = (node*)malloc(sizeof(*temp));
	temp->coef = c;
	temp->x_exp = x_e;
	temp->y_exp = y_e;
	temp->z_exp = z_e;
	(*ptr)->link = temp;
	*ptr = temp;
}


//this function is completely useless
//the only reason why I did not remove it is because if I remove this function
//I would need to change my super messy code
//and to avoid mistakes I decided to keep this function
void erase(node** a, node** b, node* pA, node* pB){
	node* tempA;
	node* tempB;
		
	node* trash;

	if(pA != NULL && pB != NULL){
		tempA = (*a)->link;
		tempB = (*b)->link;

		*a = pA;
		*b = pB;

		(*a)->link = tempA;	
		(*b)->link = tempB;
	}
	else if(pA ==  NULL && pB != NULL){
		tempB = (*b)->link;
		*b = pB;
		*a = (*a)->link;
		(*b)->link = tempB;
	}
	else if(pA != NULL && pB == NULL){
		tempA = (*a)->link;
		*a = pA;
		(*a)->link = tempA;
		*b = (*b)->link;
	}
}


void deleteNode(node **head_ref, int position)
{
    if (*head_ref == NULL)
        return;

    node* temp = *head_ref;

    if (position == 0)
    {
        *head_ref = temp->link; 
        free(temp);             
        return;
    }
  
    for(int i = 0; temp != NULL && i < position - 1; i++)
        temp = temp->link;
  
    if (temp == NULL || temp->link == NULL)
        return;
  
    node *link = temp->link->link;
    free(temp->link); 
    temp->link = link; 
}

//reduce polynomial after multiplication
void rDup(node* start)
{
    node *ptr1, *ptr2, *dup;
    ptr1 = start;
 
    while (ptr1 != NULL && ptr1->link != NULL) {
        ptr2 = ptr1;
 
        while (ptr2->link != NULL) {
            if (ptr1->x_exp == ptr2->link->x_exp && ptr1->y_exp == ptr2->link->y_exp && ptr1->z_exp == ptr2->link->z_exp) {
 		start->term-=1;
                ptr1->coef = ptr1->coef + ptr2->link->coef;
                dup = ptr2->link;
                ptr2->link = ptr2->link->link;
                delete (dup);
            }
            else
                ptr2 = ptr2->link;
        }
        ptr1 = ptr1->link;
    }
}

//addition
node* addNodes(node* a, node *b){
	//the code is very messy
	//I did not clean and structurize the code because I wanted to avoid mistakes
	//since it is linked list,and my small brain can't visualize things properly
	//you may see a lot of nonsense declarations such as flags and etc
	//maybe I could use my "rDup" function to reduce length of "addNode" and "subNode" functions
	//but I'm already overdue by 2 days, and I dont want to edit this code anymore

		
	int aT = a->term;
	int bT = b->term;
	
	//exchange two polynomials
	node* zalupa = a;
	if(aT < bT){
		a = b;
		b = zalupa;
	}
	//heads
	node* ha = a;
	node* hb = b;
	//head to rear
	node* c;

	node* prevA = NULL;
	node* prevB = NULL;

	node* temp;

	node* rear;
	float sum;
	rear = NULL;
	rear = (node*)malloc(sizeof(node));
	c = rear;
	c->term = 0;
	bool first = true;
	while(a != NULL){
		while(b != NULL && a != NULL){
			//flag is to access "b = b->link" at a specific time
			bool flag = false;

			//if powers are same sum up terms
			if(a->x_exp == b->x_exp && a->y_exp == b->y_exp && a->z_exp == b->z_exp){
				sum = a->coef + b->coef;
				if(sum != 0) {
					//attach to back of rear
					if(!first)attach(sum, a->x_exp, a->y_exp, a->z_exp, &rear);
					else{
						rear->coef = sum;
						rear->x_exp = a->x_exp;
						rear->y_exp = a->y_exp;
						rear->z_exp = a->z_exp;
						first = false;
					}
					c->term += 1;
				}
				if(prevA != NULL && prevB != NULL) erase(&a, &b, prevA, prevB);//useless line
				else{
					flag = true;
					a = a->link;
					b = b->link;
				}
			}	
			prevB = b;
			if(!flag){
				b = b->link;
				flag = false;
			}
		}
		b = hb;
		prevB = NULL;
		prevA = a;
		a = a->link;
	}
	a = ha;
	b = hb;


	int size = c->term;
	//attach a and b to rear back
	//rear is a reasult of sum of a and b
	while(a != NULL || b != NULL){
		if(a != NULL){
			attach(a->coef, a->x_exp, a->y_exp, a->z_exp, &rear);
			a = a->link;
			c->term += 1;
		}
		if(b != NULL){
			attach(b->coef, b->x_exp, b->y_exp, b->z_exp, &rear);
			b = b->link;
			c->term += 1;
		}
	}
		
	vector<int> key;
	node* head;
	temp = NULL;
	head = c;

	node* temp1 = head;
	node* temp2 = head;
	int k = 1;
	int n = c->term;

	//since first values of rear is a sum of a and b: rear[0: size]
	//after rear[size] values of rear are values of a and b
	//so we can reduce rear[size:end] if term is same as terms from rear[0:size]
	//
	//
	//here I get keys(index) from polynomial
	for(int i = 0; i < size; i++){
		temp2 = temp1->link;
		for(int j = k; j < n; j++){
			if(temp1->x_exp == temp2->x_exp && temp1->y_exp == temp2->y_exp && temp1->z_exp == temp2->z_exp){
				key.push_back(j);	
			}
			temp2 = temp2->link;
		}
		k++;
		temp1 = temp1->link;
	}
	//sort vector of keys
	sort(key.begin(), key.end());

	//delete duplicates
	for(int i = 0; i < key.size(); i++){
		key[i] = key[i] - i;
		deleteNode(&head, key[i]);
		head->term -= 1;
	}
	//cout<<"after"<<endl;
	//show(head);
	return head;
}

node* getNegative(node* a){
	node* head;
	head = a;
	while(a != NULL){
		a->coef *= -1;
		a= a->link;
	}
	a = head;
	return a;
}

node* subNodes(node* a, node *b){
	int aT = a->term;
	int bT = b->term;

	node* zalupa = a;

	//echange polynomials
	if(aT < bT){
		a = b;
		b = zalupa;
		a = getNegative(a);//make it negative to get proper subtraction later on(since there is no subration, only sum) ;) 
	}
	
	/*
	 
	The rest is same as "addNode" function

	*/

	node* ha = a;
	node* hb = b;

	node* c;

	node* prevA = NULL;
	node* prevB = NULL;

	node* temp;

	node* rear;
	float sum;
	rear = NULL;
	rear = (node*)malloc(sizeof(node));
	c = rear;
	c->term = 0;
	bool first = true;
	while(a != NULL){
		while(b != NULL && a != NULL){
			bool flag = false;
			if(a->x_exp == b->x_exp && a->y_exp == b->y_exp && a->z_exp == b->z_exp){
				if(aT < bT) sum = a->coef + b->coef;
				else sum = a->coef - b->coef;
				if(sum != 0) {
					if(!first)attach(sum, a->x_exp, a->y_exp, a->z_exp, &rear);
					else{
						rear->coef = sum;
						rear->x_exp = a->x_exp;
						rear->y_exp = a->y_exp;
						rear->z_exp = a->z_exp;
						first = false;
					}
					c->term += 1;
				}
				if(prevA != NULL && prevB != NULL) erase(&a, &b, prevA, prevB);//useless line, I did not want to erase this line because I would need to rewrite the code. And the code is so messy that any change can affect it. And I'm tired!
				else{
					flag = true;
					a = a->link;
					b = b->link;
				}
			}	
			prevB = b;
			if(!flag){
				b = b->link;
				flag = false;
			}
		}
		b = hb;
		prevB = NULL;
		prevA = a;
		a = a->link;
	}
	 
	a = ha;
	b = hb;
	zalupa = b;

	if(aT < bT){
		b = a;
		a = zalupa;
		b = getNegative(b);
	}

	ha = a;
	hb = b;

	a = ha;
	b = hb;


	int size = c->term;
	while(a != NULL || b != NULL){
		if(a != NULL){
			attach(a->coef, a->x_exp, a->y_exp, a->z_exp, &rear);
			a = a->link;
			c->term += 1;
		}
		if(b != NULL){
			attach(b->coef, b->x_exp, b->y_exp, b->z_exp, &rear);
			b = b->link;
			c->term += 1;
		}
	}

	vector<int> key;
	node* head;
	temp = NULL;
	head = c;

	node* temp1 = head;
	node* temp2 = head;
	int k = 1;
	int n = c->term;
	for(int i = 0; i < size; i++){
		temp2 = temp1->link;
		for(int j = k; j < n; j++){
			if(temp1->x_exp == temp2->x_exp && temp1->y_exp == temp2->y_exp && temp1->z_exp == temp2->z_exp){
				key.push_back(j);	
			}
			temp2 = temp2->link;
		}
		k++;
		temp1 = temp1->link;
	}
	sort(key.begin(), key.end());
	for(int i = 0; i < key.size(); i++){
		key[i] = key[i] - i;
		deleteNode(&head, key[i]);
		head->term -= 1;
	}
	return head;
}

node* mult(node* a, node* b){
	node* ha = a;
	node* hb = b;
	
	node* c;	
	node* rear;
	rear = (node*)malloc(sizeof(node));
	c = rear;
	c->term = 0;
	int aT = a->term;
	int bT = b->term;


	float product;
	for(int i = 0; i < aT; i++){
		for(int j = 0; j < bT; j++){
			if(i == 0 && j == 0){
				//cout<<"rear->coef";
				rear->coef = a->coef * b->coef;
				//cout<<rear->coef<<" = "<<a->coef<<" * "<<b->coef<<endl;
				if(a->x_exp != 0 && b->x_exp != 0)rear->x_exp = a->x_exp + b->x_exp;
				else if(a->x_exp != 0 && b->x_exp == 0) rear->x_exp = a->x_exp;
				else if(a->x_exp == 0 && b->x_exp != 0) rear->x_exp = b->x_exp;
				else rear->x_exp = 0;

				if(a->y_exp != 0 && b->y_exp != 0)rear->y_exp = a->y_exp + b->y_exp;
				else if(a->y_exp != 0 && b->y_exp == 0) rear->y_exp = a->y_exp;
				else if(a->y_exp == 0 && b->y_exp != 0) rear->y_exp = b->y_exp;
				else rear->y_exp = 0;

				if(a->z_exp != 0 && b->z_exp != 0)rear->z_exp = a->z_exp + b->z_exp;
				else if(a->z_exp != 0 && b->z_exp == 0) rear->z_exp = a->z_exp;
				else if(a->z_exp == 0 && b->z_exp != 0) rear->z_exp = b->z_exp;
				else rear->z_exp = 0;
			}
			else{
				int c = a->coef * b->coef;
				int x, y, z;

				if(a->x_exp != 0 && b->x_exp != 0) x = a->x_exp + b->x_exp;
				else if(a->x_exp != 0 && b->x_exp == 0) x = a->x_exp;
				else if(a->x_exp == 0 && b->x_exp != 0) x = b->x_exp;
				else x = 0;

				if(a->y_exp != 0 && b->y_exp != 0) y = a->y_exp + b->y_exp;
				else if(a->y_exp != 0 && b->y_exp == 0) y = a->y_exp;
				else if(a->y_exp == 0 && b->y_exp != 0) y = b->y_exp;
				else y = 0;

				if(a->z_exp != 0 && b->z_exp != 0) z = a->z_exp + b->z_exp;
				else if(a->z_exp != 0 && b->z_exp == 0) z = a->z_exp;
				else if(a->z_exp == 0 && b->z_exp != 0) z = b->z_exp;
				else z = 0;

				attach(c, x, y, z, &rear);
			}
			b = b->link;
			c->term += 1;
		}
		b = hb;
		a = a->link;
	}
	//reduce duplicates
	rDup(c);
	return c;
}
