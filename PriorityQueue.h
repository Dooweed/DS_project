#pragma once
#include "Heap.h"

template <typename T>
class PriorityItem {
	T* object;
	long long priority;
public:
	PriorityItem(T* object, long long priority) {
		this->object = object;
		this->priority = priority;
	}

	// Getters
	T* get_object() {
		return this->object;
	}

	// Comparison operator overloading
	bool operator < (const PriorityItem& obj) {
		return this->priority < obj.priority;
	}
	bool operator > (const PriorityItem& obj) {
		return this->priority > obj.priority;
	}
	bool operator == (const PriorityItem& obj) {
		return this->priority == obj.priority;
	}
};

// This class should not be instantiated
template <typename T>
class PriorityQueue {
protected:
	BinaryHeap<PriorityItem<T>> *heap;

	PriorityQueue() {};
public:
	~PriorityQueue() {
		delete this->heap;
	}

	void enqueue(T* obj, long long priority) {
		heap->insert(
			new PriorityItem<T>(obj, priority)
		);
	}

	// Insert array of new values in O(n). Works faster than calling insert() for every element of array ( O(nlogn) ). Works only for empty heap.
	void build(PriorityItem<T>* array[], int length) {
		heap->build(array, length);
	}
	
	T* dequeue() {
		PriorityItem<T> *priority_item = heap->remove_root();
		T* obj = priority_item->get_object();
		delete priority_item;
		return obj;
	}

	T* remove(int index) {
		PriorityItem<T>* priority_item = heap->remove(index);
		T* obj = priority_item->get_object();
		delete priority_item;
		return obj;
	}

	T* peek() {
		return heap->get_root()->get_object();
	}

	PriorityItem<T>** get_items() {
		return heap->get_items();
	}

	void print() {
		heap->print();
	}

	int length() {
		return this->heap->get_len();
	}

	void sort() {
		this->heap->sort();
	}
};

template <typename T>
class MinPriorityQueue : public PriorityQueue<T> {
public:
	MinPriorityQueue(int max_len) {
		this->heap = new MinBinaryHeap<PriorityItem<T>>(max_len);
	}
};

template <typename T>
class MaxPriorityQueue : public PriorityQueue<T> {
public:
	MaxPriorityQueue(int max_len) {
		this->heap = new MaxBinaryHeap<PriorityItem<T>>(max_len);
	}
};


template <typename T>
string to_string(PriorityItem<T> item) {
	return to_string(*item.get_object());
}
