#pragma once

#include <string>
#include "Task.h"
using namespace std;

template <typename T> class MaxBinaryHeap;
template <typename T> class MinBinaryHeap;

// Exchanges values passed by reference
template <typename T>
void exchange_values(T& value_1, T& value_2) {
	T temp = value_1;
	value_1 = value_2;
	value_2 = temp;
}

/*
  Abstract class for MinBinaryHeap and MaxBinaryHeap
  child classes must implement percolate_up, percolate_down, remove and build functions in a proper way

  Heap can only accept comparable types ( <, >, == )
*/
template <typename T>
class BinaryHeap {
protected:
	int MAX_LEN;
	int len; // Points to the next after the last non-empty value
	T** items;

protected:
	// Returns item array as a string
	string get_string() {
		string str("{");
		for (int i = 1; i < this->len; i++) {
			str.append(to_string(*this->items[i]));
			if (i != this->len) {
				str.append(", ");
			}
		}
		str.append(" }");
		return str;
	}

	// Returns true if array has empty space and false otherwise
	bool has_available_space() {
		return this->len < this->MAX_LEN;
	}
	// Returns true if element has no children
	bool is_leaf(int index) {
		return index * 2 >= this->len;
	}

	// Returns index of the left child if it exists and -1 otherwise
	int left_child(int parent_index) {
		int child_index = parent_index * 2;
		return child_index < this->len ? child_index : -1;
	}
	// Returns index of the right child if it exists and -1 otherwise
	int right_child(int parent_index) {
		int child_index = parent_index * 2 + 1;
		return child_index < this->len ? child_index : -1;
	}
	// Returns index of the parent
	int parent(int child_index) {
		return child_index / 2;
	}

	// Returns index of the smallest child and -1 if parent has no children
	int smallest_child(int parent_index) {
		int l_child = left_child(parent_index), r_child = right_child(parent_index);
		if (l_child == -1 || r_child == -1) // If node has less than 2 children
			return l_child == -1 ? -1 : l_child;
		else
			return *this->items[l_child] < *this->items[r_child] ? l_child : r_child;
	}
	// Returns index of the biggest child and -1 if parent has no children
	int biggest_child(int parent_index) {
		int l_child = left_child(parent_index), r_child = right_child(parent_index);
		if (l_child == -1 || r_child == -1) // If node has less than 2 children
			return l_child == -1 ? -1 : l_child;
		else
			return *this->items[l_child] > *this->items[r_child] ? l_child : r_child;
	}

	// Moves up an element to a proper position
	virtual void percolate_up(int i) = 0;
	// Moves down an element to a proper position. Takes index of element as an argument
	virtual void percolate_down(int i) = 0;

	// Default value calls
	void percolate_up() { percolate_up(this->len); }
	void percolate_down() { percolate_down(1); }

public:
	// Constructor
	BinaryHeap<T>(int max_len) {
		this->items = new T* [max_len+1];

		this->MAX_LEN = max_len+1;
		this->len = 1;
	}
	~BinaryHeap() {
		delete this->items;
	}

	// Returns true if heap is empty and false otherwise
	bool is_empty() {
		return this->len <= 1;
	}

	// Print array
	void print() {
		cout << this->get_string() << endl;
	}

	// Insert new value to appropriate place in the heap
	void insert(T* number) {
		if (this->has_available_space()) {
			this->items[this->len] = number;
			this->percolate_up();
			this->len += 1;
		}
		else {
			cout << "Heap is full" << endl;
		}
	}

	// Removes and returns root element
	T* remove_root() {
		if (this->is_empty()) {
			cout << "Heap is empty, nothing to remove" << endl;
			return NULL;
		}
		else {
			T* element = this->get_root();
			this->items[1] = this->items[this->len - 1];
			this->len -= 1;
			percolate_down();
			return element;
		}
	}

	// Returns index of corresponding value
	int index_of(T value) {
		for (int i = 1; i < this->len; i++) {
			if (this->items[i] == value) {
				return i;
			}
		}
		return NULL;
	}

	// Removes element by value and returns it
	T* remove_value(T value) {
		return remove(index_of(value));
	}

	// Removes element by index and returns it
	virtual T* remove(int index) = 0;
	// Sorting the heap
	virtual void sort() = 0;

	// Returns root element without deleting it
	T* get_root() {
		if (this->is_empty()) {
			cout << "Heap is empty" << endl;
			return NULL;
		}
		else
			return this->items[1];
	}

	// Getters
	int get_len() {
		return this->len - 1;
	}
	T** get_items() {
		return this->items;
	}

