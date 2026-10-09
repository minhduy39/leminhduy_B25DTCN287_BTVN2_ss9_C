#include <stdio.h>
#include <string.h>

int main(void) {
    struct FlightTicket {
        char pnrCode[15];
        char passengerName[50];
        int ticketClass;
        float baggageWeight;
        float baggageFee;
    };

    struct FlightTicket danhSachVe[100];
    int soLuong = 0;
    int luaChon, i, j, viTri;
    char pnrInput[15];
    int tiepTuc;

    do {
        printf("\n=== HE THONG BAN VE VA CHECK-IN MAY BAY ===\n");
        printf("1. Them ve may bay moi\n");
        printf("2. Hien thi danh sach ve\n");
        printf("3. Cap nhat hanh ly theo PNR\n");
        printf("4. Xoa ve theo PNR\n");
        printf("5. Thoat\n");
        printf("Lua chon cua ban: ");

        if (scanf("%d", &luaChon) != 1) {
            while (getchar() != '\n');
            printf("Lua chon khong hop le!\n");
            continue;
        }
        while (getchar() != '\n');

        switch (luaChon) {
            case 1:
                if (soLuong >= 100) {
                    printf("Danh sach ve da day, khong the them moi!\n");
                    break;
                }

                printf("Nhap ma PNR: ");
                fgets(danhSachVe[soLuong].pnrCode,
                      sizeof(danhSachVe[soLuong].pnrCode), stdin);
                danhSachVe[soLuong].pnrCode[
                    strcspn(danhSachVe[soLuong].pnrCode, "\n")] = '\0';

                printf("Nhap ho ten hanh khach: ");
                fgets(danhSachVe[soLuong].passengerName,
                      sizeof(danhSachVe[soLuong].passengerName), stdin);
                danhSachVe[soLuong].passengerName[
                    strcspn(danhSachVe[soLuong].passengerName, "\n")] = '\0';

                do {
                    printf("Nhap hang ve (1-Eco, 2-Deluxe, 3-Business): ");
                    if (scanf("%d", &danhSachVe[soLuong].ticketClass) != 1) {
                        while (getchar() != '\n');
                        danhSachVe[soLuong].ticketClass = 0;
                    } else {
                        while (getchar() != '\n');
                    }

                    if (danhSachVe[soLuong].ticketClass < 1 ||
                        danhSachVe[soLuong].ticketClass > 3) {
                        printf("Hang ve khong hop le! Vui long nhap lai.\n");
                    }
                } while (danhSachVe[soLuong].ticketClass < 1 ||
                         danhSachVe[soLuong].ticketClass > 3);

                do {
                    printf("Nhap khoi luong hanh ly (kg): ");
                    if (scanf("%f",
                              &danhSachVe[soLuong].baggageWeight) != 1) {
                        while (getchar() != '\n');
                        danhSachVe[soLuong].baggageWeight = -1;
                    } else {
                        while (getchar() != '\n');
                    }

                    if (danhSachVe[soLuong].baggageWeight < 0) {
                        printf("Khoi luong khong hop le! Vui long nhap lai.\n");
                    }
                } while (danhSachVe[soLuong].baggageWeight < 0);

                if (danhSachVe[soLuong].ticketClass == 3 ||
                    danhSachVe[soLuong].baggageWeight <= 7.0f) {
                    danhSachVe[soLuong].baggageFee = 0.0f;
                } else {
                    danhSachVe[soLuong].baggageFee =
                        (danhSachVe[soLuong].baggageWeight - 7.0f) * 50000.0f;
                }

                printf("Them ve thanh cong! Cuoc phat hanh ly qua can: %.0f VNÐ.\n",
                       danhSachVe[soLuong].baggageFee);

                soLuong++;
                break;

            case 2:
                if (soLuong == 0) {
                    printf("Danh sach ve dang rong!\n");
                    break;
                }

                printf("\n================ DANH SACH VE MAY BAY ================\n");
                printf("%-5s %-15s %-25s %-12s %-15s %-18s\n",
                       "STT", "Ma PNR", "Ho ten hanh khach",
                       "Hang ve", "Hanh ly (kg)", "Cuoc qua can");
                printf("--------------------------------------------------------------------------"
                       "----------------\n");

                for (i = 0; i < soLuong; i++) {
                    const char *tenHangVe;

                    if (danhSachVe[i].ticketClass == 1) {
                        tenHangVe = "Eco";
                    } else if (danhSachVe[i].ticketClass == 2) {
                        tenHangVe = "Deluxe";
                    } else {
                        tenHangVe = "Business";
                    }

                    printf("%-5d %-15s %-25s %-12s %-15.1f %-18.0f VNÐ\n",
                           i + 1,
                           danhSachVe[i].pnrCode,
                           danhSachVe[i].passengerName,
                           tenHangVe,
                           danhSachVe[i].baggageWeight,
                           danhSachVe[i].baggageFee);
                }

                printf("=========================================================================="
                       "================\n");
                break;

            case 3:
                if (soLuong == 0) {
                    printf("Danh sach ve dang rong!\n");
                    break;
                }

                printf("Nhap ma PNR can cap nhat hanh ly: ");
                fgets(pnrInput, sizeof(pnrInput), stdin);
                pnrInput[strcspn(pnrInput, "\n")] = '\0';

                viTri = -1;
                for (i = 0; i < soLuong; i++) {
                    if (strcmp(danhSachVe[i].pnrCode, pnrInput) == 0) {
                        viTri = i;
                        break;
                    }
                }

                if (viTri == -1) {
                    printf("Khong tim thay ve co ma PNR da nhap!\n");
                } else {
                    printf("Tim thay hanh khach: %s\n",
                           danhSachVe[viTri].passengerName);

                    do {
                        printf("Nhap trong luong hanh ly moi (kg): ");
                        if (scanf("%f",
                                  &danhSachVe[viTri].baggageWeight) != 1) {
                            while (getchar() != '\n');
                            danhSachVe[viTri].baggageWeight = -1;
                        } else {
                            while (getchar() != '\n');
                        }

                        if (danhSachVe[viTri].baggageWeight < 0) {
                            printf("Khoi luong khong hop le! Vui long nhap lai.\n");
                        }
                    } while (danhSachVe[viTri].baggageWeight < 0);

                    if (danhSachVe[viTri].ticketClass == 3 ||
                        danhSachVe[viTri].baggageWeight <= 7.0f) {
                        danhSachVe[viTri].baggageFee = 0.0f;
                    } else {
                        danhSachVe[viTri].baggageFee =
                            (danhSachVe[viTri].baggageWeight - 7.0f)
                            * 50000.0f;
                    }

                    printf("Cap nhat thanh cong! Phi hanh ly qua can moi: %.0f VNÐ.\n",
                           danhSachVe[viTri].baggageFee);
                }
                break;

            case 4:
                if (soLuong == 0) {
                    printf("Danh sach ve dang rong!\n");
                    break;
                }

                printf("Nhap ma PNR can xoa: ");
                fgets(pnrInput, sizeof(pnrInput), stdin);
                pnrInput[strcspn(pnrInput, "\n")] = '\0';

                viTri = -1;
                for (i = 0; i < soLuong; i++) {
                    if (strcmp(danhSachVe[i].pnrCode, pnrInput) == 0) {
                        viTri = i;
                        break;
                    }
                }

                if (viTri == -1) {
                    printf("Khong tim thay ve co ma PNR da nhap!\n");
                } else {
                    for (j = viTri; j < soLuong - 1; j++) {
                        danhSachVe[j] = danhSachVe[j + 1];
                    }

                    soLuong--;

                    printf("Da xoa thanh cong ve co ma PNR: %s\n", pnrInput);
                }
                break;

            case 5:
                printf("Cam on ban da su dung he thong! Tam biet.\n");
                break;

            default:
                printf("Lua chon khong hop le! Vui long chon tu 1 den 5.\n");
        }

    } while (luaChon != 5);

    return 0;
}
