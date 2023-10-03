#include<iostream>
#include<string>
#include<filesystem>
#include<fstream>

using namespace std;

class Book{
public:
    string bookCode, name, loc;
    int amount;
    Book(){}
    Book(string name, string bookCode, string loc, int amount){
        this->bookCode = bookCode; this->name = name; this->loc = loc; this->amount = amount;
    }
};

class Libary{
private:
    static const int sizeHastTable = 10000;
    Book books[sizeHastTable];
    void creatHastTable(){
        for (int i = 0; i < sizeHastTable; i++){
            books[i].amount = 0;
        }
    }
    int hast(string nameBook){
        int res = 0;
        for (int i = 0; i < nameBook.length(); i++){
            res += (nameBook[i] - '0');
        }
        return res%sizeHastTable;
    }
    bool cmpBook(Book b1, Book b2){
        return (b1.name == b2.name) && (b1.bookCode == b2.bookCode) && (b1.loc == b2.loc) && (b1.amount == b2.amount);
    }
public:
    Libary(){
        creatHastTable();
    }
    Book *getBooks(){
        return books;
    }
    int getSizeHastTable(){
        return sizeHastTable;
    }
    void readFile(string filename){
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Could not open file: " << filename << endl;
        }
        string bookCode, name, loc;
        int amount;
        while (getline(file, name) &&
                getline(file, bookCode) &&
                getline(file, loc) &&
                file >> amount){
            // !!!
            file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Bỏ qua dòng trống
            // !!!
            Book t(name, bookCode, loc, amount);
            insertBook(t);
        }
        file.close();
    }
    void writeFile(string filename){
        ofstream file(filename);
        if (!file.is_open()) {
            cerr << "Không thể mở tệp!" << endl;
        }
        for (int i = 0; i < sizeHastTable; i++){
            if (books[i].amount != 0){
                file << "Tên sách: " << books[i].name << ", mã sách: " << books[i].bookCode << ", vị trí: " << books[i].loc << ", số lượng: " << books[i].amount << endl;
            }
        }
        file.close();
    }
    Book find(string nameBook){
        int index = hast(nameBook);
        while (nameBook != books[index].name && books[index].amount != 0){
            index = (index + 1)%sizeHastTable;
        }
        if (nameBook != books[index].name){
            return books[index];
        } else {
            Book t;
            t.amount = 0;
            return t;
        }
    }
    void findBook(string nameBook){
        Book t = find(nameBook);
        if (t.amount != 0){
            cout << "Tên sách: " << t.name << ", mã sách: " << t.bookCode << ", vị trí: " << t.loc << ", số lượng: " << t.amount << endl;
        } else {
            cout << "Không có tìm thấy sách" << endl;
        }
    }
    void insertBook(Book b){
        // Linear probing
        if (b.amount != 0){
            int index = hast(b.name);
            // Tránh cập nhập hai sách giống nhau
            if (!cmpBook(books[index], b)){
                while(books[index].amount != 0){
                    index = (index + 1)%sizeHastTable;
                }
                books[index] = b;
            }
        } else {
            cout << "Sách nhập vào sai định dạng" << endl;
        }
    }
    void delBook(string nameBook){
        Book t = find(nameBook);
        if (t.amount != 0){
            t.amount = 0;
            t.bookCode = "";
            t.loc = "";
            t.name = "";
        } else {
            cout << "Không tìm thấy sách" << endl;
        }
    }
};

void showLibary(Book b[], int size){
    for (int i = 0; i < size; i++){
        if (b[i].amount != 0){
            cout << "Tên sách: " << b[i].name << ", mã sách: " << b[i].bookCode << ", vị trí: " << b[i].loc << ", số lượng: " << b[i].amount << endl;
        }
    }
}

void run(){
    Libary l;
    while (true){
        int n;
        cout << "----------------------------------------------------------------\n";
        cout << "Nhập 1 để: Nạp thông tin sách của thư viện từ file vào bảng băm \n";
        cout << "Nhập 2 để: Tìm kiếm sách theo tên sách \n";
        cout << "Nhập 3 để: Thêm một sách mới vào thư viện \n";
        cout << "Nhập 4 để: Xoá sách theo tên \n";
        cout << "Nhập 5 để: Lưu thông tin thư viện vào file \n";
        cout << "Nhập 6 để: Hiển thị thông tin sách trong thư viện ra màn hình \n";
        cout << "Nhập 7 để: Thoát \n";
        cout << "----------------------------------------------------------------" << endl;
        cout << "Nhập n = "; cin >> n;
        if (n == 1){
            string filename;
            cout << "Chỉ đến thư mục bạn muốn nhập dữ liệu: "; cin >> filename;
            l.readFile(filename);
            cout << "Đã tải thư mục lên !!!" << endl;
        } else if (n == 2){
            string nameBook;
            cout << "Nhập tên sách bạn muốn tìm kiếm: ";
            cin.ignore();
            getline(cin, nameBook);
            l.findBook(nameBook);
        } else if (n == 3){
            string bookCode, name, loc;
            int amount;
            cout << "Nhập tên sách: ";
            cin.ignore();
            getline(cin, name);
            cout << "Nhập tên mã sách: ";
            getline(cin, bookCode);
            cout << "Nhập tên vị trí sách: ";
            getline(cin, loc);
            cout << "Nhập số lượng sách: ";
            cin >> amount;
            Book temp(name, bookCode, loc, amount);
            l.insertBook(temp);
            cout << "..." << endl;
        } else if (n == 4){
            string nameBook;
            cout << "Nhập tên sách bạn muốn tìm kiếm: ";
            cin.ignore();
            getline(cin, nameBook);
            l.delBook(nameBook);
        } else if (n == 5){
            string filename;
            cout << "Nhập tên file muốn xuất dữ liệu: ";
            cin.ignore();
            getline(cin, filename);
            l.writeFile(filename);
            cout << "Đã xuất file !!!" << endl;
        } else if (n == 6){
            showLibary(l.getBooks(), l.getSizeHastTable());
        } else if (n == 7){
            for (int i = 0; i < 6; i++){
                cout << "END"<< endl;
            }
            break;
        } else{
            cout << "----- Vui lòng nhập số từ 1 đến 6 -----" << endl;
        }
    }
}

int main(){

    run();

    return 0;
}
