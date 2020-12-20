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

// Function to convert from char [] to string 
string char_array_to_string(char char_array[], int length_of_array) {
	string temp = "";
	for (int i = 0; i < 30; i++)
	{
		if (char_array[i] == '\0')
			break;
		temp += char_array[i];
	}
	return temp;
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
	int value;
	while (true) {
		input(value, text);
		if (min <= value && max >= value) {
			return value;
		}
		else {
			char buffer[100];
			snprintf(buffer, sizeof(buffer), "Please enter the value between %d and %d", min, max);
			beauty_print(buffer, 6, 1);
		}
	}
}

// Function to check whether item exists in an array
template <class item_type, class ar_type>
bool item_in_array(item_type item, ar_type& ar, int length) {
	for (int i = 0; i < length; i++)
	{
		if (item == ar[i]) {
			return true;
		}
	}
	return false;
}
// Function to display all color text-background combinations
void colors() {
	system("cls");
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	// you can loop k higher to see more color choices
	for (int k = 1; k < 255; k++)
	{
		// pick the colorattribute k you want
		SetConsoleTextAttribute(hConsole, k);
		cout << k << " I want to be nice today!" << endl;
	}
	SetConsoleTextAttribute(hConsole, 7);
	system("pause");
}