#include "card.h"
#include "cardManager.h"
#include <iostream>
#include <fstream>
#include <map>
using namespace std;

map<string, Card*> allclasses;
void loadData(string filename);
void printAllClasses();

int main(){
	int no;	// menu number 
    int quit = 0;

    loadData("classes.txt");
	string name;

	CardManager manager; 

	while(!quit){
		cout << "[Menu] 1.View 2.Add 3.Change 4.Sort 5.Search 6.Load 7.All 8.Save 9.Delete 0.Quit\n";
		cout << ">> Menu? > ";
		cin >> no;
        switch(no){
            case 1: 
			    cout << "> 1. All My Score Cards\n";
	    		manager.printAll();
                break;
            case 2:
			    cout << "> 2.Add a New Score Card\n";
    			manager.addCard();
                break;
		    case 3:
    			cout << "> 3.Change a Grade\n";
	    		manager.editCard();
                break;
		    case 4:
    			cout << "> 4.Sort by Code\n";
	    		manager.sortByCode();
		    	cout << "Sorted.\n";
                break;
            case 5:
            	cout << "> 5.Search a Class\n";
			    cout << ">> Enter class name > ";
			    cin >> name;
    			manager.findCards(name);
                break;
		    case 6:
    			cout << "> 6.Load My Cards\n";
	    		manager.loadCards("mycard.txt");
                break;
    		case 7:
    			cout << ">>7.All Classes\n";
                printAllClasses();
                break;
			case 8:
				cout << ">>8.Save\n";
				manager.saveClasses();
				break;
			case 9:
				cout << ">>9.Delete myclasse\n";
				manager.deleteClasses();
				break;
            case 0:
                quit = 1;
                break;
		}
	}
	return 0;
}

void loadData(string filename){
    string line, name, code;
    int credit, count=0;
	ifstream file(filename);
	while(!file.eof()){
        if(file.eof()) break;
		file >> code >> name >> credit;
        allclasses[code] = new Card(code, name, credit);
		count++;
	}
	file.close();
    cout << count << " classes are loaded.\n";
}

void printAllClasses(){
    map<string, Card*>::iterator iter;
    for (iter = allclasses.begin(); iter != allclasses.end(); ++iter) {
        cout << iter->second->toStringShort() << endl;
    }
}
