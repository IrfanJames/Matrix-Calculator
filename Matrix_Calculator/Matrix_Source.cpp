/*
taskkill /F /IM Matix_Calculator.exe
*/
#include <iostream>
#define order 15
#define userArr 17
using namespace std;
int totalMatrices = 0, currentMatrix, ansCols = 0, ansRows = 0;
float interArray[order][order], ansArray[order][order], binary1stArray[order][order], binary2ndArray[order][order], null[order][order];
int aSerial = 0, Ra = 0, Ca = 0, bSerial = 0, Rb = 0, Cb = 0;

int abslt(int a) {
    return (a >= 0) * (a) + (a < 0) * (a * -1);
}
void printMatrix(float Array[][order], int Rows, int Cols) {
    int p1 = 0, p2 = 0;
    for (p1 = 0; p1 < Rows; p1++) {
        cout << "R" << p1 + 1 << ":\t| ";
        for (p2 = 0; p2 < Cols; p2++) 
            cout << Array[p1][p2]<<" ";
        cout << endl;
    }
    cout << endl;
}
void previewMatrix(float Array[][order], int Rows, int Cols) {
    int tempCol = (Cols < 3) * Cols + (Cols >= 3) * 3;
    for (int c = 0; c < Rows; c++) {
        for (int cc = 0; cc < tempCol; cc++)
            cout << " " << Array[c][cc];
        if (Cols > 3)
            cout << "...";
        cout << "  ";
    }
    cout << endl;
}
void interMatrix(float arrayIn[][order], float arrayOut[][order], int Rows, int Cols) {
    int in1 = 0, in2 = 0;
    for (in1 = 0; in1 < Rows; in1++)
        for (in2 = 0; in2 < Cols; in2++)
            arrayIn[in1][in2] = arrayOut[in1][in2];
    in1 = 0; in2 = 0;
}
void extract(float Array[][order], float extractIn[][order], int Size, int Row, int Col) {
    int A = 0, B = 0, C = 0, D = 0;
    for (A = 0, C = 0; C < Size; C++) {
        if (C == Row) continue;
        for (B = 0, D = 0; D < Size; D++) {
            if (D == Col) continue;
            extractIn[A][B] = Array[C][D]; B++;
        }
        A++;
    }
}
float det(float Array[][order], int Cols) {
    if (Cols == 2) { return (Array[0][0]) * (Array[1][1]) - (Array[1][0]) * (Array[0][1]); }
    else if (Cols == 1) return (Array[0][0]);
    float extractArray[order][order], determinent=0;
    int sign = 1;

    for (int c = 0; c < Cols; c++) {
        extract(Array, extractArray, Cols, 0, c);
        //printMatrix(extractArray, Cols - 1, Cols - 1);
        
        determinent += det(extractArray, Cols - 1) * Array[0][c] * sign;
        sign = -sign;
    }
    return determinent;
}
void adjoint(float Array[][order], int Cols){
    if (Cols == 1 || Cols == 0) interArray[0][0] = Array[0][0];
    else
    for (int c = 0; c < Cols; c++) {
        for (int cc = 0; cc < Cols; cc++) {
            float extractArray[order][order];
            extract(Array, extractArray, Cols, c, cc);
            interArray[cc][c] = det(extractArray, Cols - 1) * (((cc % 2 == 0) + (cc % 2 == 1) * -1) * (c % 2 == 0) + ((cc % 2 == 0) + (cc % 2 == 1) * -1) * -1 * (c % 2 == 1));
        }
    }
    interMatrix(ansArray, interArray, Cols, Cols);
    ansRows = Cols;
    ansCols = Cols;
}
void inverse(float Array[][order], int Cols) {
    float arr[order][order], determinent=0;
    determinent = det(Array, Cols);
    adjoint(Array, Cols);
    for (int c = 0; c < Cols; c++)
        for (int cc = 0; cc < Cols; cc++)
            arr[c][cc] = (interArray[c][cc]) / determinent;
    interMatrix(ansArray, arr, Cols, Cols);
    ansRows = Cols;
    ansCols = Cols;
}
void mul(float ArrayA[][order], int Ra, int CaRb, int Cb, float ArrayB[][order]) {
    interMatrix(interArray, null, Ra + 1, Cb + 1);
    for (int c = 0; c < Ra; c++)
        for (int cc = 0; cc < Cb; cc++)
            for (int b = 0; b < CaRb; b++)
                interArray[c][cc] += ArrayA[c][b] * ArrayB[b][cc];
    interMatrix(ansArray, interArray, Ra, Cb);
    ansRows = Ra;
    ansCols = Cb;
}
void add(float ArrayA[][order], float ArrayB[][order], int Rows, int Cols) {
    interMatrix(interArray, null, Rows + 1, Cols + 1);
    for (int a = 0; a < Rows; a++)
        for (int b = 0; b < Cols; b++)
            interArray[a][b] = ArrayA[a][b] + ArrayB[a][b];
    interMatrix(ansArray, interArray, Rows, Cols);
    ansRows = Rows;
    ansCols = Cols;
}
void sub(float ArrayA[][order], float ArrayB[][order], int Rows, int Cols) {
    interMatrix(interArray, null, Rows + 1, Cols + 1);
    for (int a = 0; a < Rows; a++)
        for (int b = 0; b < Cols; b++)
            interArray[a][b] = ArrayA[a][b] - ArrayB[a][b];
    interMatrix(ansArray, interArray, Rows, Cols);
    ansRows = Rows;
    ansCols = Cols;
}


