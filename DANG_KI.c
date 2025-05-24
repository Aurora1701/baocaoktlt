#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>

#define TEN_TEP "taikhoan.txt"

char username[100], password[100], email[100];

int chuHoa(char c) {
	return c >= 'A' && c <= 'Z';
}

int chuThuong(char c) {
	return c >= 'a' && c <= 'z'; 
}

int chuSo(char c) {
	return c >= '0' && c <= '9';	
}

int matKhauHopLe(char *mk) {
	if(strlen(mk) < 8) return 0;
	int hoa = 0, thuong = 0, so = 0;
	for(int i = 0; mk[i] != '\0'; i++) {
		if(chuHoa(mk[i])) hoa = 1;
		if(chuThuong(mk[i])) thuong = 1;
		if(chuSo(mk[i])) so = 1;
	}	
	return hoa && thuong && so;
}

void nhapMatKhau(char *mk) {
	int i = 0;   
    char ch;
    while (1) {
        ch = getch();
        if (ch == 13) break; // Enter
        if (ch == 8) {
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        } else {
            if (i < 99) {
                mk[i++] = ch;
                printf("*");
            }
        }
    }
    mk[i] = '\0';
    printf("\n");
}

void dangKi() {
    char tenDangNhap[100], matKhau[100], xacNhan[100], emailNguoiDung[100];

    printf("\n=== Dang ky tai khoan moi ===\n");

    do {
        printf("Nhap ten dang nhap (>= 5 ky tu): ");
        scanf("%s", tenDangNhap);
        if (strlen(tenDangNhap) < 5) {
            printf(">> Ten dang nhap qua ngan. Vui long nhap lai.\n");
        }
    } while (strlen(tenDangNhap) < 5);

    printf("Nhap dia chi email: ");
    scanf("%s", emailNguoiDung);

    while (1) {
        printf("Nhap mat khau (>=8 ky tu, co chu hoa, thuong, so): ");
        nhapMatKhau(matKhau);

        printf("Xac nhan lai mat khau: ");
        nhapMatKhau(xacNhan);

        if (strcmp(matKhau, xacNhan) != 0) {
            printf(">> Mat khau xac nhan khong khop. Vui long thu lai.\n");
        } else if(!matKhauHopLe(matKhau)) {
            printf(">> Mat khau chua dat yeu cau. Vui long thu lai.\n");
        } else {
            break;
        }
    }

    FILE *f = fopen(TEN_TEP, "w");
    if (!f) {
        printf(">> Loi khi mo file.\n");
        return;
    }
    fprintf(f, "%s %s %s\n", tenDangNhap, matKhau, emailNguoiDung);
    fclose(f);

    printf(">> Dang ky thanh cong!\n");
}

int dangNhap() {
    char tenNhap[100], matKhauNhap[100];
    char tenFile[100], mkFile[100], emailFile[100];
    int lanThu = 3;

    FILE *f = fopen(TEN_TEP, "r");
    if (!f) {
        printf(">> Vui long dang ky tai khoan neu chua co tai khoan.\n");
        return 0;
    }
    fscanf(f, "%s %s %s", tenFile, mkFile, emailFile);
    fclose(f);

    printf("\n=== Dang nhap he thong ===\n");
    while (lanThu--) {
        printf("Ten dang nhap: ");
        scanf("%s", tenNhap);
        printf("Mat khau: ");
        nhapMatKhau(matKhauNhap);

        if (strcmp(tenNhap, tenFile) == 0 && strcmp(matKhauNhap, mkFile) == 0) {
            printf(">> Dang nhap thanh cong! Xin chao, %s!\n", tenNhap);
            return 1;
        } else {
            printf(">> Sai thong tin. Con %d lan thu.\n", lanThu);
        }
    }

    printf(">> Ban da nhap sai qua 3 lan. Dang nhap that bai.\n");
    return 0;
}

int yeuCauGuiMK = 0;


//Ham lay lai mat khau
void quenMatKhau() {
    FILE *f = fopen(TEN_TEP, "r");
    if (!f) {
        printf(">> Chua co tai khoan. Vui long dang ky truoc.\n");
        return;
    }

    char tenFile[100], mkFile[100], emailFile[100];
    fscanf(f, "%s %s %s", tenFile, mkFile, emailFile);
    fclose(f);

    char tenNhap[100];
    printf("Nhap ten dang nhap de khoi phuc mat khau: ");
    scanf("%s", tenNhap);

    if (strcmp(tenNhap, tenFile) == 0) {
        printf(">> Mat khau da duoc gui ve email da dang ky. Vui long kiem tra email: %s\n", emailFile);
        yeuCauGuiMK = 1; // Danh dau da yeu cau gui lai mat khau
    } else {
        printf(">> Ten dang nhap khong ton tai. Khong the khoi phuc mat khau.\n");
    }
}

//Xu ly Email nguoi dung
void xuLyEmailNguoiDung()
{
    FILE *f = fopen(TEN_TEP, "r");
    if (!f) {
        printf(">> Chua co tai khoan. Vui long dang ky.\n");
        return;
    }

    char tenFile[100], mkFile[100], emailFile[100];
    fscanf(f, "%s %s %s", tenFile, mkFile, emailFile);
    fclose(f);

    printf(">> Email dang ky cua ban la: %s\n", emailFile);

    if (yeuCauGuiMK) {
        printf(">> Ban da yeu cau khoi phuc mat khau.\n");
        printf(">> Mat khau cua ban la: %s\n", mkFile);
        yeuCauGuiMK = 0;
    } else {
        printf(">> Khong co thong bao moi trong hop thu.\n");
    }
}

int main() {
    int chon;
    do {
        system("cls");
        printf("\n========================================\n");
        printf("|         HE THONG QUAN LY TAI KHOAN   |\n");
        printf("========================================\n");
        printf("| 1. Dang ky tai khoan                 |\n");
        printf("| 2. Dang nhap                         |\n");
        printf("| 3. Quen mat khau                     |\n");
        printf("| 4. Xem email nguoi dung              |\n");
        printf("| 0. Thoat chuong trinh                |\n");
        printf("========================================\n");
        printf(">> Moi ban chon chuc nang: ");
        scanf("%d", &chon);
        switch (chon) {
            case 1:
                dangKi();
                break;
            case 2:
                dangNhap();
                break;
            case 3:
                quenMatKhau();
                break;
            case 0:
                printf(">> Tam biet!\n");
                break;
			case 4:
    			xuLyEmailNguoiDung();
    			break;
 
            default:
                printf(">> Lua chon khong hop le.\n");
        }
    } while(chon != 0);
    return 0;
}
