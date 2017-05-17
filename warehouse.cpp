#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <iomanip>

/**
 * TODO
 * 1. add description header
 * 2. fix add item x/y position check/add dont allow 0/0 (x, y > 0)
 * 3. add warehouse positions representation print into file
 * 4. add functions description
 */

using namespace std;
int state = 0;
struct Item {
    string primary;
    string secondary;

    int x;
    int y;

    Item(string name = "", string desc = "", int x = -1, int y = -1) {
        Item::primary = name;
        Item::secondary = desc;
        Item::x = x;
        Item::y = y;
    }

    string get(int key = 0) {
        if(key == 1) {
            return Item::primary;
        }

        if(key == 2) {
            return Item::secondary;
        }

        return "";
    }
};

bool isInited = false;
int width;
int height;
vector<vector<bool> > storage;

//delete this code for a release version
vector<Item> data = {
        Item ("test", "test", 0, 0),
        Item ("test1", "test2", 0, 1),
        Item ("test3", "test3", 3, 6),
};

void showState();
void showMenu();
void addItem();
void findItem(int);
void listItems();
void deleteItem();
void writeData();
void showStorage();
bool setDimensions();

int main() {
    isInited = setDimensions();

    while(!isInited) {
        isInited = setDimensions();
    }
    showState();
    return 0;
}

/**
 * basic state logic
 */
void showState() {
    switch(state) {
        case 8:
            cout << "Good by!";
            exit(1);
            break;
        case 7:
            showStorage();
            break;
        case 6:
            writeData();
            break;
        case 5:
            listItems();
            break;
        case 4:
            deleteItem();
            break;
        case 3:
            findItem(1);
            break;
        case 2:
            findItem(0);
            break;
        case 1:
            addItem();
        case 0:
        default:
            showMenu();
            break;
    }
}

/**
 * shows menu
 */
void showMenu() {
    cout << "1. Add Item\n";
    cout << "2. Find by primary key\n";
    cout << "3. Find by secondary key\n";
    cout << "4. Delete Item\n";
    cout << "5. List Items\n";
    cout << "6. Write data into file\n";
    cout << "7. Show storage\n";
    cout << "8. Exit\n\n";


    cout << "What will we do? ";
    cin >> state;
    cout << "\n\n";
    showState();
}

/**
 * sets initial dimensions of the storage
 * @return
 */
bool setDimensions() {
    cout << "Enter dimensions (width height): ";
    cin >> width >> height;
    if(width > 0 && height > 0) {
        //fill the storage variable with empty slots
        for(int row=0;row<height;row++) {
            vector<bool> rowArr;
            for (int col=0;col<width; col++) {
                rowArr.push_back(false);
            }

            storage.push_back(rowArr);

        }

        //delete this code for a release version
        storage[0][0] = true;
        storage[0][1] = true;
        storage[3][6] = true;
        return true;
    }
    return false;
}

/**
 * displays storage state to the screen;
 */
void showStorage() {
    cout << left << setw(5) << " ";
    for (int col=0;col<width; col++) {
        cout << "_";
    }
    cout << endl;
    for(int row=0;row<height;row++) {
        cout << left << setw(4) << (row+1) << "|";

        for (int col=0;col<width; col++) {
            if(storage[row][col]) {
                cout << "X";
            } else {
                cout << " ";
            }
        }
        cout << "|\n";
    }

    cout << left << setw(5) << " ";
    for (int col=0;col<width; col++) {
        cout << "_";
    }

    cout << endl << endl;

    state = 0;
    showState();
}

/**
 * deletes item
 */
void deleteItem() {
    int index;
    cout << "Enter delete index: ";
    cin >> index;

    //clear storage array
    storage[data[index-1].x][data[index-1].y] = false;

    data.erase (data.begin()+(index-1));

    state = 0;
    showState();
}

/**
 * gets newItem data from input, returns false if had errors
 * @param newItem
 * @return
 */
