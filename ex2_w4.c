#include <stdio.h>
#include <stdlib.h>

/*
    Cấu trúc node của cây nhị phân
    - data: giá trị
    - left: con trái
    - right: con phải
*/
struct tnode {
    int data;
    struct tnode* left;
    struct tnode* right;
};

/*
    (a) Hàm tạo node mới
    - Cấp phát bộ nhớ
    - Gán giá trị
    - Khởi tạo left, right = NULL
*/
struct tnode* talloc(int data) {
    struct tnode* newNode = (struct tnode*)malloc(sizeof(struct tnode));

    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

/*
    (b) Hàm thêm node vào cây (BST)
    - Nếu nhỏ hơn: đi sang trái
    - Nếu lớn hơn: đi sang phải
    - Đệ quy
*/
struct tnode* addnode(struct tnode* root, int data) {

    // Nếu cây rỗng → tạo node mới
    if (root == NULL) {
        return talloc(data);
    }

    // Nếu data nhỏ hơn → sang trái
    if (data < root->data) {
        root->left = addnode(root->left, data);
    }
    // Nếu lớn hơn → sang phải
    else {
        root->right = addnode(root->right, data);
    }

    return root;
}

/*
    (c) Duyệt Preorder (N-L-R)
    - In node hiện tại
    - Duyệt trái
    - Duyệt phải
*/
void preorder(struct tnode* root) {
    if (root == NULL) return;

    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

/*
    (d) Duyệt Inorder (L-N-R)
    - Kết quả sẽ được sắp xếp tăng dần (BST)
*/
void inorder(struct tnode* root) {
    if (root == NULL) return;

    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

/*
    (e) Xóa toàn bộ cây (post-order)
    - Trái → phải → node
    - Trả về số node đã xóa
*/
int deltree(struct tnode* root) {
    if (root == NULL) return 0;

    int count = 0;

    // Xóa cây con trái
    count += deltree(root->left);

    // Xóa cây con phải
    count += deltree(root->right);

    // Xóa node hiện tại
    free(root);
    count++;

    return count;
}

/*
    (f) Hàm main test
*/
int main() {
    struct tnode* root = NULL;

    // Thêm các phần tử theo đề bài
    int arr[] = {3, 1, 0, 2, 8, 6, 5, 9};
    int n = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < n; i++) {
        root = addnode(root, arr[i]);
    }

    // In preorder
    printf("Preorder: ");
    preorder(root);
    printf("\n");

    // In inorder (phải tăng dần)
    printf("Inorder (sorted): ");
    inorder(root);
    printf("\n");

    // Xóa cây
    int deleted = deltree(root);
    root = NULL; // tránh dangling pointer

    printf("So node da xoa: %d\n", deleted);

    return 0;
}