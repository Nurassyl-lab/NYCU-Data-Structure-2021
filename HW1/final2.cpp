#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

void compareMatrix(vector<vector<int>> A, vector<vector<int>> B){
	if(A.at(0).size() != B.size()){
		cout<<"Number of columns in matrix A is not equal to number of rows in matrix B"<<endl;
		cout<<"The multiplication of matrix A and matrix B cannot be done!"<<endl;
		exit(0);
	}
}

vector<vector<int>> transpose(vector<vector<int>> matrix){
	int rows = matrix.size();
	int cols = matrix.at(0).size();
	vector<vector<int>> temp(cols, vector<int>(rows));
	for(int i =0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			temp[j][i] = matrix[i][j];
		}
	}
	return temp;
}

vector<vector<int>> mult(vector<vector<int>> A, vector<vector<int>> B){
	compareMatrix(A, B);
	vector<vector<int>> temp(A.size(), vector<int>(B.at(0).size()));

	for (int i = 0; i < A.size(); i++) {	
        	for (int j = 0; j < B.at(0).size(); j++) {
            		temp[i][j] = 0; 
            		for (int k = 0; k < B.size(); k++) {
                		temp[i][j] += A[i][k] * B[k][j];
            		}
        	}	
        }
	return temp;
}

int main(int argc, char* argv[]){
	ifstream File;
	File.open(argv[1]);
	ofstream wFile(argv[2]);
	string x;
        string s; 
	string comp = " ;AB";
	
	vector<string> a;
	vector<string> b;

	bool flagA = true;
	bool flagB = false;
	
	int i = 0;
	while(getline(File, s)){
		if(s[0] == comp[3]){
			flagA = false;
			flagB = true;
		}
		if(s[0] != comp[2] && s[0] != comp[3]){
			if(flagA )
				a.push_back(s);
			if(flagB)
				b.push_back(s);
		}
	}

	/*
	cout<<"Matrix A"<<endl;
	for(int i = 0; i < a.size(); i++){
			cout<<a.at(i);
			cout<<endl;
	}
	cout<<"\nMatrix B"<<endl;
	for(int i = 0; i < b.size(); i++){
			cout<<b.at(i);
			cout<<endl;
	}*/

	cout<<endl;
	vector<vector<int>> matrixA;
	vector<vector<int>> matrixB;
	
	int M;

	if(a.size()<2 || b.size()<2){
		cout<<"Matrices are empty!";
		exit(0);
	}

	//Matrix A
	for(int i = 0; i < a.size();i++){
		matrixA.push_back(vector<int>());
		stringstream ss (a.at(i));
		while(ss >> M){
			matrixA.at(i).push_back(M);
		}
	}

	//Matrix B
	for(int i = 0; i < b.size();i++){
		matrixB.push_back(vector<int>());
		stringstream ss (b.at(i));
		while(ss >> M){
			matrixB.at(i).push_back(M);
		}
	}

	cout<<"\nOutput from integer matrix: "<<endl;
	/*
	cout<<"Matrix A: "<<endl;
	for(int i = 0; i < matrixA.size(); i++){
		for(int j = 0; j < matrixA.at(i).size(); j++){
			cout<<matrixA.at(i).at(j)<<" ";
		}
		cout<<endl;
	}
	cout<<"\nMatrix B: "<<endl;
	for(int i = 0; i < matrixB.size(); i++){
		for(int j = 0; j < matrixB.at(i).size(); j++){
			cout<<matrixB.at(i).at(j)<<" ";
		}
		cout<<endl;
	}
	*/
	int m = matrixA.size();
	int n = matrixA.at(0).size();
        int p = matrixB.size();
	int q = matrixB.at(0).size();	

	/*if(matrixA.size() <  1 || matrixB.size() < 1) {
		cerr<<"Error!"<<endl;
		exit(0);
	}
	else{
		cout<<"n = "<<n<<" m = "<<m<<endl;
		cout<<"p = "<<p<<" q = "<<q<<endl;
	}*/
	File.close();
//reading from file
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//computating
	vector<vector<int>> matrixC;

	if(n == p){
		cout<<"case 1"<<endl;
		matrixC = mult(matrixA, matrixB);
	}
	else if(m == p){
		cout<<"case 2"<<endl;
		matrixA = transpose(matrixA);
		matrixC = mult(matrixA, matrixB);
		/*for(int i = 0; i < matrixC.size(); i++){
			for(int j = 0; j < matrixC.at(i).size(); j++){
				cout<<matrixC.at(i).at(j)<<" ";
			}
			cout<<endl;
		}*/

	}
	else if(n == q){
		cout<<"case 3"<<endl;
		matrixB = transpose(matrixB);
		matrixC = mult(matrixA, matrixB);	
	}
	else if(m == q){
		cout<<"case 4"<<endl;
		matrixA = transpose(matrixA);
		matrixB = transpose(matrixB);
		matrixC = mult(matrixA, matrixB);
	}	
	if(wFile.is_open()){
		for(int i = 0; i < matrixC.size(); i++){
			for(int j = 0; j < matrixC.at(0).size(); j++){
				wFile<<matrixC[i][j]<<" ";
			}
			wFile<<";\n";
		}
	}
	else cout<<"Can't open file!"<<endl;
	wFile.close();
}
