#include "0810981.h"

int main(int argc, char* argv[]){
	element access;//since I have created vector of struct 
	//it is not convenient to access the struct functions using vector
	//thats why I have created new element variable "access"
	//I agree that this is a very weird way of solving a problem
	//but I was tired, and I just wanted to finish this HW asap


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

	int a = 0, e = 0;//just to check if this task have appeared in the input file or not
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
			a++;
			istringstream ss(str);//create stringstream variable and assign "str" to it in order to read values
			
			ss>>method>>id>>task;
			element a = {task};
			
			//add "task" to a queue
			access.addQ(queue[id - 1], a, rear[id - 1][0], front[id - 1][0]);
			//queue[id - 1].push_back(a);//add to a queue
			//rear[id - 1][0] += 1;
		}
		else if(execute){
			e++;
			istringstream ss(str);//create stringstream variable and assign "str" to it in order to read values
			ss>>method>>id;
			
			if(rear[id - 1][0] < front[id - 1][0]){
				cout<<"Error! Front value is bigger than Rear value"<<endl;
				exit(0);
			}
			//if processor is being executed but it is empty
			//else if(rear[id - 1][0] == front[id - 1][0]){
			else if(access.isEmpty(rear[id - 1][0],front[id - 1][0])){
				int size = queue[0].size();
				int index = 0;
				int compare = rear[0][0] - front[0][0];
				
				//look for the longhest queue
				//since queue are in ascending order 
				//index will take value of first longest queue 
				//in case if multiple queues have same length
				for(int i = 1; i < numberOfProcessors; i++){
					if(rear[i][0] - front[i][0] > compare){
						compare = rear[i][0] - front[i][0];
						size = queue[i].size();
						index = i;
					}
				}

				if(size == 0){
					cout<<"Error! All queues are free!"<<endl;
					break;
				}
				
				access.addQ(queue[id - 1], element{queue[index][size - 1].t}, rear[id-1][0], front[id-1][0]);
				access.delQ(queue[index], rear[index][0], front[index][0], front[id - 1][0], size);	
			}
			else{//if processor is being executed and it isn't empty
				front[id - 1][0] += 1;
			}
		}
	}
	//output a file
	file.close();
	if(a == 0 && e == 0){
		cout<<"Your input file is wrong!"<<endl;
		return 0;
	}
	write(argv[2], queue, front, rear);
	return 0;
}
