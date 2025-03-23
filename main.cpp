#include <iostream>
#include "mrs.h"
using namespace std;

int main() {
    MatchmakingSystem system;
    Node* loggedInPlayer = nullptr;
    system.registerPlayer(1,"Saad",5);
	system.registerPlayer(3,"Ali",6);
	system.registerPlayer(7,"Talha",5);
	system.registerPlayer(8,"Balti",6);
	system.registerPlayer(9,"Kami",6);
	system.registerPlayer(12,"Rizi",9);
	system.registerPlayer(16,"Kazama",5);
	system.registerPlayer(13,"King",5);
	system.registerPlayer(15,"Jin",9);
    int idCounter = 17;

    while (true) {
        if (!loggedInPlayer) {
            cout << "\nWelcome! Login to Get Started\n";
            cout << "1. Login\n2. Register\n3. Quit\n";
            int choice;
            cin >> choice;

            if (choice == 1) {
                cout << "Enter ID: ";
                int id;
                cin >> id;
                loggedInPlayer = system.getPlayerById(id);
                if (loggedInPlayer) {
                    cout << "Welcome back, " << loggedInPlayer->name << "!\n";
                    system.loadPriorityQueue(loggedInPlayer->level);
                } else {
                    cout << "Player not found.\n";
                }
            } else if (choice == 2) {
                cout << "Enter Name: ";
                string name;
                cin >> name;
                cout << "Enter Level (1-10): ";
                int level;
                cin >> level;
                system.registerPlayer(idCounter++, name, level);
            } else if (choice == 3) {
                cout << "Goodbye!\n";
                break;
            } else {
                cout << "Invalid choice.\n";
            }
        } else {
            cout << "\nMain Menu\n";
            cout << "ID: " << loggedInPlayer->id << "  Name: " << loggedInPlayer->name << "  Level: " << loggedInPlayer->level << "\n";
            cout << "1. Start Game\n2. View Leaderboard\n3. Quit\n";
            int choice;
            cin >> choice;

            if (choice == 1) {
                //system.loadPriorityQueue(loggedInPlayer->level);
                system.findMatch(*loggedInPlayer);
            } else if (choice == 2) {
                system.loadMaxHeap();
                system.displayLeaderboard();
            } else if (choice == 3) {
                cout << "Goodbye, " << loggedInPlayer->name << "!\n";
                loggedInPlayer = nullptr;
            } else if (choice==4){ //get players outta queue
            	system.players.outtamatch();
            	system.priorityQueue.clear();
            	system.loadPriorityQueue(loggedInPlayer->level);
			} else {
                cout << "Invalid choice.\n";
            }
        }
    }

    return 0;
}

