class matrix {
    int rows, cols, serialNo;
public:
    float arr[order][order];

    matrix() {
        rows = 1;
        cols = 1;
        arr[0][0] = 0.0;
        serialNo = totalMatrices++;
        currentMatrix = serialNo;
    }
    ~matrix() {

    }
    void setAll() {
        bool forR = 0, forC = 0;
        while (forR == 0) {
            cout << "No. of Rows:\t";
            cin >> rows;
            rows = abslt(rows);
            if (rows > order) cout << "Limit: " << order << endl;
            else forR = 1;
        }
        while (forC == 0) {
            cout << "No. of Columns:\t";
            cin >> cols;
            cols = abslt(cols);
            if (cols > order) cout << "Limit: " << order << endl;
            else forC = 1;
        }
        setArr();
    }
    void getInfo() {
        cout << "Name:\tMatrix " << getName() << endl;
        cout << "S.No:\t" << serialNo << endl;
        cout << "Rows:\t" << rows << endl;
        cout << "Cols:\t" << cols << endl;
        printArr();
        cout << endl;
    }
    int  getRows() {
        return rows;
    }
    int  getCols() {
        return cols;
    }
    char  getName() {
        return (char)(serialNo + 65);
    }
    void setArr() {
        cout << "Enter Matrix:\n\n";
        for (int c = 0; c < rows; c++) {
            cout << "R" << c + 1 << ":\t| ";

            for (int cc = 0; cc < cols; cc++) {
                cin >> arr[c][cc];
            }

        }
    }
    void printArr() {
        cout << "\nMatrix " << getName() << ":\n";
        for (int c = 0; c < rows; c++) {
            cout << "R" << c + 1 << ":\t| ";
            for (int cc = 0; cc < cols; cc++) {
                cout << arr[c][cc];
                cout << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    matrix Matrices[userArr];
    int userSelect = 1, userTotal = 0, currentMatrix = 0;

    //system("pause");

Home_Page:
    system("cls");
    cout << "Home Page/ " << Matrices[currentMatrix].getName() << "\n\n\t\tMatrix Calculator\n\n\t1. Create Matrix\n\t2. Select Matrix\n\t\n\t0. Exit\n\n";
    cin >> userSelect; userSelect = abslt(userSelect);
    switch (userSelect) {
    case 1:
    Frist:
        system("cls");
        cout << "Home Page/Create Matrix/Matrix " << Matrices[currentMatrix].getName() << endl << endl;
        currentMatrix = userTotal; userTotal++;
        Matrices[currentMatrix].setAll();
        system("cls");
        cout << "Home Page/Create Matrix\n\nMatrix " << Matrices[currentMatrix].getName() << " Created!!!\n\nMatrix " << Matrices[currentMatrix].getName() << " :\n";
        Matrices[currentMatrix].getInfo();
        system("pause");
        system("cls");
        goto Main_Menu;
        break;

    case 2:
        system("cls");
        cout << "Home Page/Select Matrix/Matrix " << Matrices[currentMatrix].getName() << endl << endl;
        for (int c = 0; c < userTotal; c++)
            cout << c + 1 << ". Matrix " << Matrices[c].getName() << endl;
        cout << "\nSelect: ";
        cin >> userSelect; userSelect = abslt(userSelect);
        if (userSelect > userTotal) userSelect = 1;
        currentMatrix = userSelect - 1;
        cout << "You selected:  Matrix " << Matrices[currentMatrix].getName() << endl;
        Matrices[currentMatrix].printArr();
        system("pause");
        system("cls");
        goto Main_Menu;
        break;

    case 7:
        system("cls");
        cout << "Home Page/God Mode/Matrix " << Matrices[currentMatrix].getName() << "\n\n\tWelcome to God Mode\n\n";
        system("pause");
        system("cls");
        goto Home_Page;
        break;

    case 0: system("cls"); system("cls"); goto Exit; break;
    default: system("cls"); system("cls"); goto Home_Page; break;
    }
        
Main_Menu:
    cout << "Main Menu/ " << Matrices[currentMatrix].getName() << "\n\n\t\tMatrix Calculator\n\nSelect Functions:\n\t1. Determinent\n\t2. Print Matrix\n\t3. Inverse\n\t4. Adjoint\n\t5. Echelon Form\n\t6. Binary Operation\n\n\t0. Home Page\n\n";
    cin >> userSelect;
    switch (userSelect) {
    case 1:
        system("cls");
        cout << "Home Page/Select Matrix/Determinent/Matrix " << Matrices[currentMatrix].getName() << endl << endl;
        if (Matrices[currentMatrix].getRows() == Matrices[currentMatrix].getCols()) {
            cout << "Det (Marix " << Matrices[currentMatrix].getName() << "): ";
            cout << det(Matrices[currentMatrix].arr, Matrices[currentMatrix].getCols()) << endl;
        }
        else {
            cout << "Given Matrix is not a Square Matrix\n\n";
        }
        Matrices[currentMatrix].printArr();
        system("pause");
        system("cls");
        goto Main_Menu;
        break;
    case 2:
        system("cls");
        cout << "Home Page/Select Matrix/Print Matrix/Matrix " << Matrices[currentMatrix].getName() << endl;
        Matrices[currentMatrix].printArr();
        system("pause");
        system("cls");
        goto Main_Menu;
        break;
    case 3:
        system("cls");
        cout << "Home Page/Select Matrix/Inverse/Matrix " << Matrices[currentMatrix].getName() << endl << endl;
        if (Matrices[currentMatrix].getRows() == Matrices[currentMatrix].getCols()) {
            cout << "Inverse of (Marix " << Matrices[currentMatrix].getName() << "):\n";
            inverse(Matrices[currentMatrix].arr, Matrices[currentMatrix].getCols());
            printMatrix(ansArray, Matrices[currentMatrix].getCols(), Matrices[currentMatrix].getCols());
        }
        else {
            cout << "Given Matrix is not a Square Matrix\n\n";
        }
        Matrices[currentMatrix].printArr();
        system("pause");
        system("cls");
        goto Main_Menu;
        break;
    case 4:
        system("cls");
        cout << "Home Page/Select Matrix/Adjoint/Matrix " << Matrices[currentMatrix].getName() << endl << endl;
        if (Matrices[currentMatrix].getRows() == Matrices[currentMatrix].getCols()) {
            cout << "Adjoint (Marix " << Matrices[currentMatrix].getName() << "):\n";
            adjoint(Matrices[currentMatrix].arr, Matrices[currentMatrix].getCols());
            printMatrix(ansArray, Matrices[currentMatrix].getCols(), Matrices[currentMatrix].getCols());
        }
        else {
            cout << "Given Matrix is not a Square Matrix\n\n";
        }
        Matrices[currentMatrix].printArr();
        system("pause");
        system("cls");
        goto Main_Menu;
        break;
    case 5:
        system("cls");
        cout << "Home Page/Select Matrix/Echelon From/Matrix " << Matrices[currentMatrix].getName() << endl << endl;
        cout << "Echelon Form of Marix (" << Matrices[currentMatrix].getName() << "):\n\nCooooming Out Soon\n";
        Matrices[currentMatrix].printArr();
        system("pause");
        system("cls");
        goto Main_Menu;
        break;
    case 6:
        system("cls");
        char operatorChar;

        cout << "Home Page/Select Matrix/Binary Operation/Matrix " << Matrices[currentMatrix].getName() << endl << endl;
        cout << "Santyx: 2+0 => Second plus AnswerMatix\n\n";
        cout << "0. AnsMatrix " << ansRows << "x" << ansCols << "\n\n";
        for (int c = 0; c < userTotal; c++) {
            cout << c + 1 << ". Matrix " << Matrices[c].getName() << "    " << Matrices[c].getRows() << "x" << Matrices[c].getCols() << " ";
            previewMatrix(Matrices[c].arr, Matrices[c].getRows(), Matrices[c].getCols());
        }
        cout << "OR Enter " << order - (order % 10) + 10 << " to create a new one.\n";
    Expression:
        cout << "\n\t| ";
        cin >> aSerial;
        aSerial = abslt(aSerial);
        if (aSerial > userTotal) goto Frist;
        cin >> operatorChar >> bSerial;
        bSerial = abslt(bSerial);


        if (operatorChar != '*' && operatorChar != '+' && operatorChar != '-' && operatorChar != '/') {
            cout << "Invalid Operator";
            goto Expression;
        }
        if (aSerial > userTotal || bSerial > userTotal) {
            cout << "Invalid Matrix/(ces)";
            goto Expression;
        }

        if (aSerial == 0) { Ra = ansRows; Ca = ansCols; }
        else {
            Ra = Matrices[aSerial - 1].getRows();
            Ca = Matrices[aSerial - 1].getCols();
        }
        
        if (bSerial == 0) { Rb = ansRows; Cb = ansCols; }
        else {
            Rb = Matrices[bSerial - 1].getRows();
            Cb = Matrices[bSerial - 1].getCols();
        }

        if ((Ca != Rb) && (Ra != Rb || Ca != Cb)) {
            cout << "Order Error!!! Order not sutible for any avialable operation";
            goto Expression;
        }

        cout << "\t";
        if (aSerial == 0) cout << "Ans";
        cout << "Matrix";
        if (aSerial != 0) cout << " " << Matrices[aSerial - 1].getName();
        cout << " " << operatorChar << " ";
        if (bSerial == 0) cout << "Ans";
        cout << "Matrix";
        if (bSerial != 0) cout << " " << Matrices[bSerial - 1].getName();
        cout << ":\n";

        if (aSerial == 0) interMatrix(binary1stArray, ansArray, Ra, Ca);
        else interMatrix(binary1stArray, Matrices[aSerial - 1].arr, Ra, Ca);

        if (bSerial == 0) interMatrix(binary2ndArray, ansArray, Rb, Cb);
        else interMatrix(binary2ndArray, Matrices[bSerial - 1].arr, Rb, Cb);

        printMatrix(binary1stArray, Ra, Ca);
        printMatrix(binary2ndArray, Rb, Cb);

        switch (operatorChar)
        {
        case '*':
            cout << "***" << endl;
            if (Ca == Rb) mul(binary1stArray, Ra, Rb, Cb, binary2ndArray);
            else cout << "Columns of 1st Matrix are not equal to Rows of 2nd Matrix\n\n";
            break;
        case '+':
            cout << "+++" << endl;
            if (Ra == Rb && Ca == Cb) add(binary1stArray, binary2ndArray, Ra, Ca);
            else cout << "Order of 1st Matrix is not equal Order of 2nd Matrix\n\n";
            break;
        case '-':
            cout << "---" << endl;
            if (Ra == Rb && Ca == Cb) sub(binary1stArray, binary2ndArray, Ra, Ca);
            else cout << "Order of 1st Matrix is not equal Order of 2nd Matrix\n\n";
            break;
        case '/': case (char)246:
            cout << "///" << endl;
            if (Ca != Rb) cout << "Columns of 1st Matrix are not equal to Rows of 2nd Matrix\n\n";
            else if (Rb != Cb) cout << "2nd Matrix is not a Square Matrix\nSo you can't divide with it\n\n";
            else if (det(binary2ndArray, Cb) == 0) cout << "Det of 2nd Matrix = 0\nSo you can't divide with it\n\n";
            else {
                inverse(binary2ndArray, Cb);
                mul(binary1stArray, Ra, Rb, Cb, ansArray);
            }
            break;
        default:
            cout << "Invalid Operator"; goto Expression;
            break;
        }
        printMatrix(ansArray, ansRows, ansCols);
        system("pause");
        system("cls");
        goto Main_Menu;
        break;

    case 0: system("cls"); system("cls"); goto Home_Page; break;
    default: system("cls"); system("cls"); goto Main_Menu; break;
    }


Exit:

    system("pause>0");
}