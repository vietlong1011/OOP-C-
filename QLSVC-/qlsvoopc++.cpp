#include<Windows.h>  // thu vien do hoa console
#include<iostream>
#include<cstring>
#include<fstream>  // thu vien ho tro file 
#include<cstdlib> // thu vien ve ky tu
#include<iomanip> // thu vien lam viec voi cac bit ky tu
#include<windows.h>
using namespace std;


// class lay ngay thang nam sinh cua sv
class date
{
	int day;
	int month;
	int year;
public:
	date()
	{
		day = 10;
		month = 11;
		year = 2002;
	}
	friend istream& operator >>(istream& is, date& r)
	{
		do
		{
			cout << "Ngay: ";
			is >> r.day;
		} while (r.day > 31 || r.day < 1);
		do
		{
			cout << "Thang: ";
			is >> r.month;
		} while (r.month > 12 || r.month < 1);
		do
		{
			cout << "Nam: ";
			is >> r.year;
		} while (r.year < 1);
		return is;
	}
	friend ostream& operator <<(ostream& os, date& r)
	{
		os << setw(2) << r.day << "/" << setw(2) << r.month << "/" << setw(4) << r.year;
	}
	void tostring(char s[10])
	{
		strcpy(s, "");
		char ngay[3], thang[3], nam[5];
		itoa(day, ngay, 10);
		itoa(month, thang, 10);
		itoa(year, nam, 10);
		if (day < 10)
			strcat(s, "0");
		strcat(s, ngay);
		strcat(s, "/");
		if (month < 10)
			strcat(s, "0");
		strcat(s, thang);
		strcat(s, "/");
		strcat(s, nam);
	}
};
void chuan_hoa(char s[18])
{

	// xoa ki tu trang o dau
	while (s[0] == ' ')
		for (int i = 0; i < strlen(s); i++)
			s[i] = s[i + 1];
	// xoa ki tu trang o giua
	for (int i = 1; i < strlen(s); i++)
		if (s[i - 1] == ' ' && s[i] == ' ')
			while (s[i] == ' ')
				for (int j = i; j < strlen(s); j++)
					s[j] = s[j + 1];
	// chuan hoa chu hoa
	for (int i = 1; i < strlen(s); i++)
		if (s[i] >= 'A' && s[i] <= 'Z')
			s[i] += 32;

	if (s[0] > 'Z')
		s[0] = s[0] - 32;
	for (int i = 1; i < strlen(s); i++)
		if (s[i - 1] == ' ' && s[i] > 'Z')
			s[i] = s[i] - 32;
}
class sinhvien
{
	friend class mangsinhvien;
	char hoten[18];
	char ns[30];
	char gioitinh[5];
	char lop[10];
	int khoa;

public:
	char msv[10];
	sinhvien()  // ham chuan hoa ky tu ,tranh viec tran du lieu
	{
		strcpy(msv, "");
		strcpy(hoten, "");
		strcpy(ns, "");
		strcpy(lop, "");
		khoa ;
		strcpy(gioitinh, "");
	}

	sinhvien  operator = (sinhvien& r);
	friend istream& operator >>(istream& is, sinhvien& r);
	friend ostream& operator <<(ostream& os, sinhvien& r);
};

