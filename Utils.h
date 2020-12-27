#pragma once
#include<iostream>
#include<Windows.h>
#include<string>

using namespace std;

// Function to print out the text with different color
void beauty_print(string text, int color, int endlines = 0, string text_before="", string text_after="") {
	for (int i = 0; i < endlines; i++) {
		text += '\n';
	}
	cout << text_before;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
	cout << text;
	SetConsoleTextAttribute(hConsole, 7);
	cout << text_after;
}

// Function to prettify text
string prettify(string text, int length, string options = "") {
	if (options == "middle") {
		int difference = length - text.length();
		if (difference % 2 == 1) {
			difference--;
			text += " ";
		}
		for (int i = 0; i < difference; i += 2)
		{
			text = " " + text + " ";
		}
	}
	else {
		text = " " + text;
		for (int i = 0; length > text.length(); i++)
		{
			text += " ";
		}
	}
	return text;
}

// Function to combine message asking for input and the input itself
string input(string& value, string text) {
	cout << text;
	getline(cin >> ws, value);
	return value;
}
template <class input_value>
input_value input(input_value& value, string text) {
	cout << text;
	cin >> value;
	return value;
}

int input_range_int(string text, int min=0, int max=INT_MAX) {
	string value;
	while (true) {
		input(value, text);
		try {
			int int_value = stoi(value);
			if (min <= int_value && max >= int_value) {
				return int_value;
			}
			else {
				char buffer[100];
				if (max == INT_MAX) {
					snprintf(buffer, sizeof(buffer), "Please enter the value more than %d", min);
				}
				else {
					snprintf(buffer, sizeof(buffer), "Please enter the value between %d and %d", min, max);
				}
				beauty_print(buffer, 6, 1);
			}
		}
		catch (invalid_argument) {
			beauty_print("\nPlease enter an integer", 4, 1);
		}
	}
}