#include <iostream>
#include <iomanip>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <fstream>
#include <iomanip>

using namespace std;

//===========================================================================
#define setColorTable 7
#define setColorText 11
#define setColorMenu1 12
#define setColorMenu0 14
#define setX 30
#define setXi 10
#define setY 8
#define TbX 30
#define TbY 20
#define MAX 100

void TextColor(int color);
void gotoXY(int x, int y);
void VeBang(int x, int y, char** tieuDe, int* kichThuoc, int m, int n);
void VeBang2(int x, int y, char** tieuDe, int* tableSize, int m, int n);

//kiem tra
bool KiemTrafloat(char* s);
bool KiemTraint(char* s);
bool KiemTraTen(char *s);
bool KiemTraBs(char *s);
float Float(char *s);

//khai bao xe
struct Xe {
	char BIENSO[10], HANGXE[20];
	int DUNGTICH;
    int GIA;
};
bool Nhap(Xe& x);
bool Update(Xe& x);
Xe* ds_xe = new Xe[MAX]; // MAX là số lượng tối đa các xe trong danh sách
int so_luong_xe = 0; // Biến này để lưu trữ số lượng các xe trong danh sách hiện tại

void ThemXe(Xe& x);
void XoaXe(char* bienso);
void XuatThongTin(Xe xe);
void SuaXe(char* bienso, Xe x);
void TimKiem(char* bienso);
void LuuDanhSach( char* ten_file);
void InDanhSach();
void XuatThongTin(Xe xe);




int main(){
    char* ten_file = "xe.txt";
    int i;

    Xe x;
    Nhap(x);
    ThemXe(x);
    LuuDanhSach( ten_file);
    //InDanhSach() ;
    cout<<" Nhap  bien so :";
    char bienso[10];
    cin>>bienso;
    XoaXe(bienso);

    system("pause");
    return 0;

}



