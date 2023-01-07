#include<Windows.h>  // thu vien do hoa console
#include<iostream>
#include<cstring>
#include<fstream>  // thu vien ho tro file 
#include<cstdlib> // thu vien ve ky tu
#include<iomanip> // thu vien lam viec voi cac bit ky tu


using namespace std;
// mo rong code 

// class lay ngay thang nam sinh cua sv
class date1
{
	int day;
	int month;
	int year;
public:
	date1()
	{
		day = 10;
		month = 11;
		year = 2002;
	}
	friend istream& operator >>(istream& is, date1& d)
	{
		do
		{
			cout << "Ngay: ";
			is >> d.day;
		} while (d.day > 31 || d.day < 1);
		do
		{
			cout << "Thang: ";
			is >> d.month;
		} while (d.month > 12 || d.month < 1);
		do
		{
			cout << "Nam: ";
			is >> d.year;
		} while (d.year < 1);
		return is;
	}
	friend ostream& operator <<(ostream& os, date1& d)
	{
		os << setw(2) << d.day << "/" << setw(2) << d.month << "/" << setw(4) << d.year;
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
void chuan_hoa1(char s[18])
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
class giangvien 
{
	friend class manggiangvien;
	char hoten[30];
	char ns[30];
	char gioitinh[5];
	int khoa;
public:
	char mgv[10];
		int songaylam;
	giangvien()  // ham chuan hoa ky tu ,tranh viec tran du lieu
	{
		strcpy(mgv, "");
		strcpy(hoten, "");
		strcpy(ns, "");
		khoa ;
		strcpy(gioitinh, "");
		songaylam;
	}

	giangvien  operator = (giangvien& d);
	friend istream& operator >>(istream& is, giangvien& d);
	friend ostream& operator <<(ostream& os, giangvien& d);
};
giangvien giangvien :: operator = (giangvien& d)
{
	strcpy(mgv, d.mgv);
	strcpy(hoten, d.hoten);
	strcpy(ns, d.ns);
	strcpy(gioitinh, d.gioitinh);
    songaylam =	d.songaylam;
    khoa = d.khoa;
	return d;
}
istream& operator >>(istream& is, giangvien& d)
{
	cout << "Ma giang vien: ";
	is.ignore(255, '\n');
	is.get(d.mgv, 6);

	cout << "Ho Va Ten: ";
	is.ignore(255, '\n');
	is.get(d.hoten, 30);
	chuan_hoa1(d.hoten);		
	cout << "Ngay Thang Nam Sinh:\n";
	date1 ns;
	cin >> ns;
	ns.tostring(d.ns);
	// 	is.ignore(255,'\n');
	// 	is.get(r.ns,11);

	cout << "Gioi tinh: ";
	is.ignore(255, '\n');
	is.get(d.gioitinh, 5);
	is.ignore(255, '\n');
    cout << "So ngay lam viec:";
	is >> d.songaylam	;
	cout << "Khoa day: ";
	is >> d.khoa;
	return is;
}
ostream& operator <<(ostream& os, giangvien& d)
{
	cout << setw(2) << left << char(186) << setw(9) << left << d.mgv << setw(2) << left << char(186) << setw(18) << left << d.hoten << setw(2) << left << char(186) << setw(15) << left << d.ns << setw(2) << left << char(186) << setw(5) << left << d.songaylam << setw(2) << left << char(186) << setw(6) << left << d.khoa << setw(2) << left << char(186) << setw(9) << left << d.gioitinh << char(186);
	return os;

}


class manggiangvien
{

public:
giangvien* data;
	int n;
	manggiangvien(int n1 = 0)
	{
		n = n1;
		data = new giangvien[n + 15];
	}
	~manggiangvien()
	{
		if (data != NULL)
			delete[]data;
	}
	void resize(int n1)
	{
		data = new giangvien[n1 + 10];
	}
	friend istream& operator >>(istream& is, manggiangvien& d)
	{
		cout << "Nhap so luong giang vien: ";
		is >> d.n;
		for (int i = 0; i < d.n; i++)
		{
			cout << "Giang vien thu " << i + 1 << "\n";
			is >> d.data[i];
		}
		return is;
	}
	friend ostream& operator <<(ostream& os, manggiangvien& d)
	{
		for (int i = 0; i < d.n; i++)
			os << setw(6) << left << i + 1 << d.data[i];
		return os;
	}

	bool fix();
	void add(giangvien b, int p);
	int remove(char p[10]);
	int remove(int p);
	int search(char s[30]);
	void print();
	int save(char filename[30]);
	int load(char filename[30]);
	void sort(char type[10]);
	bool trungmgv(giangvien bosung);
	float luong(float &a);
     giangvien  operator [](int i);
	
};
//ham in ra man hinh
void manggiangvien::print()
{
	system("cls");

	cout << "--------------------***CHUONG TRINH QUAN LY GiANG VIEN***-----------------------" << endl;
    cout << "\t\t\t=================MENU================\n";
	cout << "\t1.add: Them thong tin 1 Giang vien\n";
	cout << "\t2.remove: Xoa thong tin 1 giang vien\n";
	cout << "\t3.load:Xuat thong tin file txt co trong source \n";
	cout << "\t4.search: Tim kiem thong tin giang vien theo ma sinh vien va ho ten\n";
	cout << "\t5.save: Luu thong tin giang vien va xuat file txt\n";
	cout << "\t6.print: In thong tin giang vien\n";
	cout << "\t7.fix: Sua thong tin giang vien\n";
	cout << "\t8.sort: Sap xep thong tin theo ma giang vien hoac ho ten \n";
    cout << "\t9.money: Tinh tien luong cua tung giang vien\n"; 
	cout << "\t10.exit: THOAT !!!\n"; 
	
	cout << char(201);
	for (int i = 0; i < 78; i++)
	{
		if (i == 4 || i == 15 || i == 35 || i == 52 || i == 59 || i == 67)
			cout << char(203);
		else
			cout << char(205);
	}
	cout << char(187);
	cout << char(186) << setw(4) << left << "STT" << setw(2) << left << char(186) << setw(9) << left << "MaGV" << setw(2) << left << char(186) << setw(18) << left << "Ho Va Ten" << setw(2) << left << char(186) << setw(15) << left << "Ngay Sinh" << setw(2) << left << char(186) << setw(5) << left << "SNL" << setw(2) << left << char(186) << setw(6) << left << "Khoa" << setw(2) << left << char(186) << setw(8) << left << "Gioi Tinh" << char(186);
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

// dieu kien trung mgv 
bool manggiangvien::trungmgv(giangvien bosung)
{
	for (int i = 0; i < n; i++)
		if (strcmp(data[i].mgv, bosung.mgv) == 0)
			return true;
	return false;
}
giangvien manggiangvien :: operator [](int i)
{
	return data[i];
}
// them
 void manggiangvien::add(giangvien b, int p)
{
	
   
	if (p == 0)
	{
	
		data[n - 1] = b;
}
	else if(p < n)
	{
		for (int j = n - 1; j > p - 1; j--)
			data[j] = data[j - 1];
		data[p - 1] = b;
	} 


    else
	{
		for (int j = 0; j < p; j++)
		{
		
		data[ n ]=b;}n++;
	}
	
}
// ham xoa
int manggiangvien::remove(char p[10])
{
	int vt = -1;
	for (int i = 0; i < n; i++)
		if (strcmp(p, data[i].mgv) == 0)
			vt = i;

	if (vt == -1)
		return 0;

	for (int i = vt; i < n; i++)
		data[i] = data[i + 1];

	n--;
	return 1;
}
int manggiangvien::remove(int p)
{
	if (p<0 || p>n - 1)
		return 0;
	for (int i = p; i < n; i++)
		data[i] = data[i + 1];

	n--;
	return 1;
}

//ham load , mo file
int manggiangvien::load(char filename[30])
{
	fstream fin;
	strcpy(filename, "D:/datagv.txt");
	fin.open(filename, ios::in);
	if (!fin.is_open())
		return 0;
	fin >> n;
	resize(n);
	char name1[10] = "";

	for (int i = 0; i < n; i++)
	{
		fin >> data[i].mgv;
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
		fin >> data[i].ns >> data[i].songaylam >> data[i].khoa >> data[i].gioitinh;
	}

	fin.close();
	return 1;
}
// ham luu file
int manggiangvien::save(char filename[30])
{
	ofstream fin;
	fin.open(filename, ios::trunc);
	if (!fin.is_open())
		return 0;
	fin << n << endl;
	for (int i = 0; i < n; i++)

		fin << setw(9) << left << data[i].mgv << setw(20) << left << data[i].hoten << " , " << setw(15) << left << data[i].ns << setw(10) << left << data[i].songaylam << setw(8) << left << data[i].khoa << setw(9) << left << data[i].gioitinh << "\n";
	fin.close();
	return 1;
}
// ham sua du lieu giang vien
bool manggiangvien::fix()
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
		cout << " Sua theo : mgv - hoten - ngaysinh - lop - khoa - gioitinh " << endl;
		cout << "Column: ";
		cin >> s;
		if (strcmp(s, "mgv") == 0)
		{
			giangvien moi;
			cout << "MGV: ";
			cin >> moi.mgv;
			if (trungmgv(moi) == true)
				return false;
			strcpy(data[p - 1].mgv, moi.mgv);
			return true;
		}
		else if (strcmp(s, "hoten") == 0)
		{
			char hoten[18];
			cout << "Ho Va Ten: ";
			cin.ignore(255, '\n');
			cin.get(hoten, 18);
			chuan_hoa1(hoten);
			strcpy(data[p - 1].hoten, hoten);
			return true;
		}
		else if (strcmp(s, "ngaysinh") == 0)
		{
			cout << "Ngay Thang Nam Sinh:\n";
			date1 ns;
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
		else if (strcmp(s, "songaylam") == 0)
		{
			giangvien moi;
			cout << "SNL: ";
			cin >> moi.songaylam;
		//	strcpy(data[p - 1].songaylam,moi.songaylam);
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

};

//ham tim kiem ten sv
int manggiangvien::search(char s[30])
{
	int key = -1;
	chuan_hoa1(s);

	for (int i = 0; i < n; i++)
		if (strcmp(data[i].mgv, s) == 0 | strcmp(data[i].hoten, s) == 0)
			return i;

	return -1;
}
// ham sap xep
void manggiangvien::sort(char type[10])
{
	if (strcmp(type, "mgv") == 0)
	{
		for (int i = 0; i < n - 1; i++)
		{
			int min = i;
			for (int j = i + 1; j < n; j++)
				if (strcmp(data[j].mgv, data[min].mgv) < 0)
					min = j;
			giangvien tg = data[min];
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
			giangvien tg = data[min];
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
// ham tinh luong cua giang vien
float manggiangvien::luong (float &a)
{  
 
	for (int i = 0; i < n; i++)
	{
		cout << "\n\n\t\t TIEN LUONG GIANG VIEN THU " << i + 1 << " la : ";
		cout << "\n\n\t\t\t\t" << data[i].songaylam * a << endl;
	}
	return a ;
}


// ket thuc
/*
int main()
{
	
	manggiangvien b;
	char k[10];
	char cmd[30];
	cout << "--------------------***CHUONG TRINH QUAN LY GiANG VIEN***-----------------------" << endl;
    cout << "\t\t\t=================MENU================\n";
	cout << "\t1.add: Them thong tin 1 Giang vien\n";
	cout << "\t2.remove: Xoa thong tin 1 giang vien\n";
	cout << "\t3.load:Xuat thong tin file txt co trong source \n";
	cout << "\t4.search: Tim kiem thong tin giang vien theo ma sinh vien va ho ten\n";
	cout << "\t5.save: Luu thong tin giang vien va xuat file txt\n";
	cout << "\t6.print: In thong tin giang vien\n";
	cout << "\t7.fix: Sua thong tin giang vien\n";
	cout << "\t8.sort: Sap xep thong tin theo ma giang vien hoac ho ten \n";
	cout << "\t9.money:Tinh tien luong cua tung giang vien\n";
	cout << "\t10.exit: THOAT !!!\n"; 
	while (true)
	{
		cout << "Nhap lua chon cua ban : ";
		cin >> cmd;
		if (strcmp(cmd, "1") == 0)
		{
			int p;
			giangvien moi;
			cout << "Nhap du lieu cho sinh vien can bo sung:\n";
			//cout<<moi;
			cin >> moi;
			while (b.trungmgv(moi) != false)
			{
				cout << "MSV nay da TON TAI, Yeu cau nhap lai MSV: ";
				cin >> moi.mgv;
			}

		//	do
		//	{
				cout << "Nhap vi chi muon chen:";
				cin >> p;
		//		if (p<0 || p>a.n)
			//		cout << "Vi Tri Khong Hop le,Nhap Lai\n";
		//	} while (p<0 || p>a.n);
           
			b.add(moi, p);
			b.print();
		}
		else if (strcmp(cmd, "2") == 0)
		{
			int kt;
			int keyso;
			char keychu[10];
			cout << "fill out STT or MSV: ";
			cin >> keyso;
			system("pause");
			if (keyso > b.n)
			{
				itoa(keyso, keychu, 10);
				kt = b.remove(keychu);
			}
			else
			{
				kt = b.remove(keyso - 1);
			}
			if (kt == 1)
				b.print();
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
				kt = b.load(filename);
				if (kt == 0)
					cout << "Filename is not exsit, Try agian!\n";
			} while (kt == 0);

			b.print();
			cout << filename << endl;
		}
		else if (strcmp(cmd, "4") == 0)
		{
			char s[50];
			cout << "Nhap thong tin can tim: ";
			cin.ignore(255, '\n');
			cin.get(s, 50);
			int kt = b.search(s);
			if (kt == -1)
			{
				system("cls");
				b.print();
				cout << "Kieu du lieu khong ton tai!\n---------------------\n";
			}

			else
			{
				system("cls");
				cout << "--------------------***CHUONG TRINH QUAN LY GiANG VIEN***-----------------------" << endl;
    cout << "\t\t\t=================MENU================\n";
	cout << "\t1.add: Them thong tin 1 Giang vien\n";
	cout << "\t2.remove: Xoa thong tin 1 giang vien\n";
	cout << "\t3.load:Xuat thong tin file txt co trong source \n";
	cout << "\t4.search: Tim kiem thong tin giang vien theo ma sinh vien va ho ten\n";
	cout << "\t5.save: Luu thong tin giang vien va xuat file txt\n";
	cout << "\t6.print: In thong tin giang vien\n";
	cout << "\t7.fix: Sua thong tin giang vien\n";
	cout << "\t8.sort: Sap xep thong tin theo ma giang vien hoac ho ten \n";
	cout << "\t9.money:Tinh tien luong cua tung giang vien\n";
	cout << "\t10.exit: THOAT !!!\n"; 
	
				cout << char(201);
				for (int i = 0; i < 78; i++)
				{
					if (i == 4 || i == 15 || i == 35 || i == 52 || i == 59 || i == 67)
						cout << char(203);
					else
						cout << char(205);
				}
				cout << char(187);
				cout << char(186) << setw(4) << left << "STT" << setw(2) << left << char(186) << setw(9) << left << "MaSV" << setw(2) << left << char(186) << setw(18) << left << "Ho Va Ten" << setw(2) << left << char(186) << setw(15) << left << "Ngay Sinh" << setw(2) << left << char(186) << setw(5) << left << "SNL" << setw(2) << left << char(186) << setw(6) << left << "Khoa" << setw(2) << left << char(186) << setw(8) << left << "Gioi Tinh" << char(186);
				cout << char(204);
				for (int i = 0; i < 78; i++)
				{
					if (i == 4 || i == 15 || i == 35 || i == 52 || i == 59 || i == 67)
						cout << char(206);
					else
						cout << char(205);
				}
				cout << char(185);
				for (int i = 0; i < b.n; i++)
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

					cout << char(186) << setw(4) << left << i +1 << b.data[i];

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
			cout <<"Chon theo mgv hoac hoten: " ;
			cin >> type;
			b.sort(type);
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
				kt = b.save(filename);
				if (kt == 0)
					cout << "Save file fail,Try agian!\n";
			} while (kt == 0);
			b.print();
			cout << "Luu file thanh cong !\n";
		}
		else if (strcmp(cmd, "10") == 0)
		{
			break;
		}
		else if (strcmp(cmd, "6") == 0)
		{
			b.print();
		}
		else if (strcmp(cmd, "7") == 0)
		{
			bool kt = b.fix();
			b.print();
			if (kt == false)
				cout << "This 'Masv' Is Exsit, Failed To Fix!\n";
		}
	  else if (strcmp(cmd, "9") == 0)
	  {
	  	float a;
		cout << "nhap muc luong toi thieu /h cua giang vien:";
	     cin >> a;
       b.luong(a);
	  }
		else
			cout << "Lua chon " << cmd << " khong ton  tai trong chuong trinh.\n";
	}

	system("pause");
	return 0;
}*/

