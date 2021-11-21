#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>//TA said that we are allowed to use <string> library
#include <algorithm>
#define MAX 1000000

using namespace std;

struct element{
	char t;

	bool isEmpty(int a, int b){
		if(a == b) return true;
		return false;
	}

	bool isFull(int rear, int front){
		if(rear - front == MAX) return true;
		else if(rear - front > MAX){
			cout<<"Error! Something is wrong and you queue exceeds limit."<<endl;
			exit(0);
		}
		return false;
	}

	void addQ(){
		int a = 1;
	}
	void delQ(){
		int a = 1;
	}

};

//write to a file
void write(string s, vector<vector<element>> v, int front[][1], int rear[][1]){
	ofstream File;
	File.open(s);
	if(!File){
		cout<<"Error! No output File."<<endl;
		exit(0);
	}

	File<<"Queuing\n";
	for(int i = 0; i < v.size(); i++){
		int processor = i + 1;
		File<<processor;
		File<<" ";
		if((rear[i][0] - front[i][0]) > 0){
			for(int j = (front[i][0] + 1); j < rear[i][0] + 1; j++){
				File<<v[i][j].t;
			}
		}
		File<<"\n";
	}	

	File<<"Executed\n";	
	for(int i = 0; i < v.size(); i++){
		int processor = i + 1;
		File<<processor;
		File<<" ";
		for(int j = 0; j <= front[i][0]; j++){
			File<<v[i][j].t;
		}
		File<<"\n";
	}
}

/*void display(vector<vector<element>> v,int front[][1], int rear[][1]){
	cout<<"Queuing"<<endl;
	for(int i = 0; i < v.size(); i++){
		int processor = i + 1;
		cout<<processor<<" ";
		if((rear[i][0] - front[i][0])!=0){
			for(int j = (front[i][0] + 1); j < v.size(); j++){
				cout<<v[i][j].t;
			}
		}
		cout<<endl;
	}	

	cout<<"Executed"<<endl;	
	for(int i = 0; i < v.size(); i++){
		int processor = i + 1;
		cout<<processor<<" ";
		for(int j = 0; j <= front[i][0]; j++){
			cout<<v[i][j].t;
		}
		cout<<endl;
	}
}*/

int main(int argc, char* argv[]){
	//create a file variable and assign a file to it
	ifstream file;
	file.open(argv[1]);
	string str;
	
	int numberOfProcessors;
	//bool numProc = false;

	string method;
	int id;
	char task;

	//get number of processors
	file>>numberOfProcessors;	

	//create 2D vector of elements with a size of number of processors
	vector<vector<element>> queue(numberOfProcessors);
	
	//create array "rear" and "front" to store information of queues
	int front[numberOfProcessors][1];
	int rear[numberOfProcessors][1];

	//set values of each queue to -1
	for(int i = 0; i < numberOfProcessors; i++){
		front[i][0] = -1;
		rear[i][0] = -1;
	}

	//main function loop
	int iterations = 0;
	while(getline(file, str)){
		bool assign = false;
		bool execute = false; 
		bool stop = false;

		//if else statement to determin which action to perform, "assign", "execute" or "stop"
		if(str.find("ASSIGN") != string::npos){
			assign = true;
		}
		else if(str.find("EXEC") != string::npos){
			execute = true;
		}
		else if(str.find("STOP") != string::npos){
			stop = true;
		}


		if(stop) break;//if str has STOP, break "while" loop

		else if(assign){
			istringstream ss(str);//create stringstream variable and assign "str" to it in order to read values
			ss>>method>>id>>task;
			element a = {task};
			queue[id - 1].push_back(a);
			rear[id - 1][0] += 1;
		}
		else if(execute){
			istringstream ss(str);//create stringstream variable and assign "str" to it in order to read values
			ss>>method>>id;
			if(rear[id - 1][0] < front[id - 1][0]){
				cout<<"Error! Front value is bigger than Rear value"<<endl;
				exit(0);
			}
			else if(rear[id - 1][0] == front[id - 1][0]){
				int size = queue[0].size();
				int index = 0;
				int compare = rear[0][0] - front[0][0];
				
				for(int i = 1; i < numberOfProcessors; i++){
					if(rear[i][0] - front[i][0] > compare){
						compare = rear[i][0] - front[i][0];
						size = queue[i].size();
						index = i;
					}
				}

				if(size == -1){
					cout<<"Error! All queues are free!"<<endl;
					break;
				}
				queue[id - 1].push_back(element{queue[index][size - 1].t});
				rear[id - 1][0] += 1;
				queue[index].erase(queue[index].begin() + (size - 1));
				rear[index][0] -= 1;
				front[id - 1][0] += 1;
			}
			else{
				front[id - 1][0] += 1;
			}
		}
	}
	
	//display(queue, front, rear);
	write(argv[2], queue, front, rear);
	return 0;
}
