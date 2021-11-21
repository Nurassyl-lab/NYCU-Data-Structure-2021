#include "0810981.h"

int main(int argc, char* argv[]){
	vector<node*> head;
	node* pols = NULL;
	ifstream file;
	file.open(argv[1]);
	string str;
	int polNum = -1;

	while(getline(file, str)){
		istringstream ss(str);
		int task;
		ss>>task;
		switch(task){
			case 0:{
//				cout<<"ADDED POLYNOMIAL!"<<endl;
				polNum += 1;
				int c, x, y, z;
				int T;
				ss>>T;
				
				pols = (node*)malloc(sizeof(node));
				head.push_back(pols);
				for(int i = 0; i < T; i++){
					getline(file, str);
					istringstream ss(str);
					ss>>c>>x>>y>>z;
					pols = createNode({c,x,y,z}, pols);
					if(i < T - 1) pols->link = (node*)malloc(sizeof(node));
					else pols->link = NULL;
					pols = pols->link;
					head[polNum]->term = i + 1;
				}
				//uncomment if you want to see what polynomial was added
//				show(head[polNum]);
				break;
			       }
			case 1:{
//				cout<<"SUM OF TWO POLYS"<<endl;
				int a, b;
				ss>>a>>b;
				node* result = addNodes(head[a], head[b]);
				head.push_back(result);
				break;
			       }
			case 2:{
//				cout<<"SUBTRACT TWO POLYS"<<endl;
				int a, b;
				ss>>a>>b;
				node* result = subNodes(head[a], head[b]);
				head.push_back(result);
				break;
			       }
			case 3:{
//				cout<<"Multiplication"<<endl;
				int a, b;
				ss>>a>>b;
				node* result = mult(head[a], head[b]);
				head.push_back(result);
				break;
			       }
			case 4:{
//				cout<<"DELETE POLY"<<endl;
				int d;
				ss>>d;	
				head.erase(head.begin() + d);
				break;
			       }
		}
	}

	//uncoment if you want to printout each poltnomial
	
	/*for(int i = 0; i < head.size(); i++){
		show(head[i]);
	}*/

	file.close();
	ofstream f;
	f.open(argv[2]);

	for(int i = 0; i < head.size(); i++){
		f<<head[i]->term<<"\n";
		while(head[i] != NULL){
                	f<<head[i]->coef<<" ";

                	f<<head[i]->x_exp<<" ";

                	f<<head[i]->y_exp<<" ";

          	      	f<<head[i]->z_exp<<"\n";

                 	head[i] = head[i]->link;
        	}	
	}
}
