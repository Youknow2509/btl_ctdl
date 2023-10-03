#include <bits/stdc++.h>

using namespace std;

class node{
public:
    string E, V;
    node *left, *right;
// Khởi tạo một node 
    node(string E, string V){
        this->E = E; 
        this->V = V;
        left = right = NULL; 
    }
};

class Dictonary{
public:
    // Thêm một phần tử vào một cây
    node *add(node *t, string Eng, string Vie){
        // Vị trí thoả mãn khi nó ở ngoài cùng trỏ ra NULL hoặc cây chưa có phần tử nào thì khởi tạo
        if (!t){
            return new node(Eng, Vie);
        }
        // Duyệt qua các phần tử trong cây theo qui tắc của cây nhị phân
        if (Eng < t->E){
            t->left = add(t->left, Eng, Vie);
        } else if (Eng > t->E){
            t->right = add(t->right, Eng, Vie);
        }
        return t;
    }
    // Hàm (hỗ trợ) tìm node có giá trị nhỏ nhất của BST
    node *minVal(node *t){
        node *temp = t;
        while(temp->left != NULL){
            temp = temp->left;
        }
        return temp;
    }
    // Xoá một phần tử bất kì trong cây
    node *del(node *t, string Eng, string Vie){ 
        if (!t){
            return t;
        }
        // duyệt tìm phần tử trong cây thoả mãn
        if (Eng > t->E){
            t->right = del(t->right, Eng, Vie);
        } else if (Eng < t->E){
            t->left = del(t->left, Eng, Vie);
        } else{ 
            // Khi tìm đc giá trị cần xoá
            // TH node chứa giá trị cần xoá không có node con hoặc chỉ có node con bên phải
            if(t->left == NULL){
                node *temp = t->right;
                delete(t);
                return temp;
            } else if(t->right == NULL){
                node *temp = t->left;
                delete(t);
                return temp;
            }
            // TH node chứa giá trị cần xoá có hai node con bên trái và bên phải
            node *change = minVal(t->right);
            t->E = Eng;
            t->V = Vie;
            t->right = del(t, change->E, change->V);
            // CHúng ta thay thế giá trị node sau đó lập lại quá trình xoá kí tự vừa đc gán giá trị 
        }
        return t;
    }
    // Tìm node trong cây
    node *find(node *t, string Eng){
       if (!t || t->E == Eng){
            return t;
        }
        if (Eng > t->E){
            return find(t->right, Eng);
        } else {
            return find(t->left, Eng);
        }
    }
    // Cập nhập dữ liệu từ trong file
    void updataVoc(node *t, string Eng, string VieUpdate){
        node *find_voc_change = find(t, Eng);
        if (!find_voc_change){
            // Nếu không tìm được từ đó trong dữ liệu thì tự động thêm vào 
            t = add(t, Eng, VieUpdate);
        } else {
            find_voc_change->V = VieUpdate;
        }
    }
    // Đọc file xây dựng cây
    node* readFile(node *t, string filename){
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Không thể mở tệp" << endl;
        }
        string Eng, Vie;
        while (file >> Eng >> Vie) {
            t = add(t, Eng, Vie);
        }
        file.close();
        return t;
    }
    // Dùng hàm mới (hàm hỗ trợ) đệ qui viết vào file
    void solveWriteFile(node* t, ofstream& file) {
        if (t) {
            solveWriteFile(t->left, file);
            file << t->E << ": " << t->V << endl;
            solveWriteFile(t->right, file);
        }
    }
    // Hàm viết dữ liệu của cây nhị phân vào file
    void writeFile(node *t, string filename){
        ofstream file(filename);
        if (!file.is_open()) {
            cerr << "Không thể mở tệp!" << endl;
        }
        // Ghi dữ liệu của cây nhị phân vào tệp
        solveWriteFile(t, file);
        file.close();
    }
};
// Hỗ trợ debug - Hàm hỗ trợ hiển thị dữ liệu ra màn hình
void showData(node *t){
    if (t != NULL){
        showData(t->left);
        cout << "--- " << t->E << ": " <<  t->V << " ---" << endl;
        showData(t->right);
    }
}
// Dọn dẹp dữ liệu máy tính - Chạy lại file nhiều lần khi debug không bị treo máy
void del_ram(node *t){
    if ( t != NULL){
        del_ram(t->left);
        del_ram(t->right);
        delete(t);
    }
}
// App 
void run(){
    Dictonary d;
    node *t = NULL;
    while(true){
        int n;
        cout << "-------------------------------------------------------\n";
        cout << "Nhập 1 để: Đọc dữ liệu từ tệp vào cây \n";
        cout << "Nhập 2 để: Ghi dữ liệu từ cây ra file \n";
        cout << "Nhập 3 để: Thêm một từ mới vào cây \n";
        cout << "Nhập 4 để: Xoá bỏ một từ của từ điển đang lưu trong cây \n";
        cout << "Nhập 5 để: Cập nhập lại nghĩa một từ trong cây \n";
        cout << "Nhập 6 để: In dữ liệu ra màn hình \n";
        cout << "Nhập 7 để: Tìm từ trong cây \n";
        cout << "Nhập 8 để: Thoát \n";
        cout << "-------------------------------------------------------" << endl;
        cout << "Nhập n = "; cin >> n;
        if (n == 1){
            string filename;
            cout << "Nhập filename: "; cin >> filename;
            t = d.readFile(t, filename);
        } else if (n == 2){
            string filename;
            cout << "Nhập filename xuất ra: "; cin >> filename;
            d.writeFile(t, filename);
            cout << "Hãy kiểm tra file dữ liệu của bạn trong file !!!" << endl;
        } else if (n == 3){
            string E, V;
            cout << "Nhập từ tiếng anh: "; cin >> E;
            cout << "Nhập nghĩa từ " << E << ": "; cin >> V;
            t = d.add(t, E, V);
        } else if (n == 4){
            string E, choose;
            cout << "Nhập từ tiếng Anh cần xoá trong file: "; cin >> E;
            node *temp = d.find(t, E);
            if (temp == NULL){
                cout << "Từ của bạn không có trong từ điểm" << endl;
            } else {
                cout << temp->E << ": " << temp->V << endl;
                cout << "Nhập Y/N, Y để đồng ý xoá từ " << E <<", N để không xoá: "; cin >> choose;
                if (choose == "y" || choose == "Y"){
                    t = d.del(t, E, temp->V);
                    cout << "Hãy check lại dữ liệu của bạn" << endl;
                }else {
                    cout << "---" << endl;
                }
            }
        } else if ( n == 5){
            string E, V;
            cout << "Nhập từ tiếng Anh sửa đổi nghĩa: "; cin >> E;
            cout << "Nhập nghĩa cần sửa đổi: "; cin >> V;
            d.updataVoc(t, E, V);
        } else if (n == 6){
            cout << "-------------------------------------------------------" << endl;
            showData(t);
            cout << "-------------------------------------------------------" << endl;
        } else if (n == 7){
            string E;
            cout << "Nhập từ tiếng Anh cần tìm: "; cin >> E;
            node *temp = d.find(t, E);
            if (temp){
                cout << temp->E << ": " << temp->V << endl;
            } else {
                cout << "Từ không có trong từ điển." << endl;
            }
        } else if ( n == 8){
            del_ram(t);
            for (int i = 0; i < 6; i++){
                cout << "END"<< endl;
            }
            break;
        } else {
            cout << "--- Vui lòng nhập số từ 1 đến 8 ---" << endl;
        }
    }
}

int main(){

    run();

    return 0;
}