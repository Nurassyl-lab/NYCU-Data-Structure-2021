#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

//define structure fro matrices
typedef struct{
	int row, col, val;
}term;

//define function os FAST matrix transpose
vector<term> transpose(vector<term> a, vector<term> b){
	vector<int> rowTerms;
	vector<int> startingPos;
	int i, j, numCols = a[0].col, numTerms = a[0].val;
	b.push_back(term{numCols, a[0].row, numTerms});
	if(numTerms > 0){
		for(i = 0; i < numCols; i++)
			rowTerms.push_back(0);
		for(i = 0; i <= numTerms; i++)
			rowTerms[a[i].col]++;
		startingPos.push_back(1);
		for(i = 1; i < numCols; i++)
			startingPos.push_back(startingPos[i - 1] + rowTerms[i-1]);
		for(i = 1; i <= numTerms; i++){
			j = startingPos[a[i].col]++;
			b.push_back(term{a[i].col, a[i].row, a[i].val});
		}
	}
	else{return a;}
	return b;
}

//define function to update matrix 'd' which is being used in function mult
vector<term> storeSum(vector<term> d, int *totalD, int row, int column, int *sum){
	if(*sum){
		d.push_back(term{row, column, *sum});
		++*totalD;
	}
	return d;
}

//define function that sum ups values on the same row and column
//used in function mult
vector<term> sumRows(vector<term> d, int Dval){
	for(int i = 1; i < Dval + 1; i++){
		for(int j = i + 1; j < Dval + 1; j++){
			if(d[i].row == d[j].row){
				if(d[i].col == d[j].col){
				//	cout<<d[i].val<<" + "<<d[j].val<<" = "<<d[i].val+d[j].val<<endl;
					d[i].val += d[j].val;
					d.erase(d.begin() + j);
					Dval--;
					j--;
				}
			}
		}
	}
	d[0].val = Dval;
	return d;

}

//define function of matrix multiplication
//takes two matrices as input and transposes matrix b
//and performs multiplication
vector<term> mult2(vector<term> a, vector<term> b){
	int Acol = a[0].col, Arow = a[0].row, Aval = a[0].val;
	int Bcol = b[0].col, Brow = b[0].row, Bval = b[0].val;
	int Dcol = 0, Drow = 0, Dval = 0;
	int s = 0;
	vector<term> d;
	d.push_back(term{Arow, Bcol, Dval});

	vector<term> newB;
	newB = transpose(b, newB);
	
	for(int i = 1; i < Aval + 1; i++){
		for(int j = 1; j < Bval + 1; j++){
			if(a[i].col == newB[j].col){
				d.push_back(term{a[i].row, b[j].col, a[i].val * newB[j].val});
				Dval++;
			}
		}
	}
	d[0].val = Dval;
	d = sumRows(d, Dval);
	return d;
}

//define function sort
//sort the matrix by row
//more convenient to assign matrix elements into an array
vector<term> sort(vector<term> a){
	vector<term> temp;
	temp.push_back(term{a[0].row, a[0].col, a[0].val});
	int index = 0;
	for(int i = 1; i < a[0].val + 1; i++){
		for(int j = 1; j < a[0].val + 1; j++){
			if(a[j].row == index){
				temp.push_back(a[j]);
			}
		}
		index++;
	}
	return temp;
}


