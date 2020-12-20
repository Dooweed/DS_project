#pragma once
#include <iostream>
#include <time.h>
#include "Utils.h"

using namespace std;

class TaskCore {
	string title;
	string description;
	time_t deadline;
	struct tm* deadline_tm;

public:
	TaskCore(string title, string description, time_t deadline) {
		this->title = title;
		this->description = description;
		this->set_deadline(deadline);
	}
	TaskCore() {};

	// Returns true if deadline is passed, otherwise false
	bool deadline_passed() {
		time_t current_time = time(NULL);
		return this->deadline < current_time;
	}

	// Returns deadline as prettified string
	string get_deadline_string() {

		// Creating and initialising time structure
		struct tm* timeinfo = new tm();
		localtime_s(timeinfo, &this->deadline);

		// Specifying date formatting string
		string strf_string = "%e %B, %R";

		// Creating and initialising the actual date string
		char time[26] = {};
		strftime(time, sizeof(time), strf_string.c_str(), timeinfo);

		// Freeing memory
		delete timeinfo;

		// Returning date string with "(passed)" indicator if deadline is passed, otherwise returning only date string
		if (this->deadline_passed()) {
			string time_str(time);
			return "(passed) " + time_str;
		}
		else {
			return time;
		}
	}

	// Setters
	void set_title(string title) {
		this->title = title;
	}
	void set_description(string description) {
		this->description = description;
	}
	void set_deadline(time_t deadline) {
		this->deadline = deadline;
		// Allocate memory for deadline_tm if it was not allocated yet
		if (!this->deadline_tm) {
			this->deadline_tm = new tm(); 
		}
		localtime_s(this->deadline_tm, &deadline);
	}
	void set_deadline(tm* deadline_tm) {
		if (this->deadline_tm) {
			delete this->deadline_tm;
		}
		this->deadline_tm = deadline_tm;
		this->deadline = mktime(deadline_tm);
	}

	// Getters
	string get_title() {
		return this->title;
	}
	string get_description() {
		return this->description;
	}
	time_t get_deadline() {
		return this->deadline;
	}
	tm* get_deadline_tm() {
		return this->deadline_tm;
	}
};

class Task : public TaskCore {
public:
	// Parametrized constructor
	Task(string title, string description, time_t deadline) : TaskCore(title, description, deadline) {};
	// Input constructor
	Task() : TaskCore() {
		this->set_values();
		beauty_print("A new task has successfully been created:", 10, 2);
		this->print_full_info();
		system("pause");
		system("cls");
	};

	void set_values() {
		beauty_print("Create a new task:", 3, 2);
		this->set_title(this->input_title());
		system("cls");

		beauty_print("Create a new task:", 3, 2);
		this->set_description(this->input_description());
		system("cls");

		beauty_print("Create a new task:", 3, 2);
		this->set_deadline(this->input_deadline());
		system("cls");
	}

	string input_title() { // Ask for title input
		string str;
		return input(str, "Please enter the title: ");
	}

	string input_description() { // Ask for description input
		string str;
		return input(str, "Please enter the description: ");
	}

	tm* input_deadline() { // Ask for deadline input

		// Creating and filling time structure
		struct tm* timeinfo = new tm();
		timeinfo->tm_year = input_range_int("Please enter the year: ", 1900) - 1900;
		timeinfo->tm_mon = input_range_int("Please enter the month: ", 1, 12) - 1;
		timeinfo->tm_mday = input_range_int("Please enter the day: ", 1, 31);
		timeinfo->tm_hour = input_range_int("Please enter the hour: ", 0, 23);
		timeinfo->tm_min = input_range_int("Please enter the minute: ", 0, 59);
		timeinfo->tm_sec = 0;

		return timeinfo;
	}

	void print_full_info() {
		cout << "-------" << endl;

		beauty_print(get_title(), 7, 2);
		beauty_print(get_description(), 8, 2);

		int color = this->deadline_passed() ? 4 : 6; // Indicating date with red if deadline is passed, otherwise green
		beauty_print(this->get_deadline_string(), color, 1, "Deadline: ");

		cout << "-------" << endl;
	}
};