/*Comsc 210 | Midterm 1 Prt 1 | Lawrence Bryant
IDE used: Visual Studio Code*/

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
        } //close constructor
    }; //Closes the struct.

    Node* head; //Variable pointer for pointing to the head/first element in the list
    Node* tail;//Variable pointer for pointing to the tail/last element in the list

public: //What everything can see regardless of being a class member or not
    DoublyLinkedList() { head = nullptr; tail = nullptr; }//Default constructor

    void insert_after(int value, int position) { //Inserts a node after a certain position
        if (position < 0) { //Validification
            cout << "Position must be >= 0." << endl; //Prints the error
            return; //Returns the function
        } //close if

        Node* newNode = new Node(value); //Creates a new node object with value variable
        if (!head) { //Checks if list is empty
            head = tail = newNode; //If true, set head and tail to newNode
            return; //Returns function
        } //Close if

        Node* temp = head; //If it's not, creates and sets the node temp to point to head
        for (int i = 0; i < position && temp; ++i) //Loops until it reaches position int and isn't Null
            temp = temp->next;//Sets temp to instead equal the next node from its current pos

        if (!temp) {//If temp is null
            cout << "Position exceeds list size. Node not inserted.\n";//prints error message
            delete newNode; //Clean up. Prevents memory leaks at end of function
            return;//Returns the function
        }

        newNode->next = temp->next; //If valid, it allows the new node to actually exist.
                                    //It sets that new node to properly point to the intended next node.
        newNode->prev = temp; //Sets the new node to point to the previous node which is temp
        if (temp->next) //If temp's next is not null
            temp->next->prev = newNode; //Has temp's next's previous point instead point to the new node.
        else //If null.
            tail = newNode; //Sets tail to the new node
        temp->next = newNode; //Has temp's next point to the new node since the position stated is for inserting afterwards
    }//Closes out the function

    void delete_val(int value) { //Function for deleting a specific value
        if (!head) return; //If list is empty retun.

        Node* temp = head; //Sets temp node to point at the same node head is pointing at.
        
        while (temp && temp->data != value)//While temp isn't null and the the data of temp isn't equal to the value loop
            temp = temp->next; //Set temp to point to the next node

        if (!temp) return; //Is temp points to nothing, return.

        if (temp->prev) //If temp's previous isn't null do thing
            temp->prev->next = temp->next;//Thing being putting temp's previous's next to point to temp next instead
            //(Which is the same one that temp is also pointing to by the way)
        else//Else
            head = temp->next; //Head is equal to temp's next (Assuming temp's previous is null)

        if (temp->next)//If temp's next is true
            temp->next->prev = temp->prev; //Set temp's next's previous to point to temp's previous
        else//Else
            tail = temp->prev; //Set tail to temp's previous.

        delete temp; //Delete temp after it has successfully disconnected itself and the node from the list.
        //The node which it now effectively is.
    }//Close out function

    void delete_pos(int pos) { //Selects a position and deletes the node 
        if (!head) { //Checks if the list exists
            cout << "List is empty." << endl; //Error message
            return; //Returns function
        } //Close if
    
        if (pos == 1) { //If position is equal to one
            pop_front(); //Calls the pop front function
            return; //Returns function
        } //Closes the if statement
    
        Node* temp = head; //Sets temp to point to head
    
        for (int i = 1; i < pos; i++){ //For int i is less tha- why does i start at 1? Whatever
            //For int i = 1, if i is less than pos, i += 1
            if (!temp) { //If temp isn't null
                cout << "Position doesn't exist." << endl; //Error
                return; //Return function
            } //Close if
            else //Else
                temp = temp->next; //Temp is now equal to temp's next like in line 40
        } //Close if
        if (!temp) {//If temp is equal to NULL
            cout << "Position doesn't exist." << endl; // Error print
            return; //Returns function
        } //Close if
    
        if (!temp->next) { //If temp's next is null
            pop_back(); //Call the popback function to remove that tail
            return; //Returns function
        } //Closes if
    
        Node* tempPrev = temp->prev; //sets the new node tempPrev to temp's previous node
        tempPrev->next = temp->next; //Sets themprev's next to temp's next
        temp->next->prev = tempPrev; //Set temp's next's previous to tempPrev
        delete temp; //Deletes temp and effectively the node at that position by cutting it out.
    } //End of function

    void push_back(int v) { //Function for putting an element at the end of the list
        Node* newNode = new Node(v); //Makes a new node with the value v (shortened from value to v)
        if (!tail)//If tail isn't null
            head = tail = newNode; //Set head to tail to newNode since there's only one thing.
        else { //Else
            tail->next = newNode; //Sets the current tail's next to equal new node
            newNode->prev = tail; //set the newnode's previous to the old tail
            tail = newNode; //Sets tail to equal newNode. Feels like it needs to also now point to Nullptr, but I suppose its handled somewhere else.
        } //End of Else
    } //End of function.
    
    void push_front(int v) { //Function for puting an element at the front of the list.
        Node* newNode = new Node(v); //Creates a new node with value v
        if (!head) //If head is null
            head = tail = newNode; //Set head to tail to newNode.
        else { // Else.
            newNode->next = head; //Set newNode's next to head
            head->prev = newNode; //Set head's previous to newNode
            head = newNode; //Set head to equal newNode
        } //End of else
    } //End of function
    
    void pop_front() { //Function for popping the first element out of the list

        if (!head) { //If head is null
            cout << "List is empty." << endl; //Error output
            return; //Return function
        } //Close if

        Node * temp = head; //Sets temp to point to head as well

        if (head->next) { //If head next exists
            head = head->next; //Head is now head next
            head->prev = nullptr; //Head previous is now NULL. 
        } //Close if
        else //Else
            head = tail = nullptr; //Head's next was null, so head is tail is null
        delete temp; //Delete temp since it was the old head.
    } //Close function out

    void pop_back() { //Pop the back out of existence. 
        if (!tail) {  //If tail is null
            cout << "List is empty." << endl; //Prints out the list being empty
            return; //Return the function.
        } //Close if.
        Node * temp = tail; //As it did for the head, sets temp to tail

        if (tail->prev) { //If tail's previous exists
            tail = tail->prev; //Tail is now its previous point
            tail->next = nullptr; //Has the tail's new next point to NULL
        } //Closes the if
        else //Else.
            head = tail = nullptr; //Head is tail is null
        delete temp; //Delete the temp which was tail to be deleted
    }//Close out function

    ~DoublyLinkedList() { //Deconstructor
        while (head) { //While the list exists
            Node* temp = head; //Sets temp to head
            head = head->next; //Head is equal to the head's next
            delete temp; //Delete temp
        } //No more list. End while loop
    } //End function
    void print() { //Prints the list starting from the head.
        Node* current = head;  //Sets current to head
        if (!current) { //If no elements
            cout << "List is empty." << endl; //Prints out list is empty
            return; //Return function
        } //Close if
        while (current) { //While it points to an element
            cout << current->data << " ";//Prints out the data stored in the node. Makes a space
            current = current->next; //Moves down the list
        } //Closes the while.
        cout << endl; //End line
    } //End print

    void print_reverse() {// Prints out the list starting from the tail, thus the reverse
        Node* current = tail; //Current to tail
        if (!current) {  //If Null
            cout << "List is empty." << endl; //Prints the list is empty
            return; //Return function
        } //Close out if
        while (current) { //While the current isn't null
            cout << current->data << " "; //Prints out the data in the element
            current = current->prev; //Moves to the previous element which is effectively reverse.
        }//Close while
        cout << endl; //End line
    } //End the reverse print

    //My member function version.
    void every_other_element() //Prints out every other element
    {
        Node* current = head;  
        if (!current) { 
            cout << "List is empty." << endl; 
            return; 
        } 
        while (current) {
            cout << current->data << " ";
            if (!current->next) //Checks if the next element is null
            {
                    break; //Break out of the while if the next element is null.
            } 
            current = current->next->next; 
        } 
        cout << endl; 
    }

}; //End of class

int main() { //Main function
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS << "\n";  // dummy statement to avoid compiler warning. Neat
    DoublyLinkedList test;

    test.push_back(2);
    test.push_back(3);
    test.push_back(4);
    test.push_back(5);
    test.push_back(6);

    test.every_other_element(); //Test!
    
    return 0; //End program with 0
} //End of function.