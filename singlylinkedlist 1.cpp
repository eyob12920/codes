#include <iostream>
// Use standard namespace (optional, but used in the original code)
using namespace std;

class SinglyLinkedList {
	private: // Keep Node private
		struct Node {
			int data;
			Node *next;
			Node(int value) : data(value), next(nullptr) {} // Constructor for Node
		};
		Node *head; // Pointer to the first node
	public:
		// Constructor
		SinglyLinkedList() : head(nullptr) {}

		// Destructor (Essential to prevent memory leaks!)
		~SinglyLinkedList() {
			Node *current = head;
			Node *nextNode = nullptr;
			while (current != nullptr) {
				nextNode = current->next; // Store next node
				delete current;          // Delete current node
				current = nextNode;      // Move to the next node
			}
			head = nullptr; // Ensure head is null after deletion
			cout << "\nList destroyed. Memory freed." << endl;
		}
		// Insert at the Beginning
		void insertAtBeginning(int value) {
			Node *newNode = new Node(value); // Correct 'new' syntax and variable name
			newNode->next = head;
			head = newNode;
			cout << value << " inserted at the beginning." << endl;
		}
		// Insert at the End
		void insertAtEnd(int value) {
			Node *newNode = new Node(value); // Correct 'new' syntax
			if (head == nullptr) { // If list is empty
				head = newNode;
				cout << value << " inserted at the end (list was empty)." << endl;
				return;
			}
			Node *temp = head;
			while (temp->next != nullptr) { // Traverse to the last node
				temp = temp->next;
			}
			temp->next = newNode; // Link the last node to the new node
			cout << value << " inserted at the end." << endl;
		}
		// Insert at a specific position (1-based index)
		void insertAtPosition(int value, int position) {
			if (position < 1) {
				cout << "Invalid position! Position must be 1 or greater." << endl;
				return;
			}
			// Node *newNode = new Node(value); // Allocate node *after* position check if possible
			if (position == 1) {
				insertAtBeginning(value); // Reuse existing function
				// No need to create newNode again here
				return;
			}
			Node *newNode = new Node(value); // Allocate node now
			Node *temp = head;
			// Traverse to the node *before* the desired position
			for (int i = 1; temp != nullptr && i < position - 1; ++i) {
				temp = temp->next;
			}
			// If temp is null (position out of range) or head is null but pos > 1
			if (temp == nullptr) {
				cout << "Position out of range!" << endl;
				delete newNode; // IMPORTANT: Free memory if insertion fails
				return;
			}
			// Insert the new node
			newNode->next = temp->next;
			temp->next = newNode;
			cout << value << " inserted at position " << position << "." << endl;
		}
		// Delete from the Beginning (Corrected Logic)
		void deleteFromBeginning() {
			if (head == nullptr) {
				cout << "List is empty! Cannot delete from beginning." << endl;
				return;
			}
			Node *temp = head;       // Node to be deleted
			head = head->next;     // Move head to the next node
			cout << temp->data << " deleted from the beginning." << endl;
			delete temp;           // Free the memory of the original head
		}
		// Delete from the End (Added Function)
		void deleteFromEnd() {
			if (head == nullptr) {
				cout << "List is empty! Cannot delete from end." << endl;
				return;
			}
			// If there is only one node in the list
			if (head->next == nullptr) {
				cout << head->data << " deleted from the end (only node)." << endl;
				delete head;
				head = nullptr; // List is now empty
				return;
			}
			// Traverse to the second-to-last node
			Node *secondLast = head;
			while (secondLast->next->next != nullptr) {
				secondLast = secondLast->next;
			}
			Node *nodeToDelete = secondLast->next; // Node to delete is the last one
			cout << nodeToDelete->data << " deleted from the end." << endl;
			delete nodeToDelete;             // Delete the last node
			secondLast->next = nullptr;      // Set the new last node's next to null
		}
		// Delete from a specific position (1-based index)
		void deleteAtPosition(int position) {
			if (position < 1) {
				cout << "Invalid position! Position must be 1 or greater." << endl;
				return;
			}
			if (head == nullptr) {
				cout << "List is empty! Cannot delete." << endl;
				return;
			}
			// If deleting the first node
			if (position == 1) {
				deleteFromBeginning(); // Reuse existing function
				return;
			}
			Node *temp = head;
			Node *prev = nullptr; // Keep track of the previous node
			// Traverse to the node *at* the desired position
			// Keep track of the previous node as well
			for (int i = 1; temp != nullptr && i < position; ++i) {
				prev = temp;
				temp = temp->next;
			}
			// If position is out of range (temp became null before reaching position)
			if (temp == nullptr) {
				cout << "Position out of range!" << endl; // Corrected typo
				return;
			}
			// Unlink the node to be deleted
			prev->next = temp->next;
			cout << temp->data << " deleted from position " << position << "." << endl;
			delete temp; // Delete the node
		}
		// Display the linked list
		void display() {
			if (head == nullptr) {
				cout << "List is empty!" << endl;
				return;
			}
			Node *temp = head;
			cout << "List: ";
			while (temp != nullptr) {
				cout << temp->data << " -> ";
				temp = temp->next;
			}
			cout << "NULL" << endl;
		}
};

int main() {
	SinglyLinkedList list; // Correct variable name (lowercase 'l')
	int choice, value, position;
	while (true) {
		cout << "\nSingly Linked List Operations" << endl; // Improved Menu Title
		cout << "1. Insert at the beginning" << endl;
		cout << "2. Insert at the end" << endl;
		cout << "3. Insert at a Specific position" << endl;
		cout << "4. Delete from the beginning" << endl;
		cout << "5. Delete from the end" << endl;
		cout << "6. Delete from specific position" << endl;
		cout << "7. Display the List" << endl; // Corrected syntax (removed comma)
		cout << "8. Exit" << endl;
		cout << "Enter your choice: "; // Added space for clarity
		cin >> choice;
		switch (choice) {
			case 1:
				cout << "Enter value: ";
				cin >> value;
				list.insertAtBeginning(value); // Correct function name
				break;
			case 2:
				cout << "Enter value: ";
				cin >> value;
				list.insertAtEnd(value); // Correct function name
				break;
			case 3:
				cout << "Enter value and position : "; // Clarified input prompt
				cin >> value >> position;
				list.insertAtPosition(value, position);
				break;
			case 4:
				list.deleteFromBeginning();
				break;
			case 5:
				list.deleteFromEnd(); // Now calls the correct function
				break;
			case 6:
				cout << "Enter position: ";
				cin >> position;
				list.deleteAtPosition(position);
				break;
			case 7:
				list.display();
				break;
			case 8:
				cout << "Exiting program." << endl;
				return 0; // Exit the program
			default:
				cout << "Invalid choice! Please try again.\n";
		}
	}
	return 0;
}