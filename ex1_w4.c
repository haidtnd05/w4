#include <stdio.h>
#include <stdlib.h>

/*
    Định nghĩa cấu trúc node của linked list
    - data: lưu giá trị
    - next: con trỏ trỏ đến node tiếp theo
*/
struct node {
    int data;
    struct node* next;
};

/*
    Hàm hiển thị danh sách liên kết
    Duyệt từ head đến NULL và in ra từng phần tử
*/
void display(struct node* head) {
    struct node* temp = head;  // con trỏ tạm để duyệt

    while (temp != NULL) {
        printf("%d -> ", temp->data);  // in dữ liệu
        temp = temp->next;             // chuyển sang node tiếp theo
    }

    printf("NULL\n"); // kết thúc danh sách
}

/*
    Hàm thêm phần tử vào cuối danh sách
    - Nếu list rỗng: node mới sẽ là head
    - Nếu không: duyệt đến cuối rồi nối vào
*/
struct node* addback(struct node* head, int data) {

    // Cấp phát bộ nhớ cho node mới
    struct node* newNode = (struct node*)malloc(sizeof(struct node));

    // Gán dữ liệu cho node mới
    newNode->data = data;
    newNode->next = NULL;  // node cuối nên next = NULL

    // Nếu danh sách rỗng
    if (head == NULL) {
        return newNode;  // node mới trở thành head
    }

    // Nếu danh sách đã có phần tử
    struct node* temp = head;

    // Duyệt đến node cuối cùng
    while (temp->next != NULL) {
        temp = temp->next;
    }

    // Gắn node mới vào cuối
    temp->next = newNode;

    return head; // trả lại head ban đầu
}

/*
    Hàm tìm phần tử trong danh sách
    - Nếu tìm thấy: trả về con trỏ đến node đó
    - Nếu không: trả về NULL
*/
struct node* find(struct node* head, int data) {
    struct node* temp = head;

    while (temp != NULL) {
        if (temp->data == data) {
            return temp; // tìm thấy
        }
        temp = temp->next;
    }

    return NULL; // không tìm thấy
}

/*
    Hàm xóa một node (pelement) trong danh sách
    - pelement được lấy từ hàm find
    - Phải xử lý riêng nếu node cần xóa là head
*/
struct node* delnode(struct node* head, struct node* pelement) {

    // Nếu danh sách rỗng hoặc phần tử cần xóa không tồn tại
    if (head == NULL || pelement == NULL)
        return head;

    // Trường hợp xóa node đầu (head)
    if (head == pelement) {
        struct node* temp = head;
        head = head->next; // cập nhật head mới
        free(temp);        // giải phóng bộ nhớ node cũ
        return head;
    }

    // Tìm node đứng trước node cần xóa
    struct node* temp = head;
    while (temp->next != NULL && temp->next != pelement) {
        temp = temp->next;
    }

    // Nếu tìm thấy pelement trong danh sách
    if (temp->next == pelement) {
        temp->next = pelement->next; // bỏ qua node cần xóa
        free(pelement);              // giải phóng bộ nhớ
    }

    return head;
}

/*
    Hàm giải phóng toàn bộ danh sách
    - Duyệt từng node và free
*/
void freelist(struct node* head) {
    struct node* temp;

    while (head != NULL) {
        temp = head;       // lưu node hiện tại
        head = head->next; // chuyển head sang node tiếp theo
        free(temp);        // free node cũ
    }
}

/*
    Hàm main để test toàn bộ chương trình
*/
int main() {
    struct node* head = NULL; // khởi tạo danh sách rỗng

    // =====================
    // Thêm phần tử vào list
    // =====================
    head = addback(head, 1);
    head = addback(head, 2);
    head = addback(head, 3);
    head = addback(head, 4);

    printf("Danh sach ban dau:\n");
    display(head);

    // =====================
    // Tìm phần tử
    // =====================
    int x = 3;
    struct node* found = find(head, x);

    if (found != NULL)
        printf("Tim thay %d trong danh sach\n", x);
    else
        printf("Khong tim thay %d\n", x);

    // =====================
    // Xóa phần tử
    // =====================
    head = delnode(head, found);

    printf("Danh sach sau khi xoa %d:\n", x);
    display(head);

    // =====================
    // Giải phóng bộ nhớ
    // =====================
    freelist(head);
    head = NULL; // tránh dangling pointer

    return 0;
}