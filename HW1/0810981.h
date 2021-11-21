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
