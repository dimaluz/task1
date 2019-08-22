// task1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int calculation(string);
double median(vector<int>*);
double percentile(vector<int>*, int);

int main(int argc, char* argv[]){
	if(argc<2){
		cout<<"WARNING main(): Filename has not been specified."<<endl;
		system("pause");
		exit(-1);
	}
	string filename = argv[1];
	calculation(filename);
	system("pause");
	return 0;
}

int calculation(string filename){
	ifstream fin(filename, ios_base::in);
	vector<int> Numbers;
	int number=0; double sum=0.0;
	if(!fin.is_open()){
		cout<<"WARNING calculation(): File cannot be opened."<<endl;
		fin.close();
		return -1;
	}
	else{
		for(fin>>number; !fin.eof(); fin>>number){
			Numbers.push_back(number);
			sum+=number;
		}
		fin.close();
	}
	sort(Numbers.begin(), Numbers.end());
	cout<<fixed; cout.precision(2);
	cout<<percentile(&Numbers, 90)<<endl;
	cout<<median(&Numbers)<<endl;
	cout<<Numbers[Numbers.size()-1]*1.0<<endl;
	cout<<Numbers[0]*1.0<<endl;
	cout<<sum/(Numbers.size()*1.0)<<endl;
	
	return 0;
}

double median(vector<int>* buffer){
	int N = (*buffer).size();
	double result = 0.0; int index = N/2;
	if(N%2!=0)
		result = (*buffer)[index];
	else
		result = ((*buffer)[index] + (*buffer)[index-1]) / 2.0;
	return result;
}
double percentile(vector<int>* buffer, int k){
	double result=0.0;
	int N = (*buffer).size();
	double d=0.0;

	if(k == 50)
		result=median(buffer);
	else{
		if(k < 50){
			d=(N*k)/100.0;
			if(d == ceil(d))
				result=((*buffer)[d]+(*buffer)[d+1])/2.0;
			else{
				int value = (int)(d + 0.5);
				result=(*buffer)[value];
			}	
		}
		if(k > 50){
			k = 100 - k;
			d = (N*k)/100.0;
			if(d == ceil(d))
				result=((*buffer)[N-d]+(*buffer)[N-d-1])/2.0;
			else{
				int value = (int)(d + 0.5);
				result=(*buffer)[N-value];
			}	
		}
	}
	return result;
}