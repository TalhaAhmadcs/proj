#include <graphics.h>
#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;

const int NODE_RADIUS = 20; // Radius of each node
const int X_SPACING = 90;   // Horizontal spacing between nodes
const int Y_SPACING = 100;  // Vertical spacing between levels

struct Movie {
    int movieID;
    char movieName[100];
    char genre[100];
    float imbdRating;
    Movie* lchild;
    Movie* rchild;

    Movie(int id, const char* name, const char* gen, float rating)
        : movieID(id), imbdRating(rating), lchild(nullptr), rchild(nullptr) {
        strncpy(movieName, name, sizeof(movieName) - 1);
        movieName[sizeof(movieName) - 1] = '\0';
        strncpy(genre, gen, sizeof(genre) - 1);
        genre[sizeof(genre) - 1] = '\0';
    }
};

// Function prototypes
void displayTree(Movie* root, int x, int y, int xOffset);
void drawNode(int x, int y, const char* movieID, const char* movieName);
void insert(Movie*& root, Movie* node);

// Main function
int main() {
    // Initialize graphics
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    // Hardcoded tree of 30 nodes
    Movie* root = nullptr;
    insert(root, new Movie(50, "Movie A", "Action", 8.5));
    insert(root, new Movie(30, "Movie B", "Comedy", 7.2));
    insert(root, new Movie(70, "Movie C", "Drama", 9.1));
    insert(root, new Movie(20, "Movie D", "Horror", 6.8));
    insert(root, new Movie(40, "Movie E", "Sci-Fi", 8.0));
    insert(root, new Movie(60, "Movie F", "Romance", 7.9));
    insert(root, new Movie(80, "Movie G", "Thriller", 8.3));
    insert(root, new Movie(10, "Movie H", "Adventure", 7.0));
    insert(root, new Movie(25, "Movie I", "Fantasy", 6.5));
    insert(root, new Movie(35, "Movie J", "Animation", 8.2));
    insert(root, new Movie(45, "Movie K", "Crime", 9.0));
    insert(root, new Movie(55, "Movie L", "Mystery", 7.7));
    insert(root, new Movie(65, "Movie M", "Biography", 8.1));
    insert(root, new Movie(75, "Movie N", "Documentary", 7.8));
    insert(root, new Movie(85, "Movie O", "Musical", 8.6));
    insert(root, new Movie(15, "Movie P", "Fantasy", 6.9));
    insert(root, new Movie(28, "Movie Q", "Action", 7.4));
    insert(root, new Movie(32, "Movie R", "Horror", 6.6));
    insert(root, new Movie(38, "Movie S", "Romance", 7.5));
    insert(root, new Movie(42, "Movie T", "Sci-Fi", 8.1));
    insert(root, new Movie(48, "Movie U", "Drama", 8.2));
    insert(root, new Movie(52, "Movie V", "Thriller", 7.3));
    insert(root, new Movie(58, "Movie W", "Crime", 7.8));
    insert(root, new Movie(62, "Movie X", "Animation", 7.6));
    insert(root, new Movie(68, "Movie Y", "Biography", 8.3));
    insert(root, new Movie(72, "Movie Z", "Mystery", 8.4));
    insert(root, new Movie(77, "Movie AA", "Adventure", 7.9));
    insert(root, new Movie(82, "Movie AB", "Fantasy", 7.5));
    insert(root, new Movie(90, "Movie AC", "Action", 8.7));
    insert(root, new Movie(48, "Movie U", "Drama", 8.2));
    insert(root, new Movie(52, "Movie V", "Thriller", 7.3));
    insert(root, new Movie(58, "Movie W", "Crime", 7.8));
    insert(root, new Movie(62, "Movie X", "Animation", 7.6));
    insert(root, new Movie(68, "Movie Y", "Biography", 8.3));
    insert(root, new Movie(72, "Movie Z", "Mystery", 8.4));
    insert(root, new Movie(77, "Movie AA", "Adventure", 7.9));
    insert(root, new Movie(82, "Movie AB", "Fantasy", 7.5));
    insert(root, new Movie(90, "Movie AC", "Action", 8.7));

    // Display tree
    displayTree(root, getmaxx() / 2, 50, getmaxx() / 4);

    // Wait for a key press and close graphics
    getch();
    closegraph();

    return 0;
}

// Function to display the tree
void displayTree(Movie* root, int x, int y, int xOffset) {
    if (root == nullptr)
        return;

    char movieID[20];
    snprintf(movieID, sizeof(movieID), "%d", root->movieID);

    // Draw the current node
    drawNode(x, y, movieID, root->movieName);

    // Draw left child
    if (root->lchild != nullptr) {
        line(x, y + NODE_RADIUS, x - xOffset, y + Y_SPACING - NODE_RADIUS);
        displayTree(root->lchild, x - xOffset, y + Y_SPACING, xOffset / 2);
    }

    // Draw right child
    if (root->rchild != nullptr) {
        line(x, y + NODE_RADIUS, x + xOffset, y + Y_SPACING - NODE_RADIUS);
        displayTree(root->rchild, x + xOffset, y + Y_SPACING, xOffset / 2);
    }
}

// Function to draw a node
// Function to draw a node with both movieID and movieName
void drawNode(int x, int y, const char* movieID, const char* movieName) {
    setcolor(WHITE);
    circle(x, y, NODE_RADIUS);
    setfillstyle(SOLID_FILL, BLUE);
    floodfill(x, y, WHITE);

    setcolor(WHITE);
    setbkcolor(BLUE);

    // Create two buffers for movieID and movieName
    char idBuffer[50]; // Buffer for movieID
    char nameBuffer[100]; // Buffer for movieName

    // Copy the movieID and movieName to respective buffers
    strncpy(idBuffer, movieID, sizeof(idBuffer) - 1);
    idBuffer[sizeof(idBuffer) - 1] = '\0'; // Ensure null termination

    strncpy(nameBuffer, movieName, sizeof(nameBuffer) - 1);
    nameBuffer[sizeof(nameBuffer) - 1] = '\0'; // Ensure null termination

    // Draw the movieID above the node
    outtextxy(x - textwidth(idBuffer) / 2, y - textheight(idBuffer) / 2 - NODE_RADIUS / 2, idBuffer);

    // Draw the movieName below the node
    outtextxy(x - textwidth(nameBuffer) / 2, y + NODE_RADIUS / 2, nameBuffer);
}



// Function to insert a node into the BST
void insert(Movie*& root, Movie* node) {
    if (root == nullptr) {
        root = node;
        return;
    }

    if (node->movieID < root->movieID)
        insert(root->lchild, node);
    else
        insert(root->rchild, node);
}