sinhvien sinhvien :: operator = (sinhvien& r)
{
	strcpy(msv, r.msv);
	strcpy(hoten, r.hoten);
	strcpy(ns, r.ns);
	strcpy(lop, r.lop);
	khoa = r.khoa;
	strcpy(gioitinh, r.gioitinh);
	return r;
}
istream& operator >>(istream& is, sinhvien& r)
{
	cout << "Ma sinh vien: ";
	is.ignore(255, '\n');
	is.get(r.msv, 6);

	cout << "Ho Va Ten: ";
	is.ignore(255, '\n');
	is.get(r.hoten, 18);
	chuan_hoa(r.hoten);

	cout << "Ngay Thang Nam Sinh:\n";
	date ns;
	cin >> ns;
	ns.tostring(r.ns);
	// 	is.ignore(255,'\n');
	// 	is.get(r.ns,11);

	cout << "Gioi tinh: ";
	is.ignore(255, '\n');
	is.get(r.gioitinh, 5);
	is.ignore(255, '\n');

	cout << "Ten lop: ";
	is.get(r.lop, 4);
	is.ignore(255, '\n');

	cout << "Khoa hoc: ";
	is >> r.khoa;
	return is;
}
ostream& operator <<(ostream& os, sinhvien& r)
{
	cout << setw(2) << left << char(186) << setw(9) << left << r.msv << setw(2) << left << char(186) << setw(18) << left << r.hoten << setw(2) << left << char(186) << setw(15) << left << r.ns << setw(2) << left << char(186) << setw(5) << left << r.lop << setw(2) << left << char(186) << setw(6) << left << r.khoa << setw(2) << left << char(186) << setw(9) << left << r.gioitinh << char(186);
	return os;

}
// tao mot mang sinh vien chua dssv duoc truy cap boi con tro
class mangsinhvien
{

public:
	sinhvien* data;
	int n;
	mangsinhvien(int n1 = 0)
	{
		n = n1;
		data = new sinhvien[n + 15];
	}
	~mangsinhvien()
	{
		if (data != NULL)
			delete[]data;
	}
	void resize(int n1)
	{
		data = new sinhvien[n1 + 10];
	}
	friend istream& operator >>(istream& is, mangsinhvien& r)
	{
		cout << "Nhap so luong sinh vien: ";
		is >> r.n;
		for (int i = 0; i < r.n; i++)
		{
			cout << "Sinh Vien thu " << i + 1 << "\n";
			is >> r.data[i];
		}
		return is;
	}
	friend ostream& operator <<(ostream& os, mangsinhvien& r)
	{
		for (int i = 0; i < r.n; i++)
			os << setw(6) << left << i + 1 << r.data[i];
		return os;
	}
	// khai bao cac chuc nang
	bool fix();
	void add(sinhvien a, int p);
	int remove(char p[10]);
	int remove(int p);
	int search(char s[30]);
	void print();
	int save(char filename[30]);
	int load(char filename[30]);
	void sort(char type[10]);
	bool trungmsv(sinhvien bosung);
	sinhvien  operator [](int i);
};
// ham sua du lieu sinh vien , luu y cu phap chu thuong
bool mangsinhvien::fix()
{
	int p;
	char s[10];
	do
	{
		cout << "Row: ";
		cin >> p;
		if (p<0 || p>n)
			cout << "This Row is not exsit, Try Again!\n";
	} while (p<0 || p>n);
	do
	{
		cout << " Sua theo : msv - hoten - ngaysinh - lop - khoa - gioitinh " << endl;
		cout << "Column: ";
		cin >> s;
		if (strcmp(s, "msv") == 0)
		{
			sinhvien moi;
			cout << "MSV: ";
			cin >> moi.msv;
			if (trungmsv(moi) == true)
				return false;
			strcpy(data[p - 1].msv, moi.msv);
			return true;
		}
		else if (strcmp(s, "hoten") == 0)
		{
			char hoten[18];
			cout << "Ho Va Ten: ";
			cin.ignore(255, '\n');
			cin.get(hoten, 18);
			chuan_hoa(hoten);
			strcpy(data[p - 1].hoten, hoten);
			return true;
		}
		else if (strcmp(s, "ngaysinh") == 0)
		{
			cout << "Ngay Thang Nam Sinh:\n";
			date ns;
			cin >> ns;
			ns.tostring(data[p - 1].ns);
			return true;
		}
		else if (strcmp(s, "gioitinh") == 0)
		{
			char gt[4];
			cout << "Gioi Tinh: ";
			cin >> gt;
			strcpy(data[p - 1].gioitinh, gt);
			return true;
		}
		else if (strcmp(s, "lop") == 0)
		{
			char lop[4];
			cout << "Lop: ";
			cin >> lop;
			strcpy(data[p - 1].lop, lop);
			return true;
		}
		else if (strcmp(s, "khoa") == 0)
		{
			int khoa;
			cout << "Khoa: ";
			cin >> khoa;
			data[p - 1].khoa = khoa;
			return true;
		}
		else
			cout << "This Column Is Not Exist, Try Again!\n";
	} while (true);

}
// ham them thong tin sinh vien
void mangsinhvien::add(sinhvien a, int p)
{
	
   
	if (p == 0)
	{
	
		data[n - 1] = a;
}
	else if(p < n)
	{
		for (int j = n - 1; j > p - 1; j--)
			data[j] = data[j - 1];
		data[p - 1] = a;
	} 


    else
	{
		for (int j = 0; j < p; j++)
		{
		
		data[ n ]=a;}n++;
	}
	
}
// ham xoa 
int mangsinhvien::remove(char p[10])
{
	int vt = -1;
	for (int i = 0; i < n; i++)
		if (strcmp(p, data[i].msv) == 0)
			vt = i;

	if (vt == -1)
		return 0;

	for (int i = vt; i < n; i++)
		data[i] = data[i + 1];

	n--;
	return 1;
}
int mangsinhvien::remove(int p)
{
	if (p<0 || p>n - 1)
		return 0;
	for (int i = p; i < n; i++)
		data[i] = data[i + 1];

	n--;
	return 1;
}
//ham tim kiem ten sv
int mangsinhvien::search(char s[30])
{
	int key = -1;
	chuan_hoa(s);

	for (int i = 0; i < n; i++)
		if (strcmp(data[i].msv, s) == 0 | strcmp(data[i].hoten, s) == 0)
			return i;

	return -1;
}
//ham load , mo file
int mangsinhvien::load(char filename[30])
{
	fstream fin;
	strcpy(filename, "D:/data.txt");
	fin.open(filename, ios::in);
	if (!fin.is_open())
		return 0;
	fin >> n;
	resize(n);
	char name1[10] = "";

	for (int i = 0; i < n; i++)
	{
		fin >> data[i].msv;
		strcpy(data[i].hoten, "");
		do
		{
			strcpy(name1, "");
			fin >> name1;
			if (name1[0] == ',')
				break;
			strcat(name1, " ");
			strcat(data[i].hoten, name1);
		} while (true);
		data[i].hoten[strlen(data[i].hoten) - 1] = data[i].hoten[strlen(data[i].hoten)];
		fin >> data[i].ns >> data[i].lop >> data[i].khoa >> data[i].gioitinh;
	}

	fin.close();
	return 1;
}
// ham luu file
int mangsinhvien::save(char filename[30])
{
	ofstream fin;
	fin.open(filename, ios::trunc);
	if (!fin.is_open())
		return 0;
	fin << n << endl;
	for (int i = 0; i < n; i++)

		fin << setw(9) << left << data[i].msv << setw(20) << left << data[i].hoten << " , " << setw(15) << left << data[i].ns << setw(10) << left << data[i].lop << setw(8) << left << data[i].khoa << setw(9) << left << data[i].gioitinh << "\n";
	fin.close();
	return 1;
}
// in ra 
void mangsinhvien::print()
{
	system("cls");

	cout << "--------------------***CHUONG TRINH QUAN LY SINH VIEN***-----------------------" << endl;
    cout << "\t\t\t=================MENU================\n";
	cout << "\t1.add: Them thong tin 1 sinh vien\n";
	cout << "\t2.remove: Xoa thong tin 1 sinh vien\n";
	cout << "\t3.load:Xuat thong tin file txt co trong source \n";
	cout << "\t4.search: Tim kiem thong tin sinh vien theo ma sinh vien va ho ten\n";
	cout << "\t5.save: Luu thong tin sinh vien va xuat file txt\n";
	cout << "\t6.print: In thong tin sinh vien\n";
	cout << "\t7.fix: Sua thong tin sinh vien\n";
	cout << "\t8.sort: Sap xep thong tin theo ma sinh vien hoac ho ten \n";
	cout << "\t9.exit: THOAT !!!\n"; 
	
	cout << char(201);
	for (int i = 0; i < 78; i++)
	{
		if (i == 4 || i == 15 || i == 35 || i == 52 || i == 59 || i == 67)
			cout << char(203);
		else
			cout << char(205);
	}
	cout << char(187);
	cout << char(186) << setw(4) << left << "STT" << setw(2) << left << char(186) << setw(9) << left << "MaSV" << setw(2) << left << char(186) << setw(18) << left << "Ho Va Ten" << setw(2) << left << char(186) << setw(15) << left << "Ngay Sinh" << setw(2) << left << char(186) << setw(5) << left << "Lop" << setw(2) << left << char(186) << setw(6) << left << "Khoa" << setw(2) << left << char(186) << setw(8) << left << "Gioi Tinh" << char(186);
	cout << char(204);
	for (int i = 0; i < 78; i++)
	{
		if (i == 4 || i == 15 || i == 35 || i == 52 || i == 59 || i == 67)
			cout << char(206);
		else
			cout << char(205);
	}
	cout << char(185);
	for (int i = 0; i < n; i++)
		cout << char(186) << setw(4) << left << i +1  << data[i];

	cout << char(200);
	for (int i = 0; i < 78; i++)
	{
		if (i == 4 || i == 15 || i == 35 || i == 52 || i == 59 || i == 67)
			cout << char(202);
		else
			cout << char(205);
	}
	cout << char(188);
}
//ham sap xep theo masv va ho ten
void mangsinhvien::sort(char type[10])
{
	if (strcmp(type, "msv") == 0)
	{
		for (int i = 0; i < n - 1; i++)
		{
			int min = i;
			for (int j = i + 1; j < n; j++)
				if (strcmp(data[j].msv, data[min].msv) < 0)
					min = j;
			sinhvien tg = data[min];
			data[min] = data[i];
			data[i] = tg;
		}
		print();
	}
	else if (strcmp(type, "hoten") == 0)
	{
		for (int i = 0; i < n - 1; i++)
		{
			int min = i;
			for (int j = i + 1; j < n; j++)
				if (strcmp(data[j].hoten, data[min].hoten) < 0)
					min = j;
			sinhvien tg = data[min];
			data[min] = data[i];
			data[i] = tg;
		}
		print();
	}
	else
	{
		print();
		cout << "Kieu du lieu ban nhap k phu hop!\n";
	}

}
// dieu kien trung msv 
bool mangsinhvien::trungmsv(sinhvien bosung)
{
	for (int i = 0; i < n; i++)
		if (strcmp(data[i].msv, bosung.msv) == 0)
			return true;
	return false;
}
sinhvien mangsinhvien :: operator [](int i)
{
	return data[i];
}

