#include <iostream> 
#include <fstream> 
#include <cstdlib>

using namespace std; 

int main() {
	ifstream fin("dna.txt"); //Opens file
	if (fin.fail()) { //Sets fail code
	    cerr << "File cannot be read, opened, or does not exist.\n"; //Prints fail message
	    exit(1); //Exits fail code
	}
	string strand; //Creates integer to input string into
	while(getline(fin, strand)) { //Reads file and inputs into string strand
	    for (int i = 0; i < strand.length(); i++) { //Sets for loop
	    	if (strand[i] == 'A' || strand[i] == 'a') { //Checks if the letter is A
	    		cout << 'U'; //Changes letter to U
	    	} else if (strand[i] == 'T' || strand[i] == 't') { //Checks if the letter is T
	    		cout << 'A'; //Changes letter to A
	    	} else if (strand[i] == 'C' || strand[i] == 'c') { //Checks if the letter is C
	    		cout << 'G'; //Changes letter to G
	    	} else if (strand[i] == 'G' || strand[i] == 'g') { //Checks if the letter is G
	    		cout << 'C'; //Changes leter to C
	    	} else { //Otherwise
	    		cout << "\n"; //Prints a new line
	    	}
	    }
	    cout << "\n"; //Prints a new line when string reaches its end
	}
	fin.close(); //Closes file
	return 0;
}