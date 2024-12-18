#include "header.h"

int main() {
    const int MAX_CASES = 100; // Define maximum size for cases array
    dllFirm firmList;
    dllCase caseList;
    StackOperation undoStack, redoStack;

    createDllFirm(firmList);
    createDllCase(caseList);

    // Sample Cases
    insertLastCase(caseList, 101, "Pembunuhan Rafif Radithya oleh Indra");
    insertLastCase(caseList, 102, "Pemalsuan Identitas oleh Fauzan");
    insertLastCase(caseList, 103, "Pembunuhan di Bojong Soang");

    bool running = true;
    int choice;

    while (running) {
        displayMenu();
        cin >> choice;

        if (choice == 1) { // Add Case to Firm using cursor
            int caseId;
            cout << "Masukkan ID Kasus yang Ingin di Tambahkan ke Cursor: ";
            cin >> caseId;
            addCaseUsingCursor(firmList, caseList, caseId);
        } else if (choice == 2) { // Add Firm
            int firmId;
            string firmName;
            cout << "Masukkan ID Firma: ";
            cin >> firmId;
            cout << "Masukkan Nama Firma: ";
            cin >> firmName;
            insertLastFirm(firmList, firmId, firmName);

            Operation op = {"insert", firmId, firmName, {}, 0};
            undoStack.push(op);
            while (!redoStack.empty()) redoStack.pop();

            cout << "Firma berhasil di Tambah." << endl;
        } else if (choice == 3) { // Delete Firm at cursor
            if (firmList.cursor) {
                Operation op = {"delete", firmList.cursor->id, firmList.cursor->name, {}, firmList.cursor->caseCount};

                for (int i = 0; i < firmList.cursor->caseCount; i++) {
                    op.cases[i] = firmList.cursor->cases[i];
                }

                deleteFirm(firmList, firmList.cursor);
                undoStack.push(op);
                while (!redoStack.empty()) redoStack.pop();

                cout << "Firma Berhasil di Hapus" << endl;
            } else {
                cout << "Tidak ada Firma yang Dipilih Cursor" << endl;
            }
        } else if (choice == 4) { // Undo Operation
            undo(firmList, undoStack, redoStack);
        } else if (choice == 5) { // Redo Operation
            redo(firmList, undoStack, redoStack);
        } else if (choice == 6) { // Display Firms
            display(firmList, caseList);
        } else if (choice == 7) { // Display Cases
            displayCases(caseList);
        } else if (choice == 8) { // Move Cursor to Next Firm
            moveCursorToNext(firmList);
        } else if (choice == 9) { // Move Cursor to Previous Firm
            moveCursorToPrev(firmList);
        } else if (choice == 10) { // Delete Case Completely
            int caseId;
            cout << "Masukkan ID Kasus yang ingin Dihapus: ";
            cin >> caseId;
            deleteCase(caseList, caseId);
        } else if (choice == 11) { // Remove Case from Cursor's Firm
            int caseId;
            cout << "Masukkan ID Kasus yang ingin Dihapus dari Firma Cursor: ";
            cin >> caseId;
            removeCaseFromCursor(firmList, caseId);
        } else if (choice == 12) { // Insert a New Case
            int caseId;
            string caseName;
            cout << "Masukan ID Kasus (3 Angka Unik): ";
            cin >> caseId;
            cout << "Masukkan Nama Kasus: ";
            cin.ignore();
            getline(cin, caseName);
            insertLastCase(caseList, caseId, caseName);
            cout << "Kasus Berhasil Ditambah." << endl;
        } else if (choice == 13) { // Exit
            running = false;
            cout << "EXIT" << endl;
        } else {
            cout << "Masukkan Input yang Tersedia." << endl;
        }
    }
    return 0;
}

