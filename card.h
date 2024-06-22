#ifndef CARD_H
#define CARD_H

#include <iostream>
using namespace std;

class Card{
private:
    string code;
    string name;
    int credit;
    string grade;
    double score;
    
public:
    Card(string code, string name, int credit);
    Card(string code, string name, int credit, string grade);
    Card(Card* card, string grade);
    ~Card(){};
    void setGrade(string newgrade){grade = newgrade;}
    string getCode(){return code;};
    string getName(){return name;};
    int getCredit(){return credit;};
    double getScore(){return score;};
    string getGrade(){return grade;};
    string toString();
    string toStringShort();

    static bool cmpCode(Card* c1, Card* c2){
        return (c1->getCode() < c2->getCode()); 
    }
};
#endif