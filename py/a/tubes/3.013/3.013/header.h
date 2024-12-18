#ifndef HEADER_H
#define HEADER_H

#include <iostream>

using namespace std;

#include <iostream>
#include <stack>
#include <string>

using namespace std;

// Konstanta untuk kapasitas maksimum kasus dalam array
const int MAX_CASES = 10;

struct Firm;
typedef struct Firm* adrFirm;

struct Case;
typedef struct Case* adrCase;

// Struktur untuk doubly linked list dari firma hukum
struct Firm {
    int id;                          // ID firma
    string name;                     // Nama firma
    int cases[MAX_CASES];            // Array statik untuk ID kasus
    int caseCount;                   // Jumlah kasus yang terdaftar
    adrFirm prev;                      // Pointer ke elemen sebelumnya
    adrFirm next;                      // Pointer ke elemen berikutnya
};

struct dllFirm {
    adrFirm head;                      // Pointer ke awal DLL
    adrFirm tail;                      // Pointer ke akhir DLL
    adrFirm cursor;                    // Pointer ke elemen saat ini (cursor)
};

struct Case {
    int id;                          // ID kasus
    string name;                     // Nama kasus
    adrCase next;                      // Pointer ke elemen berikutnya
};

struct dllCase {
    adrCase head;                      // Pointer ke awal DLL kasus
};

struct Operation {
    string type;                     // "insert" atau "delete"
    int firmId;                      // ID firma terkait
    string firmName;                 // Nama firma terkait
    int cases[MAX_CASES];            // Array statik ID kasus terkait
    int caseCount;                   // Jumlah kasus terkait
};

typedef stack<Operation> StackOperation;

// Deklarasi fungsi
void createDllFirm(dllFirm &dllF);
void createDllCase(dllCase &dllC);
void insertLastFirm(dllFirm &dllF, int id, const string &name);
void deleteFirm(dllFirm &dllF, adrFirm firm);
void insertLastCase(dllCase &dllC, int id, const string &name);
void moveCursorToNext(dllFirm &dllF);
void moveCursorToPrev(dllFirm &dllF);
void display(const dllFirm &dllF, const dllCase &dllC);
void displayCases(const dllCase &dllC);
bool addCaseUsingCursor(dllFirm &dllF, dllCase &dllC, int caseId);
void undo(dllFirm &dllF, StackOperation &undoStack, StackOperation &redoStack);
void redo(dllFirm &dllF, StackOperation &undoStack, StackOperation &redoStack);
void displayMenu();
bool caseExists(const dllCase &dllC, int caseId);
string getCaseName(const dllCase &dllC, int caseId);
void deleteCase(dllCase &dllC, int caseId);
void removeCaseFromCursor(dllFirm &dllF, int caseId);

#endif
