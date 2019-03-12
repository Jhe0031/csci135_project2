#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

int main() {
	ifstream fin("dna.txt");
	if (fin.fail()) {
	    cerr << "File cannot be read, opened, or does not exist.\n";
	    exit(1);
	}
	string strand;
	while(getline(fin, strand)) {
	    // cout << strand << endl;
	    for (int i = 0; i < strand.length(); i++) {
	    	if (strand[i] == 'A') {
	    		cout << 'U';
	    	} else if (strand[i] == 'T') {
	    		cout << 'A';
	    	} else if (strand[i] == 'C') {
	    		cout << 'G';
	    	} else if (strand[i] == 'G') {
	    		cout << 'C';
	    	} else {
	    		cout << "\n";
	    	}
	    }
	    cout << "\n";
	}
	fin.close();
	return 0;
}