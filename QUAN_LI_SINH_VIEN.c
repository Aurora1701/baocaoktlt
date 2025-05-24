#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct SinhVien
{
    char mssv[10];
    char hoten[50];
    float diem;
    struct SinhVien *next;
} SinhVien;

// Them sinh vien vao danh sach theo thu tu tang dan cua MSSV
void themSV(SinhVien **head)
{
    SinhVien *sv = (SinhVien *)malloc(sizeof(SinhVien));
    if (!sv)
    {
        printf("Khong cap phat duoc bo nho.\n");
        return;
    }

    printf("Nhap MSSV: ");
    fgets(sv->mssv, 10, stdin);
    sv->mssv[strcspn(sv->mssv, "\n")] = '\0';
    printf("Nhap ho ten: ");
    fgets(sv->hoten, 50, stdin);
    sv->hoten[strcspn(sv->hoten, "\n")] = '\0';
    printf("Nhap diem: ");
    scanf("%f", &sv->diem);
    getchar();

    sv->next = NULL;

    if (*head == NULL || strcmp(sv->mssv, (*head)->mssv) < 0)
    {
        sv->next = *head;
        *head = sv;
        return;
    }

    SinhVien *p = *head;
    while (p->next != NULL && strcmp(sv->mssv, p->next->mssv) > 0)
        p = p->next;

    sv->next = p->next;
    p->next = sv;
}

// Hien thi danh sach sinh vien
void hienthi(SinhVien *head)
{
    printf("\n%-10s %-30s %-5s\n", "MSSV", "Ho Ten", "Diem");
    while (head != NULL)
    {
        printf("%-10s %-30s %.2f\n", head->mssv, head->hoten, head->diem);
        head = head->next;
    }
}

// Tim sinh vien theo MSSV
SinhVien *timSV(SinhVien *head, char *mssv)
{
    while (head != NULL)
    {
        if (strcmp(head->mssv, mssv) == 0)
            return head;
        head = head->next;
    }
    return NULL;
}

// Xoa sinh vien theo MSSV
void xoaSV(SinhVien **head, char *mssv)
{
    SinhVien *p = *head;
    SinhVien *truoc = NULL;

    while (p != NULL && strcmp(p->mssv, mssv) != 0)
    {
        truoc = p;
        p = p->next;
    }

    if (p == NULL)
    {
        printf("Khong tim thay sinh vien.\n");
        return;
    }

    if (truoc == NULL)
    {
        *head = p->next;
    }
    else
    {
        truoc->next = p->next;
    }

    free(p);
    printf("Da xoa sinh vien co MSSV %s.\n", mssv);
}

// Tim sinh vien co diem cao nhat
void timDiemCaoNhat(SinhVien *head)
{
    if (head == NULL)
    {
        printf("Danh sach rong.\n");
        return;
    }

    float max = head->diem;
    SinhVien *p = head->next;

    while (p != NULL)
    {
        if (p->diem > max)
            max = p->diem;
        p = p->next;
    }

    printf("Sinh vien co diem cao nhat:\n");
    p = head;
    while (p != NULL)
    {
        if (p->diem == max)
            printf("%-10s %-30s %.2f\n", p->mssv, p->hoten, p->diem);
        p = p->next;
    }
}

// Tim sinh vien theo khoang diem
void timTheoKhoangDiem(SinhVien *head, float min, float max)
{
    int found = 0;
    printf("Danh sach sinh vien trong khoang diem tren:");
    printf("\n%-10s %-30s %-5s\n", "MSSV", "Ho Ten", "Diem");
    while (head != NULL)
    {
        if (head->diem >= min && head->diem <= max)
        {
            printf("%-10s %-30s %.2f\n", head->mssv, head->hoten, head->diem);
            found = 1;
        }
        head = head->next;
    }
    if (!found)
        printf("Khong co sinh vien nao trong khoang diem nay.\n");
}

void tachDanhSach(SinhVien *goc, SinhVien **dat, SinhVien **khongdat)
{
    while (goc != NULL)
    {
        SinhVien *sv = (SinhVien *)malloc(sizeof(SinhVien));
        if (!sv)
        {
            printf("Khong du bo nho.\n");
            return;
        }
        strcpy(sv->mssv, goc->mssv);
        strcpy(sv->hoten, goc->hoten);
        sv->diem = goc->diem;
        sv->next = NULL;

        if (sv->diem >= 5)
        {
            sv->next = *dat;
            *dat = sv;
        }
        else
        {
            sv->next = *khongdat;
            *khongdat = sv;
        }
        goc = goc->next;
    }
}

