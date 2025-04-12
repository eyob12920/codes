#include <iostream>
using namespace std;

// Node structure for circular doubly linked list
class Node {
	public:
		int data;     // Data stored in the node
		Node *prev;   // Pointer to previous node
		Node *next;   // Pointer to next node
		Node(int val) : data(val), prev(nullptr), next(nullptr) {}  // Constructor
};

class CircularDoublyLinkedList {
	private:
		Node *head;  // Pointer to the first node
	public:
		CircularDoublyLinkedList() : head(nullptr) {}  // Initialize empty list
		~CircularDoublyLinkedList() {  // Destructor to free memory
			if (!head)
				return;
			Node *current = head->next;
			while (current != head) {  // Traverse and delete all nodes
				Node *temp = current;
				current = current->next;
				delete temp;
			}
			delete head;  // Delete the head node
		}
		void insertAtBeginning(int val) {  // Insert node at start
			Node *newNode = new Node(val);
			if (!head) {  // If list is empty
				head = newNode;
				head->next = head;
				head->prev = head;
			} else {
				newNode->next = head;          // New node points to head
				newNode->prev = head->prev;    // New node prev points to tail
				head->prev->next = newNode;    // Tail points to new node
				head->prev = newNode;          // Head prev points to new node
				head = newNode;                // Update head
			}
		}

		void insertAtEnd(int val) {  // Insert node at end
			Node *newNode = new Node(val);
			if (!head) {  // If list is empty
				head = newNode;
				head->next = head;
				head->prev = head;
			} else {
				newNode->next = head;          // New node points to head
				newNode->prev = head->prev;    // New node prev points to tail
				head->prev->next = newNode;    // Tail points to new node
				head->prev = newNode;          // Head prev points to new node
			}
		}

		void insertAtPosition(int val, int pos) {  // Insert at specific position
			if (pos <= 0)
				return;  // Invalid position
			if (pos == 1) {
				insertAtBeginning(val);
				return;
			}

			Node *current = head;
			for (int i = 1; i < pos - 1 && current->next != head; i++) // Traverse
				current = current->next;

			Node *newNode = new Node(val);
			newNode->next = current->next;  // New node points to next
			newNode->prev = current;        // New node prev points to current
			current->next->prev = newNode;  // Next node's prev points to new
			current->next = newNode;        // Current points to new node
		}

		void deleteFromBeginning() {  // Delete first node
			if (!head)
				return;  // Empty list
			if (head->next == head) {  // Single node
				delete head;
				head = nullptr;
				return;
			}
			Node *temp = head;              // Node to delete
			head->prev->next = head->next;  // Tail points to new head
			head->next->prev = head->prev;  // New head's prev points to tail
			head = head->next;              // Update head
			delete temp;                    // Free memory
		}

		void deleteFromEnd() {  // Delete last node
			if (!head)
				return;  // Empty list
			if (head->next == head) {  // Single node
				delete head;
				head = nullptr;
				return;
			}
			Node *temp = head->prev;    // Node to delete (tail)
			temp->prev->next = head;    // New tail points to head
			head->prev = temp->prev;    // Head prev points to new tail
			delete temp;                // Free memory
		}

		void deleteFromPosition(int pos) {  // Delete from position
			if (pos <= 0 || !head)
				return;  // Invalid
			if (pos == 1) {
				deleteFromBeginning();
				return;
			}

			Node *current = head;
			for (int i = 1; i < pos && current->next != head; i++)  // Traverse
				current = current->next;

			if (current == head)
				return;  // Position too large
			current->prev->next = current->next;  // Bypass node
			current->next->prev = current->prev;  // Bypass node
			delete current;                       // Free memory
		}

		void displayForward() {  // Display all nodes forward
			if (!head) {
				cout << "List is empty\n";
				return;
			}
			Node *current = head;
			do {
				cout << current->data << " <-> ";
				current = current->next;
			} while (current != head);  // Loop until back to start
			cout << "(head)\n";
		}

		void displayBackward() {  // Display all nodes backward
			if (!head) {
				cout << "List is empty\n";
				return;
			}
			Node *current = head->prev;
			do {
				cout << current->data << " <-> ";
				current = current->prev;
			} while (current != head->prev);  // Loop until back to start
			cout << "(tail)\n";
		}
};

int main() {
	CircularDoublyLinkedList cdll;
	int choice, val, pos;

	do {
		cout << "\nCircular Doubly Linked List Operations\n";
		cout << "1. Insert at beginning\n";
		cout << "2. Insert at end\n";
		cout << "3. Insert value and position\n";
		cout << "4. Delete from beginning\n";
		cout << "5. Delete from end\n";
		cout << "6. Delete from position\n";
		cout << "7. Display forward\n";
		cout << "8. Display backward\n";
		cout << "0. Exit\n";
		cout << "Enter choice: ";
		cin >> choice;

		switch (choice) {
			case 1:
				cout << "Enter value:\n";
				cin >> val;
				cdll.insertAtBeginning(val);
				break;
			case 2:
				cout << "Enter value:\n ";
				cin >> val;
				cdll.insertAtEnd(val);
				break;
			case 3:
				cout << "Enter value and position:\n";
				cin >> val >> pos;
				cdll.insertAtPosition(val, pos);
				break;
			case 4:
				cout << "delete from the beginning\n";
				cdll.deleteFromBeginning();
				break;
			case 5:
				cout << "delete from the end\n";
				cdll.deleteFromEnd();
				break;
			case 6:
				cout << "delete the position: \n";
				cin >> pos;
				cdll.deleteFromPosition(pos);
				break;
			case 7:
				cdll.displayForward();
				break;
			case 8:
				cdll.displayBackward();
				break;
			case 0:
				cout << "Exiting...\n";
				break;
			default:
				cout << "Invalid choice!\n";
		}
	} while (choice != 0);

	return 0;
}