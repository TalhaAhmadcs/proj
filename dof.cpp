#include "mrs.h"
//#include<stdio.h>
//#include<graphics.h>

void LinkedList::insert(int id, string name, int level) {
    Node* newNode = new Node(id, name, level);
    if (!head) {
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void LinkedList::swapp(Node* a, Node* b) {
	swap(a->name,b->name);
	swap(a->id,b->id);
	swap(a->level,b->level);
	swap(a->inMatch,b->inMatch);
}    

void LinkedList::outtamatch() {
    Node* temp = head;
    while (temp) {
        temp->inMatch=false;
        temp = temp->next;
    }
}

Node* LinkedList::merge(Node* left, Node* right) {
    if (!left) return right;
    if (!right) return left;

    if (left->level > right->level) { // Descending order
        left->next = merge(left->next, right);
        return left;
    } else {
        right->next = merge(left, right->next);
        return right;
    }
}

void LinkedList::split(Node* source, Node** frontRef, Node** backRef) {
    Node* slow = source;
    Node* fast = source->next;

    // Fast advances two nodes, slow advances one node
    while (fast) {
        fast = fast->next;
        if (fast) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    // Split the list
    *frontRef = source; //head
    *backRef = slow->next; //next of mid
    slow->next = nullptr;
}


Node* LinkedList::mergeSort(Node* head) {
    if (!head || !head->next) return head;

    Node* left = nullptr;
    Node* right = nullptr;

    // Split the list into two halves
    split(head, &left, &right);

    // Sort each half
    left = mergeSort(left);
    right = mergeSort(right);

    // Merge the sorted halves
    return merge(left, right);
}

void LinkedList::bubbleUp() {
    head = mergeSort(head);
}

Node* LinkedList::popTop() {
    if (!head) return nullptr;
    Node* top = head;
    head = head->next;
    top->next = nullptr;
    return top;
}

void LinkedList::display() {
	
	 Node* temp = head;
	while (temp) {
	         cout << temp->name << " (Level: " << temp->level << ")\n";
			 temp = temp->next;
     }
	 }
	 
//    // Initialize the graphics window
//    char ep[]="";
//    char tt[]="Leadeerboard";
//    int gd = DETECT, gm;
//    initgraph(&gd, &gm, ep);
//
//    // Set the title for the leaderboard
//    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2); // Set font and size
//    outtextxy(200, 50, tt); // Title position and text
//
//    // Display the leaderboard entries
//    Node* temp = head;
//    int y = 100; // Starting y-coordinate for the entries
//    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1); // Set smaller font for the entries
//
//    while (temp) {
//        char buffer[100];
//        sprintf(buffer, "%s (Level: %d)", temp->name.c_str(), temp->level); // Format the text
//        outtextxy(200, y, buffer); // Display text at (x, y)
//        y += 30; // Move to the next line
//        temp = temp->next;
//    }
//
//    // Hold the screen to view the leaderboard
//    getch();
//
//    // Close the graphics window
//    closegraph();

// Check if the list is empty
bool LinkedList::isEmpty() {
    return head == nullptr;
}

// Clear the list
void LinkedList::clear() {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}


///////////////////// Matchmaking Functions ///////////////////////////////////
///////////////////// Matchmaking Functions ///////////////////////////////////
///////////////////// Matchmaking Functions ///////////////////////////////////


    // Register a player
    void MatchmakingSystem::registerPlayer(int id, string name, int level) {
        players.insert(id, name, level);
        //cout << "Player " << name << " registered successfully!\n";
    }

    // Load players into the priority queue (up to a specific level)
    void MatchmakingSystem::loadPriorityQueue(int level) {
        priorityQueue.clear();
        Node* temp = players.head;
        while (temp) {
            if (temp->level <= level) {
                priorityQueue.insert(temp->id, temp->name, temp->level);
                priorityQueue.bubbleUp();
            }
            temp = temp->next;
        }
    }

    // Load players into the max heap for leaderboard
    void MatchmakingSystem::loadMaxHeap() {
        maxHeap.clear();
        Node* temp = players.head;
        while (temp) {
            maxHeap.insert(temp->id, temp->name, temp->level);
            maxHeap.bubbleUp();
            temp = temp->next;
        }
    }

    // Find a match for the logged-in player
    void MatchmakingSystem::findMatch(Node& loggedInPlayer) {
        if (priorityQueue.isEmpty()) {
            cout << "No players available for matchmaking.\n";
            return;
        }

        Node* candidate = priorityQueue.popTop();
        while (candidate) {
            if (candidate->level == loggedInPlayer.level && candidate->id != loggedInPlayer.id && !candidate->inMatch) {
                cout << "Match Found: " << loggedInPlayer.name << " vs " << candidate->name << "\n";
                candidate->inMatch=true;
                return;
            }
            candidate = priorityQueue.popTop();
        }

        cout << "No match found for " << loggedInPlayer.name << ".\n";
    }

    // Display the leaderboard
    void MatchmakingSystem::displayLeaderboard() {
        if (maxHeap.isEmpty()) {
            cout << "No players available for leaderboard.\n";
            return;
        }

        cout << "\nLeaderboard (Sorted by Level):\n";
        maxHeap.display();
    }

    // Get player by ID (for login)
    Node* MatchmakingSystem::getPlayerById(int id) {
        Node* temp = players.head;
        while (temp) {
            if (temp->id == id) return temp;
            temp = temp->next;
        }
        return nullptr;
    }