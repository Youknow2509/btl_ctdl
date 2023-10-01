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
private:
    Dictonary *tree;
    // Thêm một phần tử vào một cây
    node *add(node *t, string Eng, string Vie){
        // Vị trí thoả mãn khi nó ở ngoài cùng trỏ ra NULL hoặc cây chưa có phần tử nào thì khởi tạo
        if (!t){
            return new node(Eng, Vie);
        }
        // Duyệt qua các phần tử trong cây theo qui tắc của cây nhị phân
        if (Eng < t->E) {
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
        if (Eng > t->E) {
            t->right = del(t->right, Eng, Vie);
        } else if (Eng < t->E) {
            t->left = del(t->left, Eng, Vie);
        } else { 
            // Khi tìm đc giá trị cần xoá
            // TH node chứa giá trị cần xoá không có node con hoặc chỉ có node con bên phải
            if(t->left == NULL) {
                node *temp = t->right;
                delete(t);
                return temp;
            } else if(t->right == NULL) {
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
public:
    
};

int main(){

    #ifndef ONLINE_JUDGE
    freopen("file/inp.txt", "r", stdin);
    freopen("file/out.txt", "w", stdout);
    #endif

    return 0;
}