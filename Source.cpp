#include <iostream>
#include "Task.h"
#include "List.h"

using namespace std;



int main() {
	List<int> list = List<int>();

	list.insert_end(1);
	list.insert_end(2);
	list.insert_end(3);
	list.insert_end(4);
	list.insert_end(5);

	list.print();

	list.remove_beg();

	list.print();

	list.remove_end();

	list.print();

	list.remove_beg();

	list.print();

	list.remove_end();

	list.print();

	system("pause");
	return 0;
}