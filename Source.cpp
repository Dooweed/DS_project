#include <iostream>
#include "Task.h"
#include "List.h"
#include "PriorityQueue.h"

using namespace std;

void print_queue(PriorityQueue<Task>* queue) {
	queue->sort();
	int len = queue->length();
	Task* task;
	PriorityItem<Task>** tasks = queue->get_items();
	cout << "-------------------------" << endl;
	for (int i = 1; i <= len; i++) {
		cout << " " << i << " - ";
		task = tasks[i]->get_object();
		task->print_short_info();
		cout << "-------------------------" << endl;
	}
}

void print_list(List<Task>* list) {
	cout << "-------------------------" << endl;
	for (Node<Task>* ptr = list->get_head(); ptr != nullptr; ptr = ptr->get_next()) {
		cout << "  - ";
		Task* task = ptr->get_value();
		task->print_short_info();
		cout << "-------------------------" << endl;
	}
}

void change_task(PriorityQueue<Task>* queue) {
	print_queue(queue);
	Task* task;
	int choice = input_range_int("Choose task to change (0 to exit): ", 0, queue->length());
	if (choice == 0){
		return;
	}
	else { // Remove task and add it back to implement "changing priority"
		task = queue->remove(choice);
		string title, description;

		cout << "Enter new title or submit empty line to remove previous title: ";
		getline(cin, title);
		if (!title.empty())
			task->set_title(title);

		cout << "Enter new description or submit empty line to remove previous description: ";
		getline(cin, description);
		if (!description.empty())
			task->set_description(description);

		int choice = input_range_int("Do you wish to change the deadline? (1-Yes/0-No): ", 0, 1);
		if (choice == 1)
			task->set_deadline(task->input_deadline());

		system("cls");
		beauty_print("Successfully changed:", 2, 2);
		task->print_full_info();
		queue->enqueue(task, task->get_deadline());
	}
}

void remove_task(PriorityQueue<Task>* queue) {
	print_queue(queue);
	Task* task;
	int choice = input_range_int("Choose task to remove (0 to exit): ", 0, queue->length());
	if (choice == 0)
		return;
	else
		task = queue->remove(choice);
	system("cls");
	beauty_print("Successfully removed:", 2, 2);
	task->print_full_info();
	delete task;
}

void remove_passed_deadlines(PriorityQueue<Task>* queue, List<Task>* passed_deadlines) {
	int i;
	for (i=0; queue->peek()->deadline_passed(); i++) {
		passed_deadlines->insert_beg(queue->dequeue());
	}
	string report("Moved " + to_string(i) + " tasks");
	beauty_print(report, 2, 2);
}

bool main_menu(PriorityQueue<Task>* queue, List<Task>* passed_deadlines) {
	system("cls");
	int n = 1;
	cout << n++ << ": Show the closest task" << endl;
	cout << n++ << ": Show all tasks" << endl;
	cout << n++ << ": Add new task" << endl;
	cout << n++ << ": Change existing task" << endl;
	cout << n++ << ": Remove the closest task" << endl;
	cout << n++ << ": Remove particular task" << endl;
	cout << n++ << ": Show passed deadlines" << endl;
	cout << n++ << ": Remove passed deadlines from queue" << endl;
	cout << "0: exit" << endl;

	Task* task;
	int choice = input_range_int("Choose action: ", 0, 8);

	switch (choice) {
	case 1:
		system("cls");
		task = queue->peek();
		task->print_full_info();
		break;
	case 2:
		system("cls");
		print_queue(queue);
		break;
	case 3:
		system("cls");
		task = new Task();
		queue->enqueue(task, task->get_deadline());
		break;
	case 4:
		system("cls");
		change_task(queue);
		break;
	case 5:
		system("cls");
		task = queue->dequeue();
		beauty_print("Successfully removed:", 2, 2);
		task->print_full_info();
		delete task;
		break;
	case 6:
		system("cls");
		remove_task(queue);
		break;
	case 7:
		system("cls");
		print_list(passed_deadlines);
		break;
	case 8:
		system("cls");
		remove_passed_deadlines(queue, passed_deadlines);
		break;
	case 0:
		return false;
	}
	system("pause");
	return true;
}

int main() {
	const int SECS_IN_DAY = 24 * 60 * 60;

	// Create queue
	PriorityQueue<Task>* queue = new MinPriorityQueue<Task>(100);

	// Create list with passed deadlines
	List<Task>* passed_deadlines = new List<Task>;

	// Create tasks
	Task* tasks[] = {
		new Task("Java project", "Complete project work", time(0) + SECS_IN_DAY * 10),
		new Task("AE project", "Complete project work", time(0) + SECS_IN_DAY * 2),
		new Task("DS project", "Complete project work", time(0) + SECS_IN_DAY * 5),
		new Task("Final exams", "Complete project work", time(0) + SECS_IN_DAY * 20),
		new Task("DS Midterm", "Complete Data Structure midterm work", time(0) - SECS_IN_DAY * 20),
		new Task("New year", "Have a rest", time(0) + SECS_IN_DAY * 6),
		new Task("End of finals", "Survive", time(0) + SECS_IN_DAY * 40),
		new Task("Java lab", "Complete java lab", time(0) + SECS_IN_DAY * 3),
		new Task("Fly", "Learn to fly", time(0) + SECS_IN_DAY * 42),
		new Task("Die", "Meet a bus with the face", time(0) + SECS_IN_DAY * 365 * 8),
		new Task("Java Midterm", "Complete Java midterm work", time(0) - SECS_IN_DAY * 22),
	};
	int len = sizeof(tasks) / sizeof(Task*);

	// Make array of Priority items to insert several objects in O(n) time
	PriorityItem<Task>** priority_tasks = new PriorityItem<Task>*[len];
	for (int i = 0; i < len; i++)
		priority_tasks[i] = new PriorityItem<Task>(tasks[i], tasks[i]->get_deadline());

	// Add items to queue
	queue->build(priority_tasks, len);
	// Free memory
	delete priority_tasks;


	// Start menu cycle
	system("MODE 100");
	while (main_menu(queue, passed_deadlines));


	system("pause");
	return 0;
}