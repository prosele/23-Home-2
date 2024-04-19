#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

template <typename T>
class Matrix {
private:
    string name;
    int rows;
    int columns;
    vector<vector<T>> matr;
    ifstream FileMatrix;
public:
    Matrix(string Name, int Rows, int Columns) : name(Name), rows(Rows), columns(Columns) {
        matr.resize(rows, vector<T>(columns));
    }
    Matrix (string Name, int Rows, int Columns, string fname) : name(Name), rows(Rows), columns(Columns) {
        matr.resize(rows, vector<T>(columns));
        inputfile(fname);
    }
    //Конструктор копирования
    Matrix(const Matrix &obj) {
        rows = obj.rows;
        columns = obj.columns;
        matr = obj.matr;
    }
    // Функция inputfile(string fname) записывает в матрицу данные из файла
    void inputfile(string fname) {
        FileMatrix.open(fname);
        if (FileMatrix.is_open()) {
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < columns; j++) {
                    FileMatrix >> matr[i][j];
                }
            }
        }
    }
    // Функция outputfile(string fname) записывает в файл матрицу
    void outputfile(string fname) {
        ofstream file;
        file.open(fname);
        if (file.is_open()) {
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < columns; j++) {
                    file << matr[i][j] << " ";
                }
                file << endl;
            }
        }
        file.close();
    }
    ~Matrix() {
        FileMatrix.close();
    }
    
    // Для ввода матрицы
    void input(istream &is) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                is >> matr[i][j];
            }
        }
    }
    // Для вывода матрицы
    void output(ostream &os) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                os << matr[i][j] << " ";
            }
            os << endl;
        }
    }
    // Перегрузка оператора +
    Matrix operator +(const Matrix & other) {
        if (rows != other.rows || columns != other.columns) {
            throw "Введены матрицы разного размера, сложение невозможно";
            }
        Matrix sum("sum", rows, columns);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                sum.matr[i][j] = matr[i][j] + other.matr[i][j];
            }
        }
        return sum;
    }
    // Перегрузка оператора -
    Matrix operator -(const Matrix & other) {
        if (rows != other.rows || columns != other.columns) {
            throw "Введены матрицы разного размера, вычитание невозможно";
        }
        Matrix dif("dif", rows, columns);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                dif.matr[i][j] = matr[i][j] - other.matr[i][j];
            }
        }
        return dif;
    }
    
    // Перегрузка оператора * для умножения матриц
    Matrix operator *(const Matrix & other) {
        if (columns != other.rows) {
            throw "Такие матрицы нельзя перемножить, так как количество столбцов первой матрицы не равно количеству строк второй матрицы";
        }
        Matrix multi("multi", rows, other.columns);
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < other.columns; j++) {
                    int summa = 0;
                    for (int k = 0; k < columns; k++) {
                        summa += matr[i][k] * other.matr[k][j];
                    }
                    multi.matr[i][j] = summa;
                    summa = 0;
                }
            }
        return multi;
    }
    //Перегрузка оператора * для умножения матрицы на число
    Matrix operator *(T sc) {
        Matrix multi("multi", rows, columns);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                multi.matr[i][j] = sc * matr[i][j];
                
            }
        }
        return multi;
    }
    
    //Перегрузка оператора присваивания
    Matrix& operator=(const Matrix &m) {
        rows = m.rows;
        columns = m.columns;
        matr = m.matr;
        return *this;
    }
    
    // Перегрузка оператора ввода >>
    friend istream& operator>>(istream &is, Matrix &m) {
        m.input(is);
        return is;
    }
    // Перегрузка оператора вывода <<
    friend ostream& operator<<(ostream &os, Matrix &m) {
        m.output(os);
        return os;
    }
    //Алгебраическое дополнение
    Matrix getMinor(int i, int j) {
        i--;
        j--;
        Matrix matrix(name, rows-1, columns-1);
        int k = 0;
        int f = 0;
        for (int indexI = 0; indexI < rows; indexI++) {
            if (indexI == i) {
                continue;
            }
            f = 0;
            for (int indexJ = 0; indexJ < columns; indexJ++) {
                if (indexJ == j) {
                    continue;
                }
                matrix.matr[k][f] = matr[indexI][indexJ];
                f++;
            }
            k++;
        }
        return matrix;
    }
    // Определитель
    double getDet() {
        if (rows != columns) {
            throw "Невозможно найти определитель матрицы, так как она не квадратная";
        }
            
        if (rows == 1) {
            return matr[0][0];
        }
        if (rows == 2) {
            return matr[0][0]*matr[1][1]  - matr[0][1]*matr[1][0];
        }
        double res = 0.0;
        for (int j = 0; j < columns; j++) {
            Matrix M = getMinor(1, j + 1);
            res += (j % 2 == 0 ? 1 : -1) * M.getDet() * matr[0][j];
        }
        return res;
    }
    //Транспонирование
    Matrix transpose() {
        Matrix transpose("transpose", columns, rows);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                transpose.matr[j][i] = matr[i][j];
            }
        }
        return transpose;
    }
    Matrix operator!() {
        Matrix current("curr", rows, columns);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                current.matr[i][j] = matr[i][j];
            }
        }
        if (columns != rows || current.getDet() == 0) {
            throw "Матрица должна быть квадратной и невырожденной";
        }
        Matrix minor("minor", rows, columns);
        if (rows == 1 && columns == 1) {
            current.matr[0][0] = 1/current.matr[0][0];
            return current;
        }
        if (rows == 2) {
            minor.matr[0][0] = matr[1][1];
            minor.matr[0][1] = -matr[1][0];
            minor.matr[1][0] = -matr[0][1];
            minor.matr[1][1] = matr[0][0];
        }
        if (rows > 2) {
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < columns; j++) {
                    minor.matr[i][j] = ((i + j) % 2 == 0? 1 : -1) * getMinor(i + 1, j + 1).getDet();
                }
            }
        }
        Matrix inverse = minor.transpose() * (1 / current.getDet());
        return inverse;
    }
};
    
