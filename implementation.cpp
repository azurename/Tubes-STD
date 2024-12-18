#include "header.h"

void createDllFirm(dllFirm &dllF) {
    dllF.head = nullptr;
    dllF.tail = nullptr;
    dllF.cursor = nullptr;
}

// Fungsi untuk membuat DLL kasus
void createDllCase(dllCase &dllC) {
    dllC.head = nullptr;
}

// Fungsi untuk menambahkan firma di akhir DLL
void insertLastFirm(dllFirm &dllF, int id, const string &name) {
    adrFirm newFirm = new Firm;
    newFirm->id = id;
    newFirm->name = name;
    newFirm->caseCount = 0;  // Awalnya tidak ada kasus
    newFirm->prev = nullptr;
    newFirm->next = nullptr;

    if (!dllF.head) {
        // Jika DLL kosong, firma menjadi elemen pertama
        dllF.head = dllF.tail = dllF.cursor = newFirm;
    } else {
        // Tambahkan di akhir DLL
        dllF.tail->next = newFirm;
        newFirm->prev = dllF.tail;
        dllF.tail = newFirm;
    }
}

// Fungsi untuk menghapus firma
void deleteFirm(dllFirm &dllF, adrFirm firm) {
    if (!firm) return;

    // Update cursor jika perlu
    if (firm == dllF.cursor) {
        if (firm->next) {
            dllF.cursor = firm->next;
        } else if (firm->prev) {
            dllF.cursor = firm->prev;
        }
    }

    // Perbarui pointer head/tail jika elemen yang dihapus ada di awal/akhir
    if (firm->prev) {
        firm->prev->next = firm->next;
    } else {
        dllF.head = firm->next;
    }

    if (firm->next) {
        firm->next->prev = firm->prev;
    } else {
        dllF.tail = firm->prev;
    }

    delete firm;
}

// Fungsi untuk menambahkan kasus di akhir DLL kasus
void insertLastCase(dllCase &dllC, int id, const string &name) {
    adrCase newCase = new Case;
    newCase->id = id;
    newCase->name = name;
    newCase->next = nullptr;

    if (!dllC.head) {
        // Jika DLL kosong, kasus menjadi elemen pertama
        dllC.head = newCase;
    } else {
        // Tambahkan di akhir DLL
        adrCase temp = dllC.head;
        while (temp->next) temp = temp->next;
        temp->next = newCase;
    }
}

// Fungsi untuk memindahkan cursor ke firma berikutnya
void moveCursorToNext(dllFirm &dllF) {
    if (dllF.cursor && dllF.cursor->next) {
        dllF.cursor = dllF.cursor->next;
        cout << "Cursor dipindahkan ke: " << dllF.cursor->name << endl;
    } else {
        cout << "Tidak ada firma berikutnya" << endl;
    }
}

// Fungsi untuk memindahkan cursor ke firma sebelumnya
void moveCursorToPrev(dllFirm &dllF) {
    if (dllF.cursor && dllF.cursor->prev) {
        dllF.cursor = dllF.cursor->prev;
        cout << "Cursor dipindahkan ke: " << dllF.cursor->name << endl;
    } else {
        cout << "Tidak ada firma sebelumnya" << endl;
    }
}

// Fungsi untuk menampilkan daftar firma dan kasusnya
void display(const dllFirm &dllF, const dllCase &dllC) {
    adrFirm temp = dllF.head;
    while (temp) {
        cout << "ID: " << temp->id << ", Nama: " << temp->name;
        if (temp == dllF.cursor) {
            cout << " (Cursor)";
        }
        cout << "\nKasus Terdaftar: ";
        for (int i = 0; i < temp->caseCount; i++) {
            cout << getCaseName(dllC, temp->cases[i]) << " (ID: " << temp->cases[i] << ") ";
        }
        cout << endl << endl;
        temp = temp->next;
    }
}

// Fungsi untuk menampilkan daftar kasus
void displayCases(const dllCase &dllC) {
    adrCase temp = dllC.head;
    cout << "Daftar Kasus:\n";
    while (temp) {
        cout << "ID: " << temp->id << ", Nama: " << temp->name << endl;
        temp = temp->next;
    }
    cout << endl;
}

