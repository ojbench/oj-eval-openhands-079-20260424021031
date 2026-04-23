
#include<iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

struct LinkedList {
    Node* head;
    
    void initialize() {
        int n;
        scanf("%d", &n);
        int *a = new int[n];
        for(int i = 0; i < n; i++) scanf("%d", &a[i]);
        
        // Create the linked list from the array
        if (n > 0) {
            head = new Node(a[0]);
            Node* current = head;
            for(int i = 1; i < n; i++) {
                current->next = new Node(a[i]);
                current = current->next;
            }
        } else {
            head = nullptr;
        }
        
        delete[] a;
    }
    
    void insert(int i, int x) {
        // Insert after the i-th node (1-indexed)
        if (i == 0) {
            // Insert at the beginning
            Node* newNode = new Node(x);
            newNode->next = head;
            head = newNode;
            return;
        }
        
        Node* current = head;
        for(int j = 1; j < i && current != nullptr; j++) {
            current = current->next;
        }
        
        if (current != nullptr) {
            Node* newNode = new Node(x);
            newNode->next = current->next;
            current->next = newNode;
        }
    }
    
    void erase(int i) {
        // Delete the i-th node (1-indexed)
        if (head == nullptr) return;
        
        if (i == 1) {
            // Delete the first node
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }
        
        Node* current = head;
        for(int j = 1; j < i-1 && current != nullptr; j++) {
            current = current->next;
        }
        
        if (current != nullptr && current->next != nullptr) {
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
        }
    }
    
    void swap() {
        // Swap odd and even positioned elements
        Node* current = head;
        while (current != nullptr && current->next != nullptr) {
            // Swap the data of current and current->next
            int temp = current->data;
            current->data = current->next->data;
            current->next->data = temp;
            
            // Move to the next pair (skip two nodes)
            current = current->next->next;
        }
    }
    
    void moveback(int i, int x) {
        // Move the first i elements back by x positions
        if (i <= 0 || x <= 0) return;
        
        // Count the total length of the list
        int len = 0;
        Node* current = head;
        while (current != nullptr) {
            len++;
            current = current->next;
        }
        
        if (i >= len) return; // Nothing to move
        
        // Find the i-th node and the node after it
        Node* i_node = head;
        for (int j = 1; j < i; j++) {
            i_node = i_node->next;
        }
        
        Node* after_i = i_node->next;
        
        // Find the (i+x)-th node and the node after it
        Node* i_plus_x_node = head;
        for (int j = 1; j < i + x; j++) {
            i_plus_x_node = i_plus_x_node->next;
        }
        
        Node* after_i_plus_x = i_plus_x_node->next;
        
        // Break the list at the i-th node
        i_node->next = nullptr;
        
        // If we're moving to the end
        if (after_i_plus_x == nullptr) {
            // Connect the end of the moved part to the beginning
            i_plus_x_node->next = head;
            // Set the new head to the node after the first i nodes
            head = after_i;
        } else {
            // Connect the end of the moved part to the beginning
            i_plus_x_node->next = head;
            // Connect the end of the first i nodes to the rest of the list
            i_node->next = after_i_plus_x;
            // Set the new head to the node after the first i nodes
            head = after_i;
        }
    }
    
    int query(int i) {
        // Return the i-th element (1-indexed)
        Node* current = head;
        for(int j = 1; j < i && current != nullptr; j++) {
            current = current->next;
        }
        
        if (current != nullptr) {
            return current->data;
        }
        return -1; // Should not happen with valid input
    }
    
    void printAll() {
        Node* current = head;
        while (current != nullptr) {
            printf("%d", current->data);
            if (current->next != nullptr) {
                printf(" ");
            }
            current = current->next;
        }
        printf("\n");
    }
    
    void ClearMemory() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    LinkedList List;
    int m, op, i, x;
    List.initialize();
    scanf("%d", &m);
    while(m--) {
        scanf("%d", &op);
        if(op == 1) {
            scanf("%d%d", &i, &x);
            List.insert(i, x);
        }
        else if(op == 2) {
            scanf("%d", &i);
            List.erase(i);
        }
        else if(op == 3) {
            List.swap();
        }
        else if(op == 4) {
            scanf("%d%d",&i, &x);
            List.moveback(i, x);
        }
        else if(op == 5) {
            scanf("%d", &i);
            printf("%d\n", List.query(i));
        }
        else if(op == 6) {
            List.printAll();
        }
    }
    List.ClearMemory();
    return 0;
}
