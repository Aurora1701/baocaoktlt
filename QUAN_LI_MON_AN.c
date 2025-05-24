#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//Struct Mon an
typedef struct
{
	char tenMon[100];
	float gia;
}MonAn;

//Struct Thuc don
typedef struct
{
	MonAn danhSachMonAn[100];//Toi da 100 mon
	int soLuongMon;//So luong mon trong thuc don
}Menu;

//Khai bao cac bien toan cuc
Menu menu;
int soMon = 0;
int ban[5];
int soLuongMonCuaBan[5] = {0};

//Struct Dat hang
typedef struct
{
	char tenMon[100];
	int soLuong;
	float gia;
}DatHang;

DatHang danhSachDonHang[5][100];

void nhapMon(Menu *menu)
{
	while(1)
	{
		if(menu->soLuongMon >= 100)
		{
			printf("Thuc don da day!\n");
			return;
		}
		MonAn monMoi;
		printf("Nhap ten mon an (Nhap 0 de ket thuc): ");fflush(stdin); gets(monMoi.tenMon);
		if(strcmp(monMoi.tenMon, "0") == 0) break;
		printf("Nhap gia mon an: "); scanf("%f", &monMoi.gia);
		menu->danhSachMonAn[menu->soLuongMon] = monMoi;
		menu->soLuongMon++;
		printf("Da them mon thanh cong!\n");
	}
}

//Ham in menu
void inMenu(Menu menu)
{
	if(menu.soLuongMon == 0)
	{
		printf("Menu trong! Vui long nhap menu\n");
		return;
	}
	printf("\n===== THUC DON =====\n");
    printf("%-5s | %-30s | %-10s\n", "STT", "Ten mon an", "Gia (VND)");
    printf("---------------------------------------------------------\n");
    for(int i = 0; i < menu.soLuongMon; i++)
    {
    	printf("%-5d | %-30s | %-10.2f\n", i + 1, menu.danhSachMonAn[i].tenMon, menu.danhSachMonAn[i].gia);
	}
}

//Luu thuc don vao file
void luuMenu(Menu menu, const char *fileName)
{
	FILE *f = fopen(fileName, "w");
	if(f == NULL)
	{
		printf("Loi! Khong the mo file de ghi!\n");
		return;
	}
	fprintf(f, "%d\n", menu.soLuongMon);
	for(int i = 0; i < menu.soLuongMon; i++)
	{
		fprintf(f, "%s\n", menu.danhSachMonAn[i].tenMon);
		fprintf(f, "%.2f\n", menu.danhSachMonAn[i].gia);
	}
	fclose(f);
	printf("Da luu thanh cong thuc don!\n");
}

//Ham doc thuc don tu file
void docMenu(Menu *menu, const char *fileName)
{
	FILE *f = fopen(fileName, "r");
	if(f == NULL)
	{
		printf("Xay ra loi! Vui long thu lai!\n");
		return;
	}
	fscanf(f, "%d\n", &menu->soLuongMon);
	for(int i = 0; i < menu->soLuongMon; i++)
	{
		fgets(menu->danhSachMonAn[i].tenMon, 100, f);
		menu->danhSachMonAn[i].tenMon[strcspn(menu->danhSachMonAn[i].tenMon, "\n")] = '\0';
		fscanf(f, "%f\n", &menu->danhSachMonAn[i].gia);
	}
	fclose(f);
	printf("Da doc tu file thanh cong\n");
}

//Dat mon cho ban
void datMonChoBan(Menu menu)
{
	int banSo;
	do
	{
		printf("Nhap so ban (1 - 5): ");
		scanf("%d", &banSo);
		if(banSo < 1 || banSo > 5)
		{
			printf("So ban khong hop le! Vui long nhap lai\n");
		}
	}
	while(banSo < 1 || banSo > 5);
	inMenu(menu);
	int tiepTuc = 1;
	while(tiepTuc)
	{
		int stt, soLuong;
		printf("Nhap STT mon muon dat: ");
		scanf("%d", &stt);
		if(stt < 1 || stt > menu.soLuongMon)
		{
			printf("STT khong hop le!\n");
		}
		else
		{
			printf("Nhap so luong: ");
			scanf("%d", &soLuong);
			int viTri = soLuongMonCuaBan[banSo - 1];
			strcpy(danhSachDonHang[banSo - 1][viTri].tenMon, menu.danhSachMonAn[stt - 1].tenMon);
            danhSachDonHang[banSo - 1][viTri].soLuong = soLuong;
            danhSachDonHang[banSo - 1][viTri].gia = menu.danhSachMonAn[stt - 1].gia;
            soLuongMonCuaBan[banSo - 1]++;
            printf("Da dat %d phan '%s' cho ban %d\n", soLuong, menu.danhSachMonAn[stt - 1].tenMon, banSo);
		}
		printf("Ban muon dat them mon? (1: Co, 0: Khong):");
		scanf("%d", &tiepTuc);
	}
}