//kiem tra//===========================================================================
bool KiemTrafloat(char* s){
	if(strcmp(s, "") == 0)
		return false;
	for(int i=0; i<strlen(s); i++)
		if(!(s[i] == '.' || (s[i] >= 48 && s[i] <= 57)))
			return false;
	return true;
}
bool KiemTraint(char* s){
		if(strcmp(s, "") == 0)
		return false;
	for(int i=0; i<strlen(s); i++)
		if(!(s[i] >= 48 && s[i] <= 57))
			return false;
	return true;
}
bool KiemTraTen(char *s){
	if(strcmp(s, "") == 0)
		return false;
	for(int i=0; i<strlen(s); i++)
		if(!((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') || s[i] == 32))
			return false;
	return true;
}
bool KiemTraBs(char *s){
	if(strcmp(s, "") == 0 || strlen(s) > 20)
		return false;
	for(int i=0; i<strlen(s); i++)
		if(!((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= 48 && s[i] <= 57)))
			return false;
	return true;
}
float Float(char* s){
    float a = 0;
    int d = 1;
    for(int i=0; i<strlen(s); i++){
        if(s[i] == '.'){
            d = 10;
            continue;
        }
        if(d == 1)
            a = a*10 + s[i] - 48;
        else{
            a += 1.0*(s[i] - 48)/d;
            d *= 10;
        }
    }
    return a;
}

// nhap xe===================================================================//===============================================
bool Nhap(Xe& x) {
    char dt[5];
    char gia[10];

	int table[] = {15, 20, 15, 15};
	char** tieuDe = new char* [4];
	for(int i=0; i<4; i++)
		tieuDe[i] = new char[100];
	strcpy(tieuDe[0], "Bien so");
	strcpy(tieuDe[1], "Hang xe");
	strcpy(tieuDe[2], "Dung tich");
	strcpy(tieuDe[3], "Gia thue  ");
    while(1)
    {
        system("cls");
        TextColor(setColorText);
        int m;
        cout << "Nhap so luong xe: ";
        cin >> m;
        if(m <= 0) {
            cout << "So luong xe khong hop le. Hay nhap lai.\n";
            system("pause");
            continue;
        }
        VeBang(setXi, setY, tieuDe, table, m, 4);
        for(int i = so_luong_xe; i < so_luong_xe + m; i++)
        {
            gotoXY(setXi + 3, setY + 3 + i * 2); cin >> ds_xe[i].BIENSO;
            gotoXY(setXi + 3 + table[0], setY + 3 + i * 2); cin >> ds_xe[i].HANGXE;
            gotoXY(setXi + 3 + table[0] + table[1], setY + 3 + i * 2); cin >> dt;
            gotoXY(setXi + 3 + table[0] + table[1] + table[2], setY + 3 + i * 2); cin >> gia;
        }
        so_luong_xe += m;
        for(int i = so_luong_xe - m; i < so_luong_xe; i++) {
            if(KiemTraBs(ds_xe[i].BIENSO) && KiemTraint(dt) && KiemTraint(gia)) {
                ds_xe[i].DUNGTICH = Float(dt);
                ds_xe[i].GIA = Float(gia);
                return true;
            }

		}
		gotoXY(TbX, TbY);
		cout << "Nhap sai kieu du lieu!";
		gotoXY(TbX, TbY + 1);
		system("pause");
	}
}

//=====================THEM XE================================//========================================
void ThemXe(Xe& x) {
    if (so_luong_xe >= MAX) {
        cout << "Danh sach day, khong the them xe!\n";
        return;
    }
    for (int i = 0; i < so_luong_xe; i++) {
        if (ds_xe[i].BIENSO == x.BIENSO) {
            cout << "Bien so xe da ton tai trong danh sach!\n";
            return;
        }
    }
    ds_xe[so_luong_xe] = x;
    so_luong_xe++;
    gotoXY(0,25);
    cout << "Them xe thanh cong!\n";
}

//==================UPDATE XE=============================================
bool Update(Xe& x) {
    char dt[5];
    char gia[10];

	int table[] = {15, 20, 15, 15};
	char** tieuDe = new char* [4];
	for(int i=0; i<4; i++)
		tieuDe[i] = new char[100];
	strcpy(tieuDe[0], "Bien so");
	strcpy(tieuDe[1], "Hang xe");
	strcpy(tieuDe[2], "Dung tich");
	strcpy(tieuDe[3], "Gia thue  ");
		VeBang(setXi, setY, tieuDe, table, 1, 4);
	gotoXY(setXi + 3, setY + 3);	cout << x.BIENSO;
	gotoXY(setXi + 3 + table[0], setY + 3);	cout << x.HANGXE;
	gotoXY(setXi + 3 + table[0] + table[1], setY + 3); cout << x.DUNGTICH;
	gotoXY(setXi + 3 + table[0] + table[1] + table[2], setY + 3); cout << x.GIA;
	getch(); // bam phim bat ki
    while(1)
    {
        system("cls");
        TextColor(setColorText);
        int m;
        cout << "Nhap so luong xe: ";
        cin >> m;
        if(m <= 0) {
            cout << "So luong xe khong hop le. Hay nhap lai.\n";
            system("pause");
            continue;
        }
        VeBang(setXi, setY, tieuDe, table, m, 4);
        for(int i = so_luong_xe; i < so_luong_xe + m; i++)
        {
            gotoXY(setXi + 3, setY + 3 + i * 2); cin >> ds_xe[i].BIENSO;
            gotoXY(setXi + 3 + table[0], setY + 3 + i * 2); cin >> ds_xe[i].HANGXE;
            gotoXY(setXi + 3 + table[0] + table[1], setY + 3 + i * 2); cin >> dt;
            gotoXY(setXi + 3 + table[0] + table[1] + table[2], setY + 3 + i * 2); cin >> gia;
        }
        so_luong_xe += m;
        for(int i = so_luong_xe - m; i < so_luong_xe; i++) {
            if(KiemTraBs(ds_xe[i].BIENSO) && KiemTraint(dt) && KiemTraint(gia)) {
                ds_xe[i].DUNGTICH = Float(dt);
                ds_xe[i].GIA = Float(gia);
                return true;
            }

		}
		gotoXY(TbX, TbY);
		cout << "Nhap sai kieu du lieu!";
		gotoXY(TbX, TbY + 1);
		system("pause");
	}
}
//==================XOA XE===============
void XoaXe(char* bienso) {
    bool tim_thay = false;
    for(int i = 0; i < so_luong_xe; i++) {
        if(strcmp(ds_xe[i].BIENSO, bienso) == 0) {
            tim_thay = true;
            for(int j = i; j < so_luong_xe - 1; j++) {
                ds_xe[j] = ds_xe[j+1];
            }
            so_luong_xe--;
            cout << "Xoa xe co bien so " << bienso << " thanh cong!\n";
            break;
        }
    }

    if(tim_thay) {
        ofstream outFile("temp.txt");
        for(int i = 0; i < so_luong_xe; i++) {
            outFile << ds_xe[i].BIENSO << " " << ds_xe[i].HANGXE << " " << ds_xe[i].DUNGTICH << " " << ds_xe[i].GIA << endl;
        }
        outFile.close();

        // Đổi tên file tạm thời thành file gốc để ghi lại dữ liệu đã xóa
        remove("xe.txt");
        rename("temp.txt", "xe.txt");
    } else {
        cout << "Khong tim thay xe co bien so nhu vay!\n";
    }
}
//========SUA XE====================
void SuaXe(char* bienso, Xe x) {
    // Kiểm tra xem xe có tồn tại trong danh sách không
    bool tim_thay = false;
    for (int i = 0; i < so_luong_xe; i++) {
        if (strcmp(ds_xe[i].BIENSO, bienso) == 0) {
            // Nếu tìm thấy xe có biển số như vậy thì sửa thông tin
            ds_xe[i] = x;
            tim_thay = true;
            break;
        }
    }
    if (tim_thay) {
        cout << "Sua thong tin xe thanh cong!\n";
    }
    else {
        cout << "Khong tim thay xe co bien so nhu vay!\n";
    }
}
//===================TIM KIEM==================
void TimKiem(char* bienso) {
    bool tim_thay = false;
    for (int i = 0; i < so_luong_xe; i++) {
        if (strcmp(ds_xe[i].BIENSO, bienso) == 0) {
            XuatThongTin(ds_xe[i]);
            tim_thay = true;
            break;
        }
    }
    if (!tim_thay) {
        cout << "Khong tim thay xe co bien so nhu vay!\n";
    }
}

void InDanhSach() {
    cout << setw(10) << "STT"
         << setw(20) << "Bien so"
         << setw(20) << "Hang xe"
         << setw(20) << "Dung tich"
         << setw(20) << "Gia" << "\n";
    for (int i = 0; i < so_luong_xe - 1; i++) {
        cout << setw(10) << i+1
             << setw(20) << ds_xe[i].BIENSO
             << setw(20) << ds_xe[i].HANGXE
             << setw(20) << ds_xe[i].DUNGTICH
             << setw(20) << ds_xe[i].GIA << "\n";
    }
}
void XuatThongTin(Xe xe) {
    system("cls");
	int j = 0;
	TextColor(setColorText);
	gotoXY(setXi, setY + j++);
    cout << "Thong tin xe:\n";
    cout << "Bien so: " << xe.BIENSO << "\n";
    cout << "Hang xe: " << xe.HANGXE << "\n";
    cout << "Dung tich: " << xe.DUNGTICH << "\n";
    cout << "Gia: " << xe.GIA << "\n";
}

void LuuDanhSach(char* ten_file) {
    ofstream fout(ten_file, ios::out | ios::app);
    if (fout.fail()) {
        cout << "Khong the ghi vao file!\n";
        return;
    }
    for (int i = 0; i < so_luong_xe - 1; i++) {
    fout<<ds_xe[i].BIENSO<< " ";
    fout<<ds_xe[i].HANGXE<<" ";
    fout<<ds_xe[i].DUNGTICH<<" ";
    fout<<ds_xe[i].GIA<<endl;

    }
    fout.close();
    cout << "Luu danh sach xe vao file thanh cong!\n";
}

void TextColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

//===========================================================================
void gotoXY(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//===========================================================================
void VeBang(int x, int y, char* tieuDe[100], int* tableSize, int m, int n)
{
	m++;
    int len = 0;
    m += 1;
    TextColor(setColorText);
    for (int j = 1; j <= n; j++) {
        gotoXY(x + len + 3, y + 1);
        cout << tieuDe[j - 1];
        len += tableSize[j - 1];
    }
    TextColor(setColorTable);
    for (int i = 0; i < m; i++) {
        len = 0;
        if(i < m - 1){
        	gotoXY(x + len + 1, y + 2 * i + 1);
        	cout << char(179);
		}
        for (int j = 0; j < n; j++) {
            // ve bang
            if(i < m - 1){
			    if (j == n - 1)
			        gotoXY(x + len + tableSize[j], y + 2 * i + 1);
			    else
			        gotoXY(x + len + tableSize[j] + 1, y + 2 * i + 1);
			    cout << char(179);// |
			}
            gotoXY(x + len, y + 2 * i);
            for (int k = 0; k < tableSize[j]; k++) {
                len++;
                gotoXY(x + len, y + i * 2);
                cout << char(196); // -
                gotoXY(x + len, y + i * 2);
                if (i == 0) {// dong dau tien
                    if (len == 1) // goc trai tren
                        cout << char(218);
                    else if (k == 0) // vi tri cot
                        cout << char(194);
                    if (j == n - 1 && k == tableSize[j] - 1) // goc phai tren
                        cout << char(191);
                }
                else if (i == m - 1) { // dong cuoi cung
                    if (len == 1) // goc trai tren
                        cout << char(192);
                    else if (k == 0) // vi tri cot
                        cout << char(193);
                    else if (j == n - 1 && k == tableSize[j] - 1) // oc phai tren
                        cout << char(217);
                }
                else {
                    if (len == 1) // goc trai tren
                        cout << char(195);
                    else if (k == 0) // vi tri cot
                        cout << char(197);
                    else if (j == n - 1 && k == tableSize[j] - 1) // goc phai tren
                        cout << char(180);
                }
            }
        }
    }
}

//===========================================================================
void VeBang2(int x, int y, char** tieuDe, int* tableSize, int m, int n) {
    char** Tieude = new char* [n + 1];
    int* Tablesize = new int[n + 1];
    for (int i = 0; i < n + 1; i++) {
        Tieude[i] = new char[100];
    }
    Tablesize[0] = 5;
    strcpy(Tieude[0], "STT");
    for (int i = 1; i < n + 1; i++) {
        strcpy(Tieude[i], tieuDe[i - 1]);
        Tablesize[i] = tableSize[i - 1];
    }

    VeBang(x, y, Tieude, Tablesize, m, n + 1);
}




