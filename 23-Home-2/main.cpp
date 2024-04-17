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
    // Перегрузка оператор +
    Matrix operator +(const Matrix & other) {
        if (rows != other.rows || columns != other.columns) {
            throw "Введены матрицы разного размера, сложение невозможно"; // Оператор throw генерирует исключение
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
            throw "Введены матрицы разного размера, вычитание невозможно"; // Оператор throw генерирует исключение
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
    template <typename V>
    Matrix operator *(V sc) {
        Matrix multi("multi", rows, columns);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                cout << sc * matr[i][j] << " ";
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
};
    
int main() {
    int rows, columns;
    cout << "Введите количество строк матрицы А:" << endl;
    cin >> rows;
    cout << "Введите количество столбцов матрицы А:" << endl;
    cin >> columns;
    Matrix<int> A("A", rows, columns);
    cout << "Введите матрицу: " << endl;
    cin >> A;
    Matrix C = A * 5.6;
    cout << C;
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
    cout << "Куда записать матрицу? " << endl;
    cin >> nameoffile;
    B.outputfile(nameoffile);*/
    //cout << B;
    //file.close();
    return 0;
}