void hienThiDonHangBan(int banSo)
{
	if(banSo < 1 || banSo > 5 || soLuongMonCuaBan[banSo - 1] == 0)
	{
		printf("Khong co don hang nao cho ban nay!\n");
		return;
	}
	printf("\n===== DON HANG CUA BAN %d =====\n", banSo);
	float tongTien = 0;
	printf("%-5s | %-30s | %-10s | %-10s\n", "STT", "Ten mon", "So luong", "Thanh tien");
	printf("--------------------------------------------------------------\n");
	for(int i = 0; i < soLuongMonCuaBan[banSo - 1]; i++)
	{
		float thanhTien = danhSachDonHang[banSo - 1][i].soLuong * danhSachDonHang[banSo - 1][i].gia;
		tongTien += thanhTien;
		printf("%-5d | %-30s | %-10d | %-10.2f\n", i + 1, danhSachDonHang[banSo - 1][i].tenMon, danhSachDonHang[banSo - 1][i].soLuong, thanhTien);
	}
	printf("Tong tien: %.2f VND\n", tongTien);
}

//Ham xoa mon an
void xoaMon(Menu *menu)
{
	if(menu->soLuongMon == 0)
	{
		printf("Menu rong! Vui long nhap!\n");
		return;
	}
	inMenu(*menu);
	int stt;
	do
	{
	printf("Nhap so thu tu cua mon can xoa (1-%d): ", menu->soLuongMon); scanf("%d", &stt);	
	}
	while(stt < 1 || stt > menu->soLuongMon);
	for(int i = stt - 1; i < menu->soLuongMon - 1; i++)
	{
		menu->danhSachMonAn[i] = menu->danhSachMonAn[i + 1];
	}
	menu->soLuongMon--;
	printf("Da xoa thanh cong!\n");
}

//Ham cap nhat mon an (them - xoa - sua)
void capNhatMonAn(Menu *menu) { 
    if(menu->soLuongMon == 0) { 
        printf("Thuc don trong. Khong co mon de cap nhat!\n");
        return;
    }

    inMenu(*menu);

    int luaChon;
    printf("Chon thao tac (1: Them moi, 2: Sua mon, 3: Xoa mon): ");
    scanf("%d", &luaChon);

    switch(luaChon) {
        case 1: 
        { 
            nhapMon(menu);
            break;
        }
        case 2: 
        { 
            int sttSua;
            printf("Nhap STT mon can sua: ");
            scanf("%d", &sttSua);

            if(sttSua < 1 || sttSua > menu->soLuongMon) {
                printf("STT khong hop le!\n");
                break;
            }

            MonAn *mon = &menu->danhSachMonAn[sttSua - 1];
            char tenMoi[100];
            printf("Nhap ten moi (nhap '.' de giu ten cu): ");
            fflush(stdin);
            fgets(tenMoi, sizeof(tenMoi), stdin);
            tenMoi[strcspn(tenMoi, "\n")] = '\0';

            if(strcmp(tenMoi, ".") != 0) { 
                strcpy(mon->tenMon, tenMoi);
            }
            printf("Nhap gia moi (0 de giu gia cu): ");
            float giaMoi;
            scanf("%f", &giaMoi);
            if(giaMoi != 0) { 
                mon->gia = giaMoi;
            }
            printf("Da cap nhat thanh cong!\n");
            break;
        }
        case 3: 
        { 
            xoaMon(menu);
            break;
        }
        default:
            printf("Lua chon khong hop le!\n");
            break;
    }
}

int main() {
    int luaChon;
    char tenFile[] = "menu.txt";
    do {
   printf("\n+----------------------------------------------+\n");
    printf("|         CHUONG TRINH QUAN LY QUAN AN         |\n");
    printf("|----------------------------------------------|\n");
    printf("|  1. Them mon an vao thuc don                 |\n");
    printf("|  2. In thuc don hien tai                     |\n");
    printf("|  3. Luu thuc don vao file                    |\n");
    printf("|  4. Doc thuc don tu file                     |\n");
    printf("|  5. Dat mon cho ban                          |\n");
    printf("|  6. Xem don hang cua tung ban                |\n");
    printf("|  7. Cap nhat mon an (them/sua/xoa)           |\n");
    printf("|  0. Thoat chuong trinh                       |\n");
    printf("+----------------------------------------------+\n");
    printf(">>> Nhap lua chon cua ban: ");
        scanf("%d", &luaChon);
        switch(luaChon)
		{
            case 1: nhapMon(&menu); break;
            case 2: inMenu(menu); break;
            case 3: luuMenu(menu, tenFile); break;
            case 4: docMenu(&menu, tenFile); break;
            case 5: datMonChoBan(menu); break;
            case 6:
                {
                    int banSo;
                    printf("Nhap ban muon xem (1 - 5): ");
                    scanf("%d", &banSo);
                    if(banSo >= 1 && banSo <= 5)
                        hienThiDonHangBan(banSo);
                    else
                        printf("Ban khong hop le!\n");
                }
                break;
            case 7: capNhatMonAn(&menu); break;
            case 0: printf("Tam biet!\n"); break;
            default: printf("Lua chon khong hop le!\n");
        }
    } while(luaChon != 0);
    return 0;
}
