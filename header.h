#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <string>

using namespace std;

const int MAX_Kasus = 10;
const int MAX_STACK = 100;

struct Firma;
typedef struct Firma* adrFirma;

struct Kasus;
typedef struct Kasus* adrKasus;

struct Firma {
    int id;
    string name;
    int Kasus[10];
    int KasusCount;
    adrFirma prev;
    adrFirma next;
};

struct dllFirma {
    adrFirma head;
    adrFirma tail;
    adrFirma cursor;
};

struct Kasus {
    int id;
    string name;
    adrKasus next;
};

struct dllKasus {
    adrKasus head;
};

struct Operation {
    string type;
    int FirmaId;
    string FirmaName;
    int Kasus[10];
    int KasusCount;
};

struct StackOperation {
    Operation items[100];
    int top;
};

void createStack(StackOperation &s);
bool isEmpty(StackOperation &s);
bool isFull(StackOperation &s);
void push(StackOperation &s, Operation &op);
Operation pop(StackOperation &s);
Operation getTop(StackOperation &s);

void createDllFirma(dllFirma &dllF);
void createDllKasus(dllKasus &dllK);

void insertLastFirma(dllFirma &dllF, int id, string &name);
void deleteFirma(dllFirma &dllF, adrFirma Firma);

void insertLastKasus(dllKasus &dllK, int id, string &name);

void moveCursorRight(dllFirma &dllF);
void moveCursorLeft(dllFirma &dllF);

void display(dllFirma &dllF, dllKasus &dllK);
void displayKasus(dllKasus &dllK);

bool addKasusUsingCursor(dllFirma &dllF, dllKasus &dllK, int KasusId);

void undo(dllFirma &dllF, StackOperation &undoStack, StackOperation &redoStack);
void redo(dllFirma &dllF, StackOperation &undoStack, StackOperation &redoStack);

void displayMenu();

bool searchKasus(dllKasus &dllK, int KasusId);
string getKasusName(dllKasus &dllK, int KasusId);

void deleteKasus(dllKasus &dllK, dllFirma &dllF, int KasusId);
void removeKasusFromCursor(dllFirma &dllF, int KasusId);

#endif