// ham do hoa console

void SetColor(int backgound_color, int text_color)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    int color_code = backgound_color * 16 + text_color;
    SetConsoleTextAttribute(hStdout, color_code);
}


void SetWindowSize(SHORT width, SHORT height)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    SMALL_RECT WindowSize;
    WindowSize.Top = 0;
    WindowSize.Left = 0;
    WindowSize.Right = width;
    WindowSize.Bottom = height;
 
    SetConsoleWindowInfo(hStdout, 1, &WindowSize);
    
}
//Hàm di chuyen con tro
void gotoxy(int x,int y)
{  
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD a = {x, y};
    SetConsoleCursorPosition(h, a);
 }
int main()
{
	SetColor(0, 14) ;  // thiet lap mau sac , backgroud
	SetWindowSize(83,32); // thieu lap kich thuoc man hinh console 20px = 1size
	mangsinhvien a;
	char k[10];
	char cmd[30];
		

  	cout << "----------***CHUONG TRINH QUAN LY SINH VIEN***----------" << endl;
    cout << "\t\t\t=================MENU================\n";
	cout << "\t1.add: Them thong tin 1 sinh vien\n";
	cout << "\t2.delete: Xoa thong tin 1 sinh vien\n";
	cout << "\t3.load:Xuat thong tin file txt co trong source \n";
	cout << "\t4.search: Tim kiem thong tin sinh vien theo ma sinh vien va ho ten\n";
	cout << "\t5.save: Luu thong tin sinh vien va xuat file txt\n";
	cout << "\t6.print: In thong tin sinh vien\n";
	cout << "\t7.fix: Sua thong tin sinh vien\n";
	cout << "\t8.sort: Sap xep thong tin theo ma sinh vien hoac ho ten \n";
	cout << "\t9.exit: THOAT !!!\n"; 
	cout << "\t\t\t=================END================\n";
	
       
	while (true)
	{
		cout << "Nhap lua chon cua ban : ";
		cin >> cmd;
		if (strcmp(cmd, "1") == 0)
		{
			int p;
			sinhvien moi;
			cout << "Nhap du lieu cho sinh vien can bo sung:\n";
			//cout<<moi;
			cin >> moi;
			while (a.trungmsv(moi) != false)
			{
				cout << "MSV nay da TON TAI, Yeu cau nhap lai MSV: ";
				cin >> moi.msv;
			}

		//	do
		//	{
				cout << "Nhap vi chi muon chen:";
				cin >> p;
		//		if (p<0 || p>a.n)
			//		cout << "Vi Tri Khong Hop le,Nhap Lai\n";
		//	} while (p<0 || p>a.n);
           
			a.add(moi, p);
			a.print();
		}
		else if (strcmp(cmd, "2") == 0)
		{
			int kt;
			int keyso;
			char keychu[10];
			cout << "fill out STT or MSV: ";
			cin >> keyso;
			system("pause");
			if (keyso > a.n)
			{
				itoa(keyso, keychu, 10);
				kt = a.remove(keychu);
			}
			else
			{
				kt = a.remove(keyso - 1);
			}
			if (kt == 1)
				a.print();
			if (kt == 0)
				cout << "Failed To Remove!\n--------------------------\n";
		}
		else if (strcmp(cmd, "3") == 0)
		{
			int kt = 0;
			char filename[30];
			do
			{
				cout << "Load filename: ";
				cin.ignore(255, '\n');
				cin.get(filename, 30);
				kt = a.load(filename);
				if (kt == 0)
					cout << "Filename is not exsit, Try agian!\n";
			} while (kt == 0);

			a.print();
			cout << filename << endl;
		}
		else if (strcmp(cmd, "4") == 0)
		{
			char s[50];
			cout << "Nhap thong tin can tim: ";
			cin.ignore(255, '\n');
			cin.get(s, 50);
			int kt = a.search(s);
			if (kt == -1)
			{
				system("cls");
				a.print();
				cout << "Kieu du lieu khong ton tai!\n---------------------\n";
			}

			else
			{
				system("cls");
				cout << "--------------------***CHUONG TRINH QUAN LY SINH VIEN***-----------------------" << endl;
                
    cout << "\t\t\t=================MENU================\n";
	cout << "\t1.add: Them thong tin 1 sinh vien\n";
	cout << "\t2.delete: Xoa thong tin 1 sinh vien\n";
	cout << "\t3.load:Xuat thong tin file txt co trong source \n";
	cout << "\t4.search: Tim kiem thong tin sinh vien theo ma sinh vien va ho ten\n";
	cout << "\t5.save: Luu thong tin sinh vien va xuat file txt\n";
	cout << "\t6.print: In thong tin sinh vien\n";
	cout << "\t7.fix: Sua thong tin sinh vien\n";
	cout << "\t8.sort: Sap xep thong tin theo ma sinh vien hoac ho ten \n";
	cout << "\t9.exit: THOAT !!!\n"; 
	cout << "\t\t\t=================END================\n";
				cout << char(201);
				for (int i = 0; i < 78; i++)
				{
					if (i == 4 || i == 15 || i == 35 || i == 52 || i == 59 || i == 67)
						cout << char(203);
					else
						cout << char(205);
				}
				cout << char(187);
				cout << char(186) << setw(4) << left << "STT" << setw(2) << left << char(186) << setw(9) << left << "MaSV" << setw(2) << left << char(186) << setw(18) << left << "Ho Va Ten" << setw(2) << left << char(186) << setw(15) << left << "Ngay Sinh" << setw(2) << left << char(186) << setw(5) << left << "Lop" << setw(2) << left << char(186) << setw(6) << left << "Khoa" << setw(2) << left << char(186) << setw(8) << left << "Gioi Tinh" << char(186);
				cout << char(204);
				for (int i = 0; i < 78; i++)
				{
					if (i == 4 || i == 15 || i == 35 || i == 52 || i == 59 || i == 67)
						cout << char(206);
					else
						cout << char(205);
				}
				cout << char(185);
				for (int i = 0; i < a.n; i++)
				{
					if (i == kt)
					{
						cout << char(199);
						for (int i = 0; i < 78; i++)
						{
							if (i == 4 || i == 15 || i == 35 || i == 52 || i == 59 || i == 67)
								cout << char(215);
							else
								cout << char(196);
						}
						cout << char(182);
					}

					cout << char(186) << setw(4) << left << i +1 << a.data[i];

					if (i == kt)
					{
						cout << char(199);
						for (int i = 0; i < 78; i++)
						{
							if (i == 4 || i == 15 || i == 35 || i == 52 || i == 59 || i == 67)
								cout << char(215);
							else
								cout << char(196);
						}
						cout << char(182);
					}
				}
				cout << char(200);
				for (int i = 0; i < 78; i++)
				{
					if (i == 4 || i == 15 || i == 35 || i == 52 || i == 59 || i == 67)
						cout << char(202);
					else
						cout << char(205);
				}
				cout << char(188);
			}
		}
		else if (strcmp(cmd, "8") == 0)
		{
			int chedo;
			char type[10];
			cout << "Hay nhap kieu du lieu ma ban muon sap xep ?: "<< endl ;
			cout <<"Chon theo msv hoac hoten: " ;
			cin >> type;
			a.sort(type);
		}
		else if (strcmp(cmd, "5") == 0)
		{
			int kt;
			char filename[30];
			do
			{
				cout << "Save filename: ";
				cin.ignore(255, '\n');
				cin.get(filename, 30);
				kt = a.save(filename);
				if (kt == 0)
					cout << "Save file fail,Try agian!\n";
			} while (kt == 0);
			a.print();
			cout << "Luu file thanh cong !\n";
		}
		else if (strcmp(cmd, "9") == 0)
		{
			break;
		}
		else if (strcmp(cmd, "6") == 0)
		{
			a.print();
		}
		else if (strcmp(cmd, "7") == 0)
		{
			bool kt = a.fix();
			a.print();
			if (kt == false)
				cout << "This 'Masv' Is Exsit, Failed To Fix!\n";
		}
		else
			cout << "Lua chon " << cmd << " khong ton  tai trong chuong trinh.\n";
	}

 system("cls");
	cout << "\n\n\t\t\t---Authors:Truong viet long---\n";

// animation 
do{
	
	for(int x = 0; x <13; x++)
    {
    	
        gotoxy(x,13); //di chuyen con tro
        cout << "---LUU Y: Chuong trinh chi mang tinh chat minh hoa cho san pham--\n";
        cout <<"\n\n\t\t\t Thanks for watching!";
          gotoxy(x,13);
        Sleep(200); // toc do
       
    }
     for(int x = 13; x > 0; x--)
        {
            gotoxy(x,13); 
                cout << "--LUU Y: Chuong trinh chi mang tinh chat minh hoa cho san pham--\n";
            Sleep(150); 
              }
          }while(1<2);
	cout<<"Press Enter To Close\n";


	system("pause");
	return 0;
}

