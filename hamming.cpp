#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <cstdlib>

using namespace std;

int main() {
	ifstream fin("mutations.txt"); //Opens file
	if (fin.fail()) { //Sets fail code
	    cerr << "File cannot be read, opened, or does not exist.\n"; //Prints fail message
	    exit(1); //Exits fail code
	}
	string mut, orig;
	while (getline (fin, mut), getline (fin, orig)) {
		int count = 0;
		for (int i = 0; i < 45; i++) {
			if (mut[i] != orig[i]) {
				count += 1;
			}
		}
		if (count > 0) {
			cout << count << " yes" << endl;
			count = 0;
		} else {
			cout << 0 << " no" << endl;
			count = 0;
		}
	}
	return 0;
}