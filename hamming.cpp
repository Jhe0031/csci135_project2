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
	string mut, orig; // Creates string variables to hold the two lines
	while (getline (fin, mut), getline (fin, orig)) { // Takes in the two lines
		int count = 0; // Creates a variable to count the amount of changes
		for (int i = 0; i < 45; i++) { // For loop 
			if (mut[i] != orig[i]) { 
				count += 1; // Adds one for every substitution
			}
		}
		if (count > 0) { 
			cout << count << " no" << endl; // Ouputs the value of count in addition to whether or not there is a mutation
			count = 0; // Resets the count value
		} else { 
			cout << 0 << " no" << endl; // Ouputs the value of count in addition to whether or not there is a mutation
			count = 0; // Resets the count value
		}
	}
	return 0;
}