// Fungsi untuk mengecek apakah ID kasus ada
bool caseExists(const dllCase &dllC, int caseId) {
    adrCase temp = dllC.head;
    while (temp) {
        if (temp->id == caseId) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

// Fungsi untuk mendapatkan nama kasus berdasarkan ID
string getCaseName(const dllCase &dllC, int caseId) {
    adrCase temp = dllC.head;
    while (temp) {
        if (temp->id == caseId) {
            return temp->name;
        }
        temp = temp->next;
    }
    return "Kasus Tidak Dikenal";
}

// Fungsi untuk menambahkan kasus ke firma yang ditunjuk cursor
bool addCaseUsingCursor(dllFirm &dllF, dllCase &dllC, int caseId) {
    if (!dllF.cursor) {
        cout << "Tidak ada firma yang dipilih (cursor null)" << endl;
        return false;
    }

    if (!caseExists(dllC, caseId)) {
        cout << "ID Kasus " << caseId << " tidak ditemukan" << endl;
        return false;
    }

    // Cek apakah kasus sudah terdaftar
    for (int i = 0; i < dllF.cursor->caseCount; i++) {
        if (dllF.cursor->cases[i] == caseId) {
            cout << "Firma sudah terdaftar dalam kasus ini" << endl;
            return false;
        }
    }

    // Tambahkan kasus ke firma
    if (dllF.cursor->caseCount == MAX_CASES) {
        cout << "Firma sudah mencapai batas maksimum kasus" << endl;
        return false;
    }

    dllF.cursor->cases[dllF.cursor->caseCount++] = caseId;
    cout << "Kasus " << getCaseName(dllC, caseId) << " (ID: " << caseId << ") ditambahkan ke firma " << dllF.cursor->name << endl;
    return true;
}

// Fungsi untuk menampilkan menu
void displayMenu() {
    cout << "\nMenu:\n";
    cout << "1. Tambah Kasus ke Firma yang ditunjuk Cursor\n";
    cout << "2. Tambah Firma\n";
    cout << "3. Hapus Firma yang ditunjuk Cursor\n";
    cout << "4. Undo Operasi pada Firma (Insert/Hapus)\n";
    cout << "5. Redo Operasi pada Firma (Insert/Hapus)\n";
    cout << "6. Display Firma\n";
    cout << "7. Display Kasus\n";
    cout << "8. Pindah Kursor ke Bawah\n";
    cout << "9. Pindah Kursor ke Atas\n";
    cout << "10. Hapus Salah Satu Kasus\n";
    cout << "11. Hapus Kasus dari Firma yang Ditunjuk\n";
    cout << "12. Tambah Kasus\n";
    cout << "13. Exit\n";
    cout << "Masukkan input yang ingin dilakukan: ";
}


void undo(dllFirm &dllF, stack<Operation> &undoStack, stack<Operation> &redoStack) {
    if (undoStack.empty()) {
        cout << "Tidak ada yang bisa di Undo" << endl;
        return;
    }

    Operation op = undoStack.top();
    undoStack.pop();

    if (op.type == "insert") {
        // Batalkan insert dengan menghapus Firm
        adrFirm temp = dllF.head;
        while (temp && temp->id != op.firmId) {
            temp = temp->next;
        }
        if (temp) {
            // Simpan data kasus ke operasi redo
            op.caseCount = temp->caseCount;
            for (int i = 0; i < temp->caseCount; i++) {
                op.cases[i] = temp->cases[i];
            }
            deleteFirm(dllF, temp);
        }
    } else if (op.type == "delete") {
        // Batalkan delete dengan menambahkan kembali Firm
        insertLastFirm(dllF, op.firmId, op.firmName);
        if (dllF.tail) {
            dllF.tail->caseCount = op.caseCount;
            for (int i = 0; i < op.caseCount; i++) {
                dllF.tail->cases[i] = op.cases[i];
            }
        }
    }

    redoStack.push(op);
}

void redo(dllFirm &dllF, stack<Operation> &undoStack, stack<Operation> &redoStack) {
    if (redoStack.empty()) {
        cout << "Tidak ada yang bisa di Redo" << endl;
        return;
    }

    Operation op = redoStack.top();
    redoStack.pop();

    if (op.type == "insert") {
        // Lakukan kembali insert
        insertLastFirm(dllF, op.firmId, op.firmName);
        if (dllF.tail) {
            dllF.tail->caseCount = op.caseCount;
            for (int i = 0; i < op.caseCount; i++) {
                dllF.tail->cases[i] = op.cases[i];
            }
        }
    } else if (op.type == "delete") {
        // Lakukan kembali delete
        adrFirm temp = dllF.head;
        while (temp && temp->id != op.firmId) {
            temp = temp->next;
        }
        if (temp) {
            deleteFirm(dllF, temp);
        }
    }

    undoStack.push(op);
}

// Function to delete a case completely from dllCase
void deleteCase(dllCase &dllC, int caseId) {
    if (!dllC.head) return;

    adrCase temp = dllC.head;
    adrCase prev = nullptr;

    while (temp && temp->id != caseId) {
        prev = temp;
        temp = temp->next;
    }

    if (!temp) {
        cout << "Case ID " << caseId << " Tidak Ditemukan." << endl;
        return;
    }

    if (prev) {
        prev->next = temp->next;
    } else {
        dllC.head = temp->next;
    }

    delete temp;
    cout << "Case ID " << caseId << " Berhasil Dihapus." << endl;
}

// Function to remove a case from the current cursor's firm
void removeCaseFromCursor(dllFirm &dllF, int caseId) {
    if (!dllF.cursor) {
        cout << "Cursor NULL / Tambahkan Firma." << endl;
        return;
    }

    bool found = false;
    for (int i = 0; i < dllF.cursor->caseCount; i++) {
        if (dllF.cursor->cases[i] == caseId) {
            found = true;
            // Shift cases to remove the ID
            for (int j = i; j < dllF.cursor->caseCount - 1; j++) {
                dllF.cursor->cases[j] = dllF.cursor->cases[j + 1];
            }
            dllF.cursor->caseCount--;
            break;
        }
    }

    if (found) {
        cout << "Case ID " << caseId << " Dihapus dari Firma " << dllF.cursor->name << " Berhasil." << endl;
    } else {
        cout << "Case ID " << caseId << " Tidak di Handle oleh Firma." << endl;
    }
}
