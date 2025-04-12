#include <iostream>
using namespace std;

// Node structure for circular singly linked list
class Node {
	public:
		int data;    // Data stored in the node
		Node *next;  // Pointer to next node
		Node(int val) : data(val), next(nullptr) {}  // Constructor
};

class CircularSinglyLinkedList {
	private:
		Node *head;  // Pointer to the first node
	public:
		CircularSinglyLinkedList() : head(nullptr) {}  // Initialize empty list
		~CircularSinglyLinkedList() {  // Destructor to free memory
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
				head->next = head;  // Point to itself
			} else {
				newNode->next = head->next;  // New node points to current first
				head->next = newNode;        // Head points to new node
			}
		}

		void insertAtEnd(int val) {  // Insert node at end
			Node *newNode = new Node(val);
			if (!head) {  // If list is empty
				head = newNode;
				head->next = head;  // Point to itself
			} else {
				newNode->next = head->next;  // New node points to first
				head->next = newNode;        // Current last points to new node
				head = newNode;              // Update head to new last node
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
			for (int i = 1; i < pos && current->next != head; i++)  // Traverse
				current = current->next;

			Node *newNode = new Node(val);
			newNode->next = current->next;  // Insert after current
			current->next = newNode;
			if (current == head)
				head = newNode;  // Update head if inserted at end
		}

		void deleteFromBeginning() {  // Delete first node
			if (!head)
				return;  // Empty list
			if (head->next == head) {  // Single node
				delete head;
				head = nullptr;
				return;
			}
			Node *temp = head->next;       // Node to delete
			head->next = temp->next;       // Bypass node
			delete temp;                   // Free memory
		}

		void deleteFromEnd() {  // Delete last node
			if (!head)
				return;  // Empty list
			if (head->next == head) {  // Single node
				delete head;
				head = nullptr;
				return;
			}
			Node *current = head;
			while (current->next != head)  // Find node before head
				current = current->next;
			current->next = head->next;    // Bypass head
			delete head;                   // Delete old head
			head = current;                // Update head
		}

		void deleteFromPosition(int pos) {  // Delete from position
			if (pos <= 0 || !head)
				return;  // Invalid
			if (pos == 1) {
				deleteFromBeginning();
				return;
			}

			Node *current = head;
			for (int i = 1; i < pos - 1 && current->next != head; i++) // Traverse
				current = current->next;

			if (current->next == head)
				return;  // Position too large
			Node *temp = current->next;         // Node to delete
			current->next = temp->next;         // Bypass node
			if (temp == head)
				head = current;   // Update head if deleting last
			delete temp;                        // Free memory
		}

		void display() {  // Display all nodes
			if (!head) {
				cout << "List is empty\n";
				return;
			}
			Node *current = head->next;
			do {
				cout << current->data << " -> ";
				current = current->next;
			} while (current != head->next);  // Loop until back to start
			cout << "(head)\n";
		}
};

int main() {
	CircularSinglyLinkedList csll;
	int choice, val, pos;

	do {
		cout << "\nCircular Singly Linked List Operations\n";
		cout << "1. Insert at beginning\n";
		cout << "2. Insert at end\n";
		cout << "3. Insert value and position\n";
		cout << "4. Delete from beginning\n";
		cout << "5. Delete from end\n";
		cout << "6. Delete from position\n";
		cout << "7. Display list\n";
		cout << "0. Exit\n";
		cout << "Enter choice: ";
		cin >> choice;

		switch (choice) {
			case 1:
				cout << "Enter value:\n";
				cin >> val;
				csll.insertAtBeginning(val);
				break;
			case 2:
				cout << "Enter value:\n";
				cin >> val;
				csll.insertAtEnd(val);
				break;
			case 3:
				cout << "Enter value and position:\n";
				cin >> val >> pos;
				csll.insertAtPosition(val, pos);
				break;
			case 4:
				cout << "delete from the beginning\n";
				csll.deleteFromBeginning();
				break;
			case 5:
				cout << "delete from the end\n";
				csll.deleteFromEnd();
				break;
			case 6:
				cout << "delete from position:\n";
				cin >> pos;
				csll.deleteFromPosition(pos);
				break;
			case 7:
				csll.display();
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