bool getItemProps(Item & newItem) {

    //if name||descrition were not specified(first time add)
    if(newItem.primary == "") {
        cout << "Enter name: ";
        cin.ignore();
        getline(cin, newItem.primary);
    }

    if(newItem.secondary == "") {
        cout << "Enter description: ";
        cin.ignore();
        getline(cin, newItem.secondary);
    }

    cout << "Enter x position: ";
    cin >> newItem.x;
    cout << "Enter y position: ";
    cin >> newItem.y;

    if(newItem.x < 0 || newItem.y < 0 || storage[newItem.x][newItem.y]) {
        return false;
    }
    return true;
}

/**
 * upper level function of addItem, generates x, y, interacts with user;
 */
void addItem() {
    Item newItem;

    bool itemCreated = getItemProps(newItem);
    //if the spot is taken then....
    while(!itemCreated) {
        char yn;
        int isYes = -1;
        //ask if user wants to auto generate new coordinates
        do {
            cout << "This position is taken, would you like to auto set position?(y/n)" << endl;
            cin >> yn;
            if(yn != 'y' || yn != 'Y') {
                isYes = 1;
            }
            if(yn != 'n' || yn != 'N') {
                isYes = 0;
            }
        } while (isYes < 0);

        if(isYes > -1) {
            //if he does
            for(int row=0;row<width && !itemCreated;row++) {

                for (int col=0;col<height && !itemCreated; col++) {
                    if(!storage[row][col]) {
                        newItem.x = row;
                        newItem.y = col;
                        itemCreated = true;
                    }
                }
            }
        } else {
            itemCreated = getItemProps(newItem);
        }
    }

    //Insert item to data array
    data.push_back(newItem);
    //dont forget to update the dimensions array
    storage[newItem.x][newItem.y] = true;

    cout << "Created element index is " << data.size() << endl << endl;
    state = 0;
    showState();
}

/**
 * shows items on the screen
 */
void listItems() {
    cout << "\n\n";

    cout << left << setw(10)
         << "Index" << setw(20)
         << "Primary" << setw(30)
         << "Secondary" << setw(10)
         << "X" << setw(10)
         << "Y" << endl;

    for (int i = 0; i < data.size(); i++) {
        cout << left << setw(10)
             << i+1 << setw(20)
             << data[i].primary << setw(30)
             << data[i].secondary << setw(10)
             << data[i].x << setw(10)
             << data[i].y << endl;
    }

    cout << "\n\n";

    state = 0;
    showState();
}

/**
 * serches for an item by name/desc, prints result into the screen
 * @param key
 */
void findItem(int key) {
    int index = key + 1;
    vector<Item> result;
    string searchStr;
    cout << "Enter search value: ";
    cin >> searchStr;
    for(int i=0;i<data.size();i++) {
        string value = data[i].get(index);
        if(value.find(searchStr) != -1) {
            result.push_back(data[i]);
        }
    }

    cout << "\n\n";

    cout << left << setw(10)
         << "Index" << setw(20)
         << "Primary" << setw(30)
         << "Secondary" << setw(10)
         << "X" << setw(10)
         << "Y" << endl;

    for (int i = 0; i < data.size(); i++) {
        cout << left << setw(10)
             << i+1 << setw(20)
             << result[i].primary << setw(30)
             << result[i].secondary << setw(10)
             << result[i].x << setw(10)
             << result[i].y << endl;
    }

    cout << "\n\n";

    state = 0;
    showState();
}

/**
 * write data into file
 */
void writeData() {
    ofstream outfile;
    string fileName;

    cout << "Enter file name: ";
    cin >> fileName;

    while (fileName.length() < 5 || fileName.substr(fileName.length()-4, 4) != ".txt") {
        cout << "File should be in .txt: ";
        cin >> fileName;
    }

    outfile.open(fileName);

    if (!outfile.is_open()) {
        cout << "Error. Couldn't create file " << fileName << endl;
        state = 0;
        showState();
    }

    outfile << left << setw(10)
            << "Index" << setw(20)
            << "Primary" << setw(30)
            << "Secondary" << setw(10)
            << "X" << setw(10)
            << "Y" << endl;

    for (int i = 0; i < data.size(); i++) {
        outfile << left << setw(10)
                << i+1 << setw(20)
                << data[i].primary << setw(30)
                << data[i].secondary << setw(10)
                << data[i].x << setw(10)
                << data[i].y << endl;
    }

    outfile.close();

    state = 0;
    showState();
}
