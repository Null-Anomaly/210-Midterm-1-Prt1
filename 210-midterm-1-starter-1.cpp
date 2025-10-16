#include <iostream> //For input and output hence io
using namespace std;//Usting a c++ standard 

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20; //Sets the minimum and maximum
//values for later random number generation

class DoublyLinkedList { //Creates the class DoublyLinkedList
private://Determines which items are private
    struct Node {//Creates a struture of type Node
        int data;//Integer variabe
        Node* prev;//Variable pointer for pointing to previous node
        Node* next;//Variable pointer for pointing to next node
        Node(int val, Node* p = nullptr, Node* n = nullptr) { //Paramaterized constructor
            data = val; //Sets data to val
            prev = p; //Sets prev to p
            next = n; //Sets next to n
        }
    };

    Node* head; //Variable pointer for pointing to the head/first element in the list
    Node* tail;//Variable pointer for pointing to the tail/last element in the list

public: //What everything can see regardless of being a class member or not
    DoublyLinkedList() { head = nullptr; tail = nullptr; }//Default constructor

    void insert_after(int value, int position) { //Inserts a node after a certain position
        if (position < 0) { //Validification
            cout << "Position must be >= 0." << endl; //Prints the error
            return; //Returns the function
        }

        Node* newNode = new Node(value); //Creates a new node object with value variable
        if (!head) { //Checks if list is empty
            head = tail = newNode; //If true, set head and tail to newNode
            return;
        }

        Node* temp = head; //If it's not, creates and sets the node temp to point to head
        for (int i = 0; i < position && temp; ++i) //Loops until it reaches position int and isn't Null
            temp = temp->next;//Sets temp to instead equal the next node from its current pos

        if (!temp) {//If temp is null
            cout << "Position exceeds list size. Node not inserted.\n";//prints error message
            delete newNode; //Clean up. Prevents memory leaks
            return;//Returns the function
        }

        newNode->next = temp->next; //If valid, it allows the new node to actually exist.
                                    //
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode;
        temp->next = newNode;
    }

    void delete_val(int value) {
        if (!head) return;

        Node* temp = head;
        
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; 

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next; 

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev; 

        delete temp;
    }

    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
    
        if (pos == 1) {
            pop_front();
            return;
        }
    
        Node* temp = head;
    
        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) {
            pop_back();
            return;
        }
    
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(int v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    void push_front(int v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }
};

int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning

    
    return 0;
}