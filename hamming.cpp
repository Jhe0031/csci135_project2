#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <cstdlib>

using namespace std;

string mrna(string strand) {
	string new_s = "";
	for (int i = 0; i < strand.length(); i+0) { //Sets for loop
		if (strand[i] == 'A' || strand[i] == 'a') { //Checks if the letter is A
			new_s += "U"; //Changes letter to U
		} else if (strand[i] == 'T' || strand[i] == 't') { //Checks if the letter is T
			new_s += "A"; //Changes letter to A
		} else if (strand[i] == 'C' || strand[i] == 'c') { //Checks if the letter is C
			new_s += "G"; //Changes letter to G
		} else if (strand[i] == 'G' || strand[i] == 'g') { //Checks if the letter is G
			new_s += "C"; //Changes leter to C
		} else { //Otherwise
			new_s += ""; //Prints a new line
		}
		i += 1;
	}
	return new_s;
}

string codon(string new_s, ifstream &dict) {
	// if (dict.fail()) { //Sets fail code
	    // cerr << "codons.tsv: File cannot be read, opened, or does not exist.\n"; //Prints fail message
	    // exit(1); //Exits fail code
	// }
	int j = 0;
	string codon = "";
	string three = "";
	while (j < new_s.length()) {
		for (int k = 0; k < 3; k++) {
			three += new_s[j];
			j += 1;
		}
		if (three == "AUG") {
			while (j < new_s.length()) {
				if (three == "UAA" || three == "UGA" || three == "UAG") {
					codon = codon.substr(0, codon.size()-1);
					codon += "\n";
					three = "";
					break;
				}
				string key, value;
				dict.clear(); // reset error state
				dict.seekg(0); // return file pointer to the beginning
				while (dict >> key >> value) {
					if (key == three) {
						codon += value;
						codon += "-";
					}
				}
				three = "";
				for (int k = 0; k < 3; k++) {
					three += new_s[j];
					j += 1; 
				}
			}
		} else {
			three = "";
		}
		if (j >= new_s.length()) {
			codon = codon.substr(0, codon.size()-1);
		}
	}
	// dict.close();
	return codon;
}

int main() {
	ifstream fin("mutations.txt"); //Opens file
	if (fin.fail()) { //Sets fail code
	    cerr << "mutations.txt: File cannot be read, opened, or does not exist.\n"; //Prints fail message
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
		string new_mut = mrna(mut);
		string new_orig = mrna(orig);

		ifstream read_dict("codons.tsv");
		string mut_codon = codon(new_mut, read_dict);
		string orig_codon = codon(new_orig, read_dict);

		int codon_count = 0;
		for (int n = 0; n <= mut_codon.length(); n+0) {
			if (mut_codon[n, n+2] != orig_codon[n, n+2]){
				codon_count += 1;
			}
			n += 3;
			if (mut_codon[n] == char(45)) {
				n += 1;
			}
		}

		cout << count;
		if (count == 0) {
			cout << " no" << endl;
		} else if (codon_count == 0) {
			cout << " no" << endl;
		} else if (codon_count > 0) {
			cout << " yes" << endl;
		} 
		count = 0;
		codon_count = 0;
		
	}
	return 0;
}