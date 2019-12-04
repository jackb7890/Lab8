#include <string>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include "fnameFinder.h"
#include <vector>
#include <queue>
#include <math.h>

using namespace std;

typedef struct coord {
	int f1;
	int f2;
	int count;
} coord;

//Function Definitions
long hashIt(string key);

string cleanKey(string str);

//Function Implementations
long hashIt(string key){
	const int hashTableSize = 799999;
	long ind = 0;
	for(int i = key.length()-1;i>=0;--i){
		ind += key[key.length()-i-1] * pow(1.3,i);
	}
	ind = ind % hashTableSize;
	if (ind < 0) ind*=-1;
	return ind;
}

string cleanKey(string str){
	string retStr = "";
	for (int i = 0; i < str.length(); ++i){
		if (str[i] >= 65 && str[i] <= 90){
			retStr += str[i] + 32;
		}
		else if(str[i] >= 97 && str[i] <= 122){
			retStr += str[i];
		}
	}
	return retStr;
}

/////////////////////////////////
/////////Main Function///////////
/////////////////////////////////
int main(int argc, char* argv[]){
	string dir = argv[1];
	int chunkSize = atoi(argv[2]);
	int pSize = atoi(argv[3]);
	vector<string> files = vector<string>();
	const int hashTableSize = 799999;
	vector<int> *hashTable = new vector<int> [hashTableSize];
	
	if (getdir(dir, files)){
		cout << "Error getting files" << endl;
		exit(-1);
	}
	//remove references to . and .. directories
	files.erase(files.begin());
	files.erase(files.begin());
	
	//initialize 2d array to hold collosion data
	int **matches = new int*[files.size()];
	for (int i =0; i < files.size(); ++i){
		matches[i] = new int[files.size()];
		for (int j = 0; j < files.size(); ++j){
			matches[i][j] = 0;
		}
	}

	//loops through files
	for (int i = 0; i < files.size(); ++i){
		vector<string> buffer = vector<string>();
		string path = dir + "/" + files[i];
		ifstream iFile;
		iFile.open(path.c_str());
		string word;
		while (iFile >> word){
			if (buffer.size() == chunkSize){//hash when the buffer is at desired chunk size
				string hashStr = "";
				for (int j = 0; j < buffer.size(); ++j){
					hashStr += buffer[j];
				}
				hashStr = cleanKey(hashStr);
				int key = hashIt(hashStr);
				hashTable[key].push_back(i);//populate hash table with the index of the file
				buffer.erase(buffer.begin());//treat vector like queue, pop front
				}
			buffer.push_back(word);//treat vector like queue, push back
		}
}
	//loop through hash table to count similarities between files
	for (int i = 0; i < hashTableSize; ++i){
		
		//checking which files contain a certain chunk
		for (int j = 0; j < hashTable[i].size(); ++j){
			for (int k = j+1; k < hashTable[i].size(); ++k){
				matches[hashTable[i][j]][hashTable[i][k]]++;
			}
		}
	
	}

	//sort file similarity data in vector coords
	vector<coord> coords;
	for (int i = 0; i < files.size(); ++i){
		for(int j = i+1; j < files.size(); ++j){
			coord *c = new coord();
			c->f1 = i;
			c->f2 = j;
			c->count = matches[i][j]; 
			coords.push_back(*c);
		}
	}
	for (int i = 0; i < coords.size(); ++i){
		int maxI = i;
		for (int j = i+1; j < coords.size(); ++j){
			if (coords[maxI].count < coords[j].count){
				maxI = j;
			}
		}
		coord temp = coords[i];
		coords[i] = coords[maxI];
		coords[maxI] = temp;
	}

	//print desired files to screen based on pSize (input parameter to main
	int c = 0;
	while (coords[c].count > pSize){
		cout << coords[c].count << ": " << files[coords[c].f1] << ", " << files[coords[c].f2] << endl;
		c++;
	}
}

