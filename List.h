#pragma once

template <typename T>
class Node {
private:
	T value;
	Node* next;

public:
	Node(T value, Node* next) {
		this->value = value;
		this->next = next;
	}

	// Getters
	T get_value(){
		return this->value;
	}
	Node* get_next() {
		return this->next;
	}

	// Setters
	void set_value(T value) {
		this->value = value;
	}
	void set_next(Node* next) {
		this->next = next;
	}
};

template <typename T>
class List {
private:
	Node<T>* head;
	int n;

public:
	void insert_beg(T value) { insert(value, 0); }
	void insert_end(T value) { insert(value, n); }
	void insert(T value, int position) {
		if (position < 0 || position > n) {
			throw out_of_range("Insertion index is out of range");
		}

		if (position == 0) {
			this->head = new Node<T>(value, this->head); // Creating new node
		}
		else {
			Node<T>* prev_ptr = this->head;

			for (int i = 1; i < position; i++) {
				prev_ptr = prev_ptr->get_next();
			}

			prev_ptr->set_next( new Node<T>(value, prev_ptr->get_next()) );
		}
		n += 1;
	}

	void remove_beg() { remove(0); }
	void remove_end() { remove(n-1); }
	void remove(int index) {
		if (index < 0 || index > n - 1) {
			throw out_of_range("Deletion index is out of range");
		}

		Node<T>* prev_ptr = this->head;
		if (index == 0) {
			this->head = this->head->get_next();
			delete prev_ptr;
		}
		else {
			Node<T>* current_ptr = prev_ptr->get_next();

			for (int i = 0; i < index - 1; i++, prev_ptr = current_ptr, current_ptr = current_ptr->get_next());

			prev_ptr->set_next(current_ptr->get_next());
			delete current_ptr;
		}
		n -= 1;
	}

	void remove_val(T value, bool all=false) {
		if (this->head) { // If list is not empty
			Node<T>* prev_ptr = this->head;

			// Checking zero indexed element
			if (this->head->get_value() == value) {
				this->head = this->head->get_next();
				delete prev_ptr;
				n -= 1;
				if (!all) { // Do not return if user wants to delete all elements with this value
					return;
				}
			}

			// Checking rest of the elements
			Node<T>* current_ptr = prev_ptr->get_next();
			for (int i = 1; i < n; i++, prev_ptr = current_ptr, current_ptr = current_ptr->get_next()) {
				if (current_ptr->get_value() == value) {
					prev_ptr->set_next(current_ptr->get_next());
					delete current_ptr;
					n -= 1;

					if (all) { // Do not return if user wants to delete all elements with this value
						current_ptr = prev_ptr;
						i--;
					}
					else {
						return;
					}
				}
			}
		}
		
	}

	void print() {
		cout << "[ ";
		Node<T>* ptr = this->head;
		for (int i = 0; i < n; i++) {
			cout << ptr->get_value();
			if (i != n - 1) {
				cout << ", ";
				ptr = ptr->get_next();
			}
		}
		cout << " ]" << endl;
	}
};