///////////////////////////////
//
//#include <graphics.h>
//#include <iostream>
//#include <cstring>
//#include "mrs.h"
//
//using namespace std;
//
//// Constants for screen dimensions
//const int SCREEN_WIDTH = 800;
//const int SCREEN_HEIGHT = 600;
//
//// Function to display text on the screen
//void drawText(int x, int y, const char *text, int color) {
//    setcolor(color);
//    outtextxy(x, y, const_cast<char *>(text));
//}
//
//// Function to create a button
//void createButton(int x1, int y1, int x2, int y2, const char *label, int color) {
//    setfillstyle(SOLID_FILL, color);
//    bar(x1, y1, x2, y2);
//    setbkcolor(color);
//    drawText((x1 + x2) / 2 - 50, (y1 + y2) / 2 - 5, label, WHITE);
//}
//
//// Function to check if a button is clicked
//bool isButtonClicked(int mouseX, int mouseY, int x1, int y1, int x2, int y2) {
//    return (mouseX >= x1 && mouseX <= x2 && mouseY >= y1 && mouseY <= y2);
//}
//
//// Function to get user input
//void getInput(int x, int y, char *buffer, int maxLength) {
//    char key;
//    int i = 0;
//    while (true) {
//        key = getch();
//        if (key == 13) { // Enter key
//            buffer[i] = '\0';
//            break;
//        } else if (key == 8 && i > 0) { // Backspace
//            i--;
//            buffer[i] = '\0';
//            setfillstyle(SOLID_FILL, BLACK);
//            bar(x, y, x + maxLength * 10, y + 20);
//            drawText(x, y, buffer, WHITE);
//        } else if (key >= 32 && key <= 126 && i < maxLength - 1) {
//            buffer[i++] = key;
//            buffer[i] = '\0';
//            drawText(x, y, buffer, WHITE);
//        }
//    }
//}
//
//// Main function
//int main() {
//    // Initialize graphics
//    int gd = DETECT, gm;
//    initgraph(&gd, &gm, (char *)"");
//
//    MatchmakingSystem system;
//    Node *loggedInPlayer = nullptr;
//    int idCounter = 17;
//
//    // Pre-register players
//    system.registerPlayer(1, "Saad", 5);
//    system.registerPlayer(3, "Ali", 6);
//    system.registerPlayer(7, "Talha", 5);
//    system.registerPlayer(8, "Balti", 6);
//    system.registerPlayer(9, "Kami", 6);
//
//    while (true) {
//        // Clear the screen
//        setfillstyle(SOLID_FILL, BLACK);
//        bar(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
//
//        if (!loggedInPlayer) {
//            drawText(50, 20, "--- Welcome! Login to Get Started ---", WHITE);
//
//            createButton(100, 100, 300, 150, "1. Login", BLUE);
//            createButton(100, 180, 300, 230, "2. Register", GREEN);
//            createButton(100, 260, 300, 310, "3. Quit", RED);
//
//            // Wait for mouse click
//            int mouseX, mouseY;
//            while (!ismouseclick(WM_LBUTTONDOWN)) {}
//            getmouseclick(WM_LBUTTONDOWN, mouseX, mouseY);
//
//            if (isButtonClicked(mouseX, mouseY, 100, 100, 300, 150)) {
//                // Login
//                char buffer[50];
//                drawText(50, 350, "Enter ID: ", WHITE);
//                getInput(150, 350, buffer, 50);
//                int id = atoi(buffer);
//                loggedInPlayer = system.getPlayerById(id);
//                if (loggedInPlayer) {
//                    drawText(50, 400, "Login successful!", GREEN);
//                    delay(2000);
//                } else {
//                    drawText(50, 400, "Player not found.", RED);
//                    delay(2000);
//                }
//            } else if (isButtonClicked(mouseX, mouseY, 100, 180, 300, 230)) {
//                // Register
//                char name[50];
//                drawText(50, 350, "Enter Name: ", WHITE);
//                getInput(150, 350, name, 50);
//
//                char buffer[10];
//                drawText(50, 400, "Enter Level (1-10): ", WHITE);
//                getInput(250, 400, buffer, 10);
//                int level = atoi(buffer);
//
//                system.registerPlayer(idCounter++, name, level);
//                drawText(50, 450, "Player registered successfully!", GREEN);
//                delay(2000);
//            } else if (isButtonClicked(mouseX, mouseY, 100, 260, 300, 310)) {
//                // Quit
//                drawText(50, 500, "Goodbye!", RED);
//                delay(2000);
//                break;
//            }
//        } else {
//            // Main Menu
//            char welcomeMsg[100];
//            sprintf(welcomeMsg, "ID: %d Name: %s Level: %d", loggedInPlayer->id, loggedInPlayer->name, loggedInPlayer->level);
//            drawText(50, 20, welcomeMsg, WHITE);
//
//            createButton(100, 100, 300, 150, "1. Start Game", BLUE);
//            createButton(100, 180, 300, 230, "2. View Leaderboard", GREEN);
//            createButton(100, 260, 300, 310, "3. Logout", RED);
//
//            int mouseX, mouseY;
//            while (!ismouseclick(WM_LBUTTONDOWN)) {}
//            getmouseclick(WM_LBUTTONDOWN, mouseX, mouseY);
//
//            if (isButtonClicked(mouseX, mouseY, 100, 100, 300, 150)) {
//                // Start Game
//                system.findMatch(*loggedInPlayer);
//                drawText(50, 350, "Matchmaking started!", GREEN);
//                delay(2000);
//            } else if (isButtonClicked(mouseX, mouseY, 100, 180, 300, 230)) {
//                // View Leaderboard
//                system.loadMaxHeap();
//                cleardevice();
//                drawText(50, 20, "Leaderboard:", WHITE);
//                system.displayLeaderboard();
//                delay(5000);
//            } else if (isButtonClicked(mouseX, mouseY, 100, 260, 300, 310)) {
//                // Logout
//                drawText(50, 350, "Logging out...", RED);
//                delay(2000);
//                loggedInPlayer = nullptr;
//            }
//        }
//    }
//
//    closegraph();
//    return 0;
//}
