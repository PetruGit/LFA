// tema2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Derivare {
public:
	char neterminal;
	string res;

	Derivare(char ch, string res) {
		this->neterminal = ch;
		this->res = res;
	}
};

bool isTerminal(char ch) {
	if ((int)ch >= 97)
		return true;
	return false;
}

bool verifica(vector<Derivare> derivari, string cuvant, char stare) {
	// lambda gasita
	if (cuvant.length() == 0) {
		for (int i = 0; i < derivari.size(); i++) 
			if (derivari[i].neterminal == stare && derivari[i].res._Equal("?"))
				return true;
		return false;
	}

	bool ok = false;
	for (int i = 0; i < derivari.size(); i++) 
		if (derivari[i].neterminal == stare) {
			string res = derivari[i].res;
			if (res.size() == 1) {
				if (isTerminal(res[0])) {
					if (cuvant.compare(res) == 0)
						ok = true;
				}
				else ok = (verifica(derivari, cuvant, res[0])) ? true : ok;
			}
			else {
				if (isTerminal(res[0]) && cuvant[0] == res[0])
					ok = (verifica(derivari, cuvant.substr(1), res[1])) ? true : ok;
				else if(cuvant[cuvant.length()-1] == res[1])
					ok = (verifica(derivari, cuvant.substr(0,cuvant.length()-1), res[0])) ? true : ok;
			}
		}
	
	return ok;
}

void print(vector<Derivare> d) {
	for (int i = 0; i < d.size(); i++)
		cout << d[i].neterminal << " " << d[i].res << endl;
}

vector<Derivare> citesteDerivari(string fileName) {
	vector<Derivare> input;

	ifstream file(fileName);
	int n; file >> n;

	for (int i = 0; i < n; i++) {
		char neterminal; file >> neterminal;
		string res; file >> res;

		Derivare *d = new Derivare(neterminal, res);
		input.push_back(*d);
	}
	
	return input;
}

int main()
{
	string fileName = "derivari.txt";
	vector<Derivare> derivari = citesteDerivari(fileName);
	print(derivari);

	string cuvant;
	cout << "Verifica cuvant: "; cin >> cuvant;
	
	if (verifica(derivari, cuvant, 'S'))
		cout << "True!" << endl;
	else
		cout << "False.." << endl;

	cin.ignore();
	cin.ignore();
    return 0;
}

