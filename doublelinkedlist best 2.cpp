#include <iostream>
using namespace std;

/**
  class Node
  brief Represents a node in the doubly linked
 */
class Node {
	public:
		int data;       // Data stored in the node
		Node *prev;     // Pointer to previous node
		Node *next;     // Pointer to next node

		// Constructor to initialize node with data and null pointers
		Node(int val) : data(val), prev(nullptr), next(nullptr) {}
};

/**
 Implements a doubly linked list with various operation
 */
class DoublyLinkedList {
	private:
		Node *head;  // Pointer to first node in list
		Node *tail;  // Pointer to last node in list

	public:
		// Constructor initializes empty list
		DoublyLinkedList() : head(nullptr), tail(nullptr) {}

		/**
		 brief Destructor to clean up memory by deleting all nodes
		 */
		~DoublyLinkedList() {
			Node *current = head;
			while (current != nullptr) {
				Node *next = current->next;  // Save next node before deleting current
				delete current;              // Free memory for current node
				current = next;              // Move to next node
			}
		}
		/**
		  Inserts a new node at the beginning of the list
		 */
		void insertAtBeginning(int val) {
			Node *newNode = new Node(val);  // Create new node
			if (head == nullptr) {          // If list is empty
				head = tail = newNode;      // New node becomes both head and tail
			} else {
				newNode->next = head;       // New node points to current head
				head->prev = newNode;       // Current head's prev points to new node
				head = newNode;             // Update head to new node
			}
			cout << "Inserted " << val << " at the beginning.\n";
		}

		/**
		 Inserts a new node at the end of the list
		 */
		void insertAtEnd(int val) {
			Node *newNode = new Node(val);  // Create new node
			if (tail == nullptr) {          // If list is empty
				head = tail = newNode;      // New node becomes both head and tail
			} else {
				tail->next = newNode;       // Current tail points to new node
				newNode->prev = tail;       // New node's prev points to current tail
				tail = newNode;             // Update tail to new node
			}
			cout << "Inserted " << val << " at the end.\n";
		}