int main() {
    int rows, columns;
    cout << "Введите количество строк матрицы А:" << endl;
    cin >> rows;
    cout << "Введите количество столбцов матрицы А:" << endl;
    cin >> columns;
    Matrix<double> A("A", rows, columns);
    cout << "Введите матрицу A: " << endl;
    cin >> A;
    /*//Умножение матрицы на число
    Matrix C = A * 5;
    cout << "Матрица С: " << endl;
    cout << C;*/
    try {
        Matrix<double> F = !A;
        cout << "Обратная к матрице А: " << endl;
        cout << F;
    }
    catch (const char* ErrorMessage) {
        cout << ErrorMessage << endl;
    }
    /*//Сложение двух матриц
    try {
        Matrix P = A + C;
        cout << "Матрица P: " << endl;
        cout << P;
    }
    catch (const char* ErrorMessage) {
        cout << ErrorMessage << endl;
    }*/
    /*//Вычитание двух матриц
    try {
        Matrix Q = A - C;
        cout << "Матрица Q: " << endl;
        cout << Q;
    }
    catch (const char* ErrorMessage) {
        cout << ErrorMessage << endl;
    }*/
    /*//Умножение двух матриц
    try {
        Matrix D = A * C;
        cout << "Матрица D: " << endl;
        cout << D;
    }
    catch (const char* ErrorMessage) {
        cout << ErrorMessage << endl;
    }*/
    /*string fname = "";
    cout << "Введите название вашего файла:" << endl;
    cin >> fname;
    ifstream file;
    file.open(fname);
    if (!file.is_open()) {
        cout << "Файл с матрицей B не открыт" << endl;
    }
    else {
        cout << "Файл с матрицей B открыт" << endl;
    }
    int characters = 0;
    int lines = 0;
    string line;
    while (getline(file, line)) {
        for (int i = 0; i < line.length(); i++) {
            if (line[i] != ' ') {
                characters++;
            }
        }
        lines++;
    }
    Matrix<int> B("B", lines, (characters - 1) / lines, fname);
    cout << B;*/
    /*string nameoffile;
    cout << "Куда записать матрицу B? " << endl;
    cin >> nameoffile;
    B.outputfile(nameoffile);*/
    //cout << B;
    //file.close();
    return 0;
}