	// Setters
	void set_len(int len) {
		this->len = len;
	}
	void set_items(T** items) {
		this->items = items;
	}

	// Insert array of new values in O(n). Works faster than calling insert() for every element of array ( O(nlogn) ). Works only for empty heap.
	void build(T* array[], int length, bool skip_first=false) {
		if (this->len == 1) {
			int starting_index = skip_first ? 1 : 0;
			for (int i = starting_index; i < length; i++, this->len++) { // Append elements of list to this->items
				this->items[this->len] = array[i];
			}
			for (int i = length / 2; i > 0; i--) { // Move element to a proper position
				this->percolate_down(i);
			}
		}
		else {
			cout << "Heap is not empty" << endl;
		}
	}
};

template <typename T>
class MinBinaryHeap : public BinaryHeap<T> {
private:
	void percolate_up(int i) {
		for (; i / 2 > 0; i /= 2) {
			T& child = *this->items[i], & parent = *this->items[i / 2];
			if (child < parent) { // Exchange parent with child if child value is less than parent value
				exchange_values(child, parent);
			}
		}
	}
public:
	MinBinaryHeap(int max_len) : BinaryHeap<T>(max_len) {};

	void percolate_down(int i) {
		while (!this->is_leaf(i)) {
			int smallest_child_index = this->smallest_child(i);
			T& parent = *this->items[i], & child = *this->items[smallest_child_index];
			if (child < parent) // Exchange parent with child if child value is less than parent value
				exchange_values(child, parent);

			i = smallest_child_index;
		}
	}

	T* remove(int index) {
		if (index < this->len && index > 0) {
			T &element = *this->items[index], &last_element = *this->items[this->len - 1], &parent_element = *this->items[this->parent(index)];
			exchange_values(element, last_element);
			this->len -= 1;
			if (element < parent_element)
				percolate_up(index);
			else
				percolate_down(index);
			return &last_element;
		}
		else {
			cout << "Index is out of bounds" << endl;
			return NULL;
		}
	}

	void sort() {
		MaxBinaryHeap<T>* max_heap = new MaxBinaryHeap<T>(this->MAX_LEN);
		max_heap->build(this->items, this->len, true);
		T** max_heap_items = max_heap->get_items();

		for (int i = this->len - 1; i > 1; i--) {
			T& last = *max_heap_items[i], & root = *max_heap_items[1];
			exchange_values(last, root);
			max_heap->set_len(max_heap->get_len());
			max_heap->percolate_down(1);
		}
		delete max_heap;
	}

	// Just another name to remove_root function
	T* remove_min() { return this->remove_root(); }
	// Just another name to get_root function
	T* get_min() { return this->get_root(); }
};

template <typename T>
class MaxBinaryHeap : public BinaryHeap<T> {
private:
	void percolate_up(int i) {
		for (int i = this->len; i / 2 > 0; i /= 2) {
			T &child = *this->items[i], &parent = *this->items[i / 2];

			if (child > parent) // Exchange parent with child if child value is bigger than parent value
				exchange_values(child, parent);
		}
	}
public:
	MaxBinaryHeap(int max_len) : BinaryHeap<T>(max_len) {};

	void percolate_down(int i) {
		while (!this->is_leaf(i)) {
			int biggest_child_index = this->biggest_child(i);
			T& parent = *this->items[i], & child = *this->items[biggest_child_index];
			if (child > parent) // Exchange parent with child if child value is bigger than parent value
				exchange_values(child, parent);

			i = biggest_child_index;
		}
	}

	T* remove(int index) {
		if (index < this->len && index > 0) {
			T &element = *this->items[index], &last_element = *this->items[this->len - 1], &parent_element = *this->items[this->parent(index)];
			exchange_values(element, last_element);
			this->len -= 1;
			if (element < parent_element)
				percolate_down(index);
			else
				percolate_up(index);
			return &last_element;
		}
		else {
			cout << "Index is out of bounds" << endl;
			return NULL;
		}
	}

	void sort() {
		MinBinaryHeap<T>* min_heap = new MinBinaryHeap<T>(this->MAX_LEN);
		min_heap->build(this->items, this->len, true);
		T** min_heap_items = min_heap->get_items();

		for (int i = this->len - 1; i > 1; i--) {
			T& last = *min_heap_items[i], & root = *min_heap_items[1];
			exchange_values(last, root);
			min_heap->set_len(min_heap->get_len());
			min_heap->percolate_down(1);
		}
		delete min_heap;
	}

	// Just another name to remove_root function
	T* remove_max() { return this->remove_root(); }
	// Just another name to get_root function
	T* get_max() { return this->get_root(); }
};