		/**
		  Inserts a new node at a specific position
		 */
		void insertAtPosition(int val, int pos) {
			if (pos < 1) {  // Validate position
				cout << "Invalid position! Position must be >= 1.\n";
				return;
			}
			if (pos == 1) {  // Handle insertion at beginning
				insertAtBeginning(val);
				return;
			}// Traverse to node before insertion point
			Node *current = head;
			int count = 1;
			while (current != nullptr && count < pos - 1) {
				current = current->next;
				count++;
			}
			if (current == nullptr) {  // Position exceeds list length
				cout << "Position out of range!\n";
				return;
			}
			// Create and insert new node
			Node *newNode = new Node(val);
			newNode->next = current->next;
			newNode->prev = current;

			if (current->next != nullptr) {  // If not inserting at end
				current->next->prev = newNode;
			} else {
				tail = newNode;  // Update tail if inserting at end
			}
			current->next = newNode;
			cout << "Inserted " << val << " at position " << pos << ".\n";
		}
		/**
		 	Deletes the first node from the list
		*/
		void deleteFromBeginning() {
			if (head == nullptr) {  // Check for empty list
				cout << "List is empty! Cannot delete.\n";
				return;
			}
			Node *temp = head;  // Save node to delete
			head = head->next;  // Move head to next node
			if (head != nullptr) {
				head->prev = nullptr;  // Remove prev reference
			} else {
				tail = nullptr;  // List became empty
			}
			cout << "Deleted " << temp->data << " from the beginning.\n";
			delete temp;  // Free memory
		}
		/**
		 	 Deletes the last node from the list
		*/
		void deleteFromEnd() {
			if (tail == nullptr) {  // Check for empty list
				cout << "List is empty! Cannot delete.\n";
				return;
			}
			Node *temp = tail;  // Save node to delete
			tail = tail->prev;  // Move tail to previous node
			if (tail != nullptr) {
				tail->next = nullptr;  // Remove next reference
			} else {
				head = nullptr;  // List became empty
			}
			cout << "Deleted " << temp->data << " from the end.\n";
			delete temp;  // Free memory
		}
		/**
			 Deletes a node from a specific position
		*/
		void deleteFromPosition(int pos) {
			if (head == nullptr) {  // Check for empty list
				cout << "List is empty! Cannot delete.\n";
				return;
			}
			if (pos < 1) {  // Validate position
				cout << "Invalid position! Position must be >= 1.\n";
				return;
			}
			if (pos == 1) {  // Handle deletion at beginning
				deleteFromBeginning();
				return;
			}
			// Traverse to node to delete
			Node *current = head;
			int count = 1;
			while (current != nullptr && count < pos) {
				current = current->next;
				count++;
			}
			if (current == nullptr) {  // Position exceeds list length
				cout << "Position out of range!\n";
				return;
			}
			// Update surrounding nodes' pointers
			current->prev->next = current->next;
			if (current->next != nullptr) {
				current->next->prev = current->prev;
			} else {
				tail = current->prev;  // Update tail if deleting last node
			}
			cout << "Deleted " << current->data << " from position " << pos << ".\n";
			delete current;  // Free memory
		}
		/**
		 Displays the list from head to tail
		 */
		void displayForward() {
			if (head == nullptr) {  // Check for empty list
				cout << "List is empty!\n";
				return;
			}
			Node *current = head;
			cout << "List (Forward): ";
			while (current != nullptr) {
				cout << current->data;
				if (current->next != nullptr) {
					cout << " <-> ";  // Show connection between nodes
				}
				current = current->next;
			}
			cout << "\n";
		}
		/**
		  Displays the list from tail to head
		 */
		void displayBackward() {
			if (tail == nullptr) {  // Check for empty list
				cout << "List is empty!\n";
				return;
			}
			Node *current = tail;
			cout << "List (Backward): ";
			while (current != nullptr) {
				cout << current->data;
				if (current->prev != nullptr) {
					cout << " <-> ";  // Show connection between nodes
				}
				current = current->prev;
			}
			cout << "\n";
		}
};

/**
 Main function with menu-driven interface
*/
int main() {
	DoublyLinkedList dll;
	int choice, value, position;
	do {
		cout << "\nDoubly Linked List Operations\n";
		cout << "1. Insert at beginning\n";
		cout << "2. Insert at end\n";
		cout << "3. Insert at position\n";
		cout << "4. Delete from beginning\n";
		cout << "5. Delete from end\n";
		cout << "6. Delete from position\n";
		cout << "7. Display list (Forward)\n";
		cout << "8. Display list (Backward)\n";
		cout << "0. Exit\n";
		cout << "Enter your choice: ";
		cin >> choice;
		switch (choice) {
			case 1:
				cout << "Enter value to insert: ";
				cin >> value;
				dll.insertAtBeginning(value);
				break;
			case 2:
				cout << "Enter value to insert: ";
				cin >> value;
				dll.insertAtEnd(value);
				break;
			case 3:
				cout << "Enter value : ";
				cin >> value;
				cout << "Enter position: ";
				cin >> position;
				dll.insertAtPosition(value, position);
				break;
			case 4:
				cout << "Delete from beginning\n";
				dll.deleteFromBeginning();
				break;
			case 5:
				cout << "Delete from end\n";
				dll.deleteFromEnd();
				break;
			case 6:
				cout << "delete from position: ";
				cin >> position;
				dll.deleteFromPosition(position);
				break;
			case 7:
				dll.displayForward();
				break;
			case 8:
				dll.displayBackward();
				break;
			case 0:
				cout << "Exiting program...\n";
				break;
			default:
				cout << "Invalid choice! Please try again.\n";
		}
	} while (choice != 0);

	return 0;
}