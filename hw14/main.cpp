#include <iostream>
#include <stdexcept>

class DoublyLinkedList {
public:
    struct Node {
        int data;
        Node *prev;
        Node *next;

        explicit Node(int data) : data(data), prev(nullptr), next(nullptr) {}
    };

    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    ~DoublyLinkedList() {
        while (head) {
            Node *temp = head;
            head = head->next;
            delete temp;
        }
    }

    void insertFront(int data) {
        Node *newNode;
        try {
            newNode = new Node(data);
        } catch (std::runtime_error &e) {
            throw std::runtime_error("Memory allocation failed for new node.");
        }

        if (!head) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void deleteFront() {
        if (!head) {
            throw std::runtime_error("Attempt to delete from an empty list.");
        }

        Node *temp = head;
        if (head == tail) {
            head = tail = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr;
        }
        delete temp;
    }

    void display() {
        if (!head) {
            std::cout << "List is empty.\n";
            return;
        }

        Node *temp = head;
        while (temp) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        std::cout << "\n";
    }

private:
    Node *head;
    Node *tail;
};

int main() {
    DoublyLinkedList list;

    try {
        list.deleteFront();  // This should throw an exception
    } catch (const std::runtime_error &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    try {
        list.insertFront(10);
        list.insertFront(20);
        list.display();  // Should print: 20 10
        list.deleteFront();
        list.display();  // Should print: 10
    } catch (const std::runtime_error &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