int main(int argc, char* argv[]){
	string comp = " ;AB";//used to compare string to elements space, cemicolon, A, and B		
	
	ifstream rFile;//assign read file
	rFile.open(argv[1]);//assign file to first command-line parameter, which is an input file
	
	string s;
	
	int Arow = -1, Acol, Aval;//"Arow and Brow = -1" for convenience in "while" loop below
	int Brow = -1, Bcol, Bval;
		
	vector<term> mA;//matrix A
	vector<term> mB;//matrix B
	
	bool flagA = true;
	bool flagB = false;
	bool ulock = true;//lock or unlock "if" statement below in while loop
	
	term a = {0,0,0};//assigned {row = 0, col = 0, val = 0} to a, for convenience

	mA.push_back(a);//leave first row to add values after loop
	mB.push_back(a);
	
	int nonZeroA = 0;//to count how many non-zero entires are in matrix A
	int nonZeroB = 0;//to count how many non-zero entires are in matrix B;

	while(getline(rFile, s)){
		if(s[0] == comp[2]){//if s[0] is A, then flagA = true. Meaning that values are going to be stored in matrix A
			flagA= true;
			flagB = false;
			nonZeroA = 0;
		}
		if(s[0] == comp[3]){//if s[0] is B, then flagB = true. Values from file are going to be stored in matrix B
			flagA = false;
			flagB = true;
			nonZeroB = 0;
		}
		if(s[0] != comp[2] && s[0] != comp[3]){
			int col = 0;//assign 0 to "col" after new line being read from file

			if(flagA) Arow++;//because of these "if" and "else if" statement I have assigned "Arow = Brow = -1"
					 //earlier in the code
			else if(flagB){
			       	Brow++;
				col = 0;
			}
		
			istringstream ss(s);//create "stringstream ss" from "string s"
			char c;
			int t;
			while (ss >> t){//assign integers from "ss" to "int t" 
				if(flagA){//assign values to matrix A
					if(t != 0){//"t != 0" means that current matrix has +1 value
						nonZeroA++;
						mA.push_back(term{Arow, col, t});
					}	
					col++;
				}
				if(flagB){//assign values to matrix B
					if(t != 0){
						nonZeroB++;
						mB.push_back(term{Brow, col, t});
					}
					col++;
				}
				if(flagA){//since I dont want to assign "col" to "colA", I just lock the "if" statement
				          //to make code faster a bit
					Acol = col;
					ulock = false;
				}
				if(flagB){
					Bcol = col;
					ulock = false;
				}
			}
		}
	}
	rFile.close();

	//if "Arow" or "Brow" are less than 0 which means that they are -1 since I have assign them to be eqaul to -1 earlier
	//means that one of these matrices does not have elements
	if(Arow < 0){
		cout<<"\nMatrix A is not defined"<<endl;
		exit(0);
	}	
	if(Brow < 0){
		cout<<"\nMatrix B is not defined"<<endl;
		exit(0);
	}
	//earlier I have created first row to assign values into it after the matrices are defined
	//so, the frist row will store information about matrices
	//such as, number of rows, columns, and non-zero entries
	mA[0] = term{Arow + 1, Acol, nonZeroA};
	mB[0] = term{Brow + 1, Bcol, nonZeroB};

	if(mA[0].val > (mA[0].row * mA[0].col)/2){
		cout<<"Warning!"<<endl;
		cout<<"Number of non-zero entries in matrix A is less that number of zero entries."<<endl;
		cout<<"This algorithm may not be suitable for you!"<<endl;
	}
	if(mB[0].val > (mB[0].row * mB[0].col)/2){
		cout<<"Warning!"<<endl;
		cout<<"Number of non-zero entries in matrix A is less that number of zero entries."<<endl;
		cout<<"This algorithm may not be suitable for you!"<<endl;
	}
	//create matrix C
	vector<term> mC;

	//create matrices to store transpose of matrices
	vector<term> transp;
	vector<term> transp2;

	//here are the conditions from "Problem description part"
	if(mA[0].col == mB[0].row){//n = p
		//cout<<"\ncase1 :"<<endl;
		if(mA[0].col == mB[0].row){
			mC = mult2(mA, mB);
			
		}
		else{
			cout<<"Error! Matrices are incompetible!"<<endl;
			exit(0);
		}
	}
	else if(mA[0].row == mB[0].row){// m = p
		//cout<<"\ncase2 :\n";
		transp = transpose(mA, transp);
		if(transp[0].col == mB[0].row){
			mC = mult2(transp, mB);
		}
		else{
			cout<<"Error! Matrices are incompetible!"<<endl;
			exit(0);
		}
	}
	else if(mA[0].col == mB[0].col){//n = q
		//cout<<"\nCAse3\n";
		transp = transpose(mB, transp);
		if(mA[0].col == transp[0].row){
			mC = mult2(mA, transp);
		}
		else{
			cout<<"Error! Matrices are incompetible!"<<endl;
			exit(0);
		}
	}
	else if(mA[0].row == mB[0].col){//m = q
		//cout<<"\nCASE 4\n";
		transp = transpose(mA, transp);
		transp2 = transpose(mB, transp2);
		if(transp[0].col == transp2[0].row){
			mC = mult2(transp, transp2);
		}
		else{
			cout<<"Error! Matrices are incompetible!"<<endl;
			exit(0);
		}
	}
	else{
		cout<<"Error! Matrices are incompetible"<<endl;
		exit(0);
	}

	mC = sort(mC);//sort matrix C

	ofstream wFile;//create file to write
	wFile.open(argv[2]);//assign second command-line parameter to the file

	int arrayC[mC[0].row][mC[0].col] = { };//create 2D array C with size of 2D vector mC and fill it with zeros


	//assign non-zero entries from mC to arrayC
	for(int i = 1; i < mC[0].val + 1; i++){
		arrayC[mC[i].row][mC[i].col] = mC[i].val;
	}
	
	//write values from arrayC to File
	for(int i = 0; i < sizeof(arrayC)/sizeof(arrayC[0]); i++){
		for(int j = 0; j < sizeof(arrayC[0])/sizeof(int); j++){
		//	cout<<arrayC[i][j]<<" ";
			wFile<<arrayC[i][j]<<" ";
		}
		wFile<<";\n";
		//cout<<endl;
	}
	cout<<"\nThe values were successfully written to the file "<<argv[2]<<"!"<<endl;
	wFile.close();

	return 0;
}
