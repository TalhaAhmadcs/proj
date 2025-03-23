#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <string>
using namespace std;

// Node structure for linked list
struct Node {
    int id;
    string name;
    int level;
    bool inMatch;
    Node* next;

    Node(int id, string name, int level) : id(id), name(name), level(level), inMatch(false), next(nullptr) {}
};

// Linked List implementation
struct LinkedList {
    // Helper function to swap node data
    
	Node* head;
    LinkedList() : head(nullptr) {}
    void insert(int id, string name, int level);
    void swapp(Node* a, Node* b);
    Node* merge(Node* left, Node* right);
    void split(Node* source, Node** frontRef, Node** backRef);
    Node* mergeSort(Node* head);
    void bubbleUp(); //heap & prioirity queue
    Node* popTop();
    void display();
    bool isEmpty();
    void clear() ;
     void outtamatch();
};

struct MatchmakingSystem {

    LinkedList players; // Master list of players
    LinkedList priorityQueue; // For matchmaking
    LinkedList maxHeap; // For leaderboard
	
	void registerPlayer(int id, string name, int level);
	void loadPriorityQueue(int level);
	void loadMaxHeap();
	void findMatch(Node& loggedInPlayer);
	void displayLeaderboard();
	Node* getPlayerById(int id);
};

#endif

