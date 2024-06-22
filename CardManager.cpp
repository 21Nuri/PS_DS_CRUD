#include "cardManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <ctime>

extern map<string, Card*> allclasses;
map<string, double> gradescoreCard = {
    {"A+",4.5},{"A0",4.0},{"B+",3.5},{"B0",3.0},{"C+",2.5},{"C0",2.0},{"D+",1.5},{"D0",1.0},{"F",0}
};


CardManager::~CardManager(){
    vector<Card*>::iterator iter;
    for (iter = myclasses.begin(); iter != myclasses.end(); ++iter) {
		delete (*iter);
	}
}

void CardManager::printAll(){
    int credit = 0; 
    double gpa = 0;
    cout << "Total " << myclasses.size() << " classes, " ;
    for (int i=0; i<myclasses.size(); i++){
        credit += myclasses[i]->getCredit();
        gpa += myclasses[i]->getCredit() * myclasses[i]->getScore();
    }
    gpa = gpa / (credit*1.0);
    cout << credit << " credit, GPA " << gpa << endl;
    for (int i=0; i<myclasses.size(); i++){
        cout << i+1 << " | " << myclasses[i]->toString() << endl;
    }
}

void CardManager::addCard(){
    string code, grade;
	cout << ">> Enter class code > ";
	cin >> code;
    for (int i=0; i<myclasses.size(); i++){
		if(myclasses[i]->getCode() == code){
            cout << "The Card of " << code << " already exists." << endl;
            return;
		}
	}
    if(allclasses.count(code) > 0){
        cout << allclasses[code]->toStringShort() << endl;
	    cout << ">> Enter grade > ";
	    cin >> grade;
        if(gradescoreCard.count(grade) < 1){
            cout << "Wrong grade!" << endl;
        }else{
            Card* new_card = new Card(allclasses[code], grade);
            myclasses.push_back(new_card);
            count++;
            total_credit += new_card->getCredit();
        }
    }else{
        cout << "No such class." << endl;
    }
}

void CardManager::editCard(){
	int no;
    string new_grade;
	cout << ">> Enter a Card number > ";
	cin >> no;
    cout << myclasses[no-1]->toString() << endl;
    cout << ">> Enter new grade > ";
    cin >> new_grade;
    myclasses[no-1]->setGrade(new_grade);
    cout << "Grade changed." << endl;	
}

void CardManager::sortByCode(){
    sort(myclasses.begin(), myclasses.end(), Card::cmpCode);
}

void CardManager::loadCards(string filename){
    string line, code, grade;
    int count=0;
	ifstream file(filename);
	while(!file.eof()){
        if(file.eof()) break;
		file >> code >> grade;
        Card* new_card = new Card(allclasses[code], grade);
        myclasses.push_back(new_card);
        count++;
        total_credit += new_card->getCredit();
	}
	file.close();
    cout << count << " classes are loaded.\n";
}

void CardManager::findCards(string name){
	int found = 0;
	cout << "Searching keyword: " << name << endl;
    for (int i=0; i<myclasses.size(); i++){
		if(myclasses[i]->getName().find(name) != string::npos){
			found++;
            cout << i+1 << " | " << myclasses[i]->toString() << endl;
		}
	}
	cout << count << " classes found.\n";
}

void CardManager::saveClasses(){
    time_t timer;
    timer = time(NULL);
    struct tm* t = localtime(&timer);
    int credit = 0; 
    double gpa = 0;
	ofstream file1("mycard.txt");
    for(int i = 0; i<myclasses.size(); i++){
        if(i == myclasses.size()-1) file1 << myclasses[i]->getCode() << " " << myclasses[i]->getGrade();
        else file1 << myclasses[i]->getCode() << " " << myclasses[i]->getGrade() << endl;
    }
	file1.close();

    ofstream file2("report.txt");
    file2 << "Total " << myclasses.size() << " classes, " ;
    for (int i=0; i<myclasses.size(); i++){
        credit += myclasses[i]->getCredit();
        gpa += myclasses[i]->getCredit() * myclasses[i]->getScore();
    }
    gpa = gpa / (credit*1.0);
    file2 << credit << " credit, GPA " << gpa << endl;
    for (int i=0; i<myclasses.size(); i++){
        file2 << i+1 << " | " << myclasses[i]->toString() << endl;
    }
    file2 << t->tm_year + 1900 << ". " <<  t->tm_mon + 1 << ". " << t->tm_mday << ". " << t->tm_hour << ":" << t->tm_min << ":" << t->tm_sec << endl ;
	file2.close();
    cout << "mycard.txt and report.txt saved." << endl;
}

void CardManager::deleteClasses(){
    remove("mycard.txt");
}