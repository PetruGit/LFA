﻿// tema1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Transition {
public:
	string state1;
	string state2;
	string letter;

	Transition (string str1, string str2, string ch) {
		this->state1 = str1;
		this->state2 = str2;
		this->letter = ch;
	}
};

class autom {
public:
	vector<string> alphabet;
	vector<string> states;
	vector<string> finalStates;
	string firstState;
	vector<Transition> transitions;

	autom(string firstState) {
		this->firstState = firstState;
	}

	void setAlphabet(vector<string> alphabet) {
		this->alphabet = alphabet;
	}

	void setStates(vector<string> states) {
		this->states = states;
	}

	void setFinalStates(vector<string> finalStates) {
		this->finalStates = finalStates;
	}

	void setTransitions(vector<Transition> transitions) {
		this->transitions = transitions;
	}

	bool inAlphabet(string str) {
		for (int i = 0; i < alphabet.size(); i++)
			if (alphabet[i] == str)
				return true;
		return false;
	}

	bool isFinalState(string str) {
		for (int i = 0; i < finalStates.size(); i++)
			if (finalStates[i] == str)
				return true;
		return false;
	}
};

void readAutom(const char* file, autom* aut) {
	ifstream f(file);
	int n; string str;

	// Alphabet
	vector<string> alphabet; f >> n;
	
	getline(f, str);
	for (int i = 0; i < n; i++) {
		getline(f, str);
		alphabet.push_back(str);
	}
	aut->setAlphabet(alphabet);

	// States
	vector<string> states; f >> n;

	getline(f, str);
	for (int i = 0; i < n; i++) {
		getline(f, str);
		states.push_back(str);
	}
	aut->setStates(states);

	// Final states
	vector<string> finalStates; f >> n;
	
	getline(f, str);
	for (int i = 0; i < n; i++) {
		getline(f, str);
		finalStates.push_back(str);
	}
	aut->setFinalStates(finalStates);

	// Transitions
	vector<Transition> transitions; f >> n;
	getline(f, str);
	string state1, state2;
	for (int i = 0; i < n; i++) {
		getline(f, state1, ' ');
		getline(f, state2, ' ');
		getline(f, str);

		transitions.push_back(*(new Transition(state1, state2, str)));
	}
	aut->setTransitions(transitions);
}

bool hasSpaces(string str) {
	for (int i = 0; i < str.size(); i++)
		if (str[i] == ' ')
			return true;
	return false;
}

vector<string> getWords(string word) {
	vector<string> words;

	int i = 0, j;
	for (j = 0; j < word.size(); j++) 
		if (word[j] == ' ') {
			string str = word.substr(i, j - i);
			i = j + 1;
			words.push_back(str);
		}
	
	if (i < j)
		words.push_back(word.substr(i, j));
	return words;
}

void print(vector<string> str) {
	for (int i = 0; i < str.size(); i++)
		cout << str[i] <<"|"<< endl;
}

int main()
{
	autom *a = new autom("start");
	readAutom("autom.txt", a);
	a->print();

	cout << "Give me a word: ";
	string word; getline(cin, word);
	string curState = a->firstState;

	if (word == "*") {
		if (a->isFinalState(curState))
			cout << "Accepted" << endl;
		else
			cout << "Rejected" << endl;
		return 0;
	}
		
	if (hasSpaces(word)) {
		vector<string> words = getWords(word);

		print(words);
		for (int i = 0; i < words.size(); i++) {
			if (!a->inAlphabet(words[i])) {
				cout << "Word not in alphabet!";
				cin.ignore();
				cin.ignore();
				return 0;
			}

			bool found = false;
			for (int j = 0; j < a->transitions.size(); j++)
				if (a->transitions[j].state1 == curState
					and a->transitions[j].letter == words[i]) {
					curState = a->transitions[j].state2;
					found = true;
					break;
				}
			if (!found) {
				cout << " was rejected!" << endl;
				cin.ignore();
				cin.ignore();
				return 0;
			}
		}
	}
	else {
		char ch[1];
		for (int i = 0; i < word.size(); i++) {
			string letter; letter.push_back(word[i]);

			if (!(a->inAlphabet(letter))) {
				cout << word[i] << " letter not in alphabet!";
				cin.ignore();
				cin.ignore();
				return 0;
			}

			bool found = false;
			for (int j = 0; j < a->transitions.size(); j++)
				if (a->transitions[j].state1 == curState
					and a->transitions[j].letter == letter) {
					curState = a->transitions[j].state2;
					found = true;
					break;
				}
			if (!found) {
				cout << word << " was rejected!" << endl;
				cin.ignore();
				cin.ignore();
				return 0;
			}
		}
	}

	if (a->isFinalState(curState))
		cout << word << " was accepted!" << endl;
	else
		cout << word << " was rejected!" << endl;

	cin.ignore();
    return 0;
}