// Ghi danh sach sinh vien vao file
void ghiDanhSachVaoFile(SinhVien *head, const char *filename)
{
    FILE *f = fopen(filename, "w");
    if (!f)
    {
        printf("Khong mo duoc file %s\n", filename);
        return;
    }
    while (head != NULL)
    {
        fprintf(f, "%s,%s,%.2f\n", head->mssv, head->hoten, head->diem);
        head = head->next;
    }
    fclose(f);
    printf("Da ghi danh sach vao %s\n", filename);
}

// Giai phong bo nho
void giaiPhong(SinhVien *head)
{
    SinhVien *temp;
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}

//nhap sinh vien lien tuc
void nhapSinhVienLienTuc(SinhVien **head)
{
    printf("\n=== Nhap sinh vien (Nhan ESC de dung) ===\n");
    while (1)
    {
        themSV(head);

        printf("Nhan ESC de dung, phim bat ky de tiep tuc...\n");
        char c = getch();
        if (c == 27)
        {
            printf("Da thoat nhap sinh vien.\n");
            break;
        }
    }
}

int main()
{
    SinhVien *danhsach = NULL;
    int choice;
    char mssv[10];

    do
    {
        system("cls");
        printf("\n==============================================\n");
        printf("|         CHUONG TRINH QUAN LY SINH VIEN     |\n");
        printf("==============================================\n");
        printf("| 1. Nhap sinh vien lien tuc                 |\n");
        printf("| 2. Hien thi danh sach                      |\n");
        printf("| 3. Tim sinh vien theo MSSV                 |\n");
        printf("| 4. Xoa sinh vien theo MSSV                 |\n");
        printf("| 5. Tim sinh vien diem cao nhat             |\n");
        printf("| 6. Tim sinh vien theo khoang diem          |\n");
        printf("| 7. Tach danh sach va ghi ra file           |\n");
        printf("| 0. Thoat chuong trinh                      |\n");
        printf("==============================================\n");
        printf(">> Moi ban chon chuc nang: ");
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 1:
            nhapSinhVienLienTuc(&danhsach);
            break;
        case 2:
            printf("---Danh sach sinh vien---");
            hienthi(danhsach);
            break;
        case 3:
            printf("Nhap MSSV can tim: ");
            fgets(mssv, 10, stdin);
            mssv[strcspn(mssv, "\n")] = '\0';
            {
                SinhVien *sv = timSV(danhsach, mssv);
                if (sv)
                {
                    printf("Da tim thay sinh vien co MSSV %d",mssv);
                    printf("%-10s %-30s %.2f\n", sv->mssv, sv->hoten, sv->diem);
            	}
                else
                    printf("Khong tim thay sinh vien co ma so tren.\n");
            }
            break;
        case 4:
            printf("Nhap MSSV can xoa: ");
            fgets(mssv, 10, stdin);
            mssv[strcspn(mssv, "\n")] = '\0';
            xoaSV(&danhsach, mssv);
            break;
        case 5:
            timDiemCaoNhat(danhsach);
            break;
        case 6:
        {
            float min, max;
            printf("Nhap diem toi thieu: ");
            scanf("%f", &min);
            printf("Nhap diem toi da: ");
            scanf("%f", &max);
            getchar();
            if (min > max)
            {
                float tmp = min;
                min = max;
                max = tmp;
            }
            timTheoKhoangDiem(danhsach, min, max);
            break;
        }
        case 7:
        {
            SinhVien *dsDat = NULL;
            SinhVien *dsKhongDat = NULL;

            tachDanhSach(danhsach, &dsDat, &dsKhongDat);

            // Hien thi ket qua
            printf("\n=== Danh sach DAT ===\n");
            hienthi(dsDat);

            printf("\n=== Danh sach KHONG DAT ===\n");
            hienthi(dsKhongDat);

            // Ghi file
            ghiDanhSachVaoFile(dsDat, "dat.txt");
            ghiDanhSachVaoFile(dsKhongDat, "khongdat.txt");

            // Giai phong bo nho 
            giaiPhong(dsDat);
            giaiPhong(dsKhongDat);

            break;
        }
        case 0:
            printf("Ket thuc chuong trinh.\n");
            break;
        default:
            printf("Lua chon khong hop le!\n");
        }
    } while (choice != 0);

    giaiPhong(danhsach);
    return 0;
}
