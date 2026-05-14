#include <graphics.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h> // ����� ������ �����

// ����� ������� ��� ������ �������� ��������
#define DEG2RAD (3.14159265f/180.0f)

// ���� ��� ����� ������
void DrawClockHand(int cx, int cy, float angle, float length, int thickness, int color) {
    int endX = cx + length * sin(angle * DEG2RAD);
    int endY = cy - length * cos(angle * DEG2RAD);

    setcolor(color);
    setlinestyle(SOLID_LINE, 0, thickness);
    line(cx, cy, endX, endY);
}

int main() {
    // 1. ����� ������
    const int screenWidth = 800;
    const int screenHeight = 900;
    initwindow(screenWidth, screenHeight, "Analog & Digital Clock - Amran University");

    int center_x = screenWidth / 2;
    int center_y = screenHeight / 2 - 50;
    float radius = 150.0f;

    int page = 0;           // ������ ��� ������
    int last_second = -1;   // ������� ���� ������� ������ �����

    while (true) {
        // ������ �� ��� �� ESC ������
        if (kbhit()) {
            if (getch() == 27) break; 
        }

        // ����� ������ ������ (����� �� �������)
        setactivepage(page);
        
        // ��� ������ ������ ������
        setbkcolor(WHITE);
        cleardevice(); 

        // ��� ����� ������ �� ������
        time_t now = time(0);
        tm *ltm = localtime(&now);

      // --- �� ��� ����� ���� ���� while �� ��� ������ ������ ����� ---

if (ltm->tm_sec != last_second) {
    
    // �������: ����� ����� ��� 100 ���� ����� ������ �������� ���� ������
    if (ltm->tm_sec % 2 == 0) {
        // ��� "���" ��� ����
        Beep(1200, 100); 
    } 
    else {
        // ��� "���" ����� �����
        Beep(900, 100); 
    }

    last_second = ltm->tm_sec; 
}

        // ���� ������� �������
        float secAngle = ltm->tm_sec * 6.0f;
        float minAngle = ltm->tm_min * 6.0f + ltm->tm_sec * 0.1f;
        float hourAngle = (ltm->tm_hour % 12) * 30.0f + ltm->tm_min * 0.5f;

        // 2. ��� ������ ������ ������ (�������)
        setfillstyle(SOLID_FILL, BLACK); 
        bar(center_x - 250, center_y - 300, center_x + 250, center_y + 350);
        
        setcolor(RED);
        setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
        rectangle(center_x - 250, center_y - 300, center_x + 250, center_y + 350);

        // 3. ��� ��� ������ (������� �������)
        setcolor(LIGHTGRAY);
        setfillstyle(SOLID_FILL, LIGHTGRAY);
        fillellipse(center_x, center_y, radius + 5, radius + 5); // ��

        setcolor(WHITE);
        setfillstyle(SOLID_FILL, WHITE);
        fillellipse(center_x, center_y, radius, radius);

        setcolor(RED);
        setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
        circle(center_x, center_y, radius);

        // 4. ��� ������ ������� ��������
        setbkcolor(WHITE); // ����� ��� ���� ������ ��� ����� ������
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
        settextjustify(CENTER_TEXT, CENTER_TEXT);

        for (int i = 0; i < 12; i++) {
            float angle = i * 30.0f;
            int p1x = center_x + (radius * 0.85f) * sin(angle * DEG2RAD);
            int p1y = center_y - (radius * 0.85f) * cos(angle * DEG2RAD);
            int p2x = center_x + radius * sin(angle * DEG2RAD);
            int p2y = center_y - radius * cos(angle * DEG2RAD);

            setcolor(BLACK);
            setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
            line(p1x, p1y, p2x, p2y);

            char num[5];
            sprintf(num, "%d", (i == 0) ? 12 : i);
            int numPosX = center_x + (radius - 30) * sin(angle * DEG2RAD);
            int numPosY = center_y - (radius - 30) * cos(angle * DEG2RAD);
            outtextxy(numPosX, numPosY, num);
        }

        // 5. ��� �������
        DrawClockHand(center_x, center_y, hourAngle, radius - 60, THICK_WIDTH, BLACK);
        DrawClockHand(center_x, center_y, minAngle, radius - 40, THICK_WIDTH, DARKGRAY);
        DrawClockHand(center_x, center_y, secAngle, radius - 20, NORM_WIDTH, RED);

        // ���� ������ (�������)
        setcolor(RED);
        setfillstyle(SOLID_FILL, RED);
        fillellipse(center_x, center_y, 6, 6);

        // 6. ���� ��������� ������� (������ ������� �������)
        int panelY = center_y + radius + 40;
        setfillstyle(SOLID_FILL, BLACK);
        bar(center_x - 190, panelY, center_x + 190, panelY + 140);
        
        setcolor(RED);
        setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
        rectangle(center_x - 190, panelY, center_x + 190, panelY + 140);

        // --- ����� ����� ������ ������� ---
        setbkcolor(BLACK); 

        // ����� ������
        const char* ampm = (ltm->tm_hour >= 12) ? "PM" : "AM";
        int h12 = (ltm->tm_hour % 12 == 0) ? 12 : ltm->tm_hour % 12;
        char timeStr[50];
        sprintf(timeStr, "%02d:%02d:%02d  %s", h12, ltm->tm_min, ltm->tm_sec, ampm);
        
        setcolor(WHITE);
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 4);
        outtextxy(center_x, panelY + 35, timeStr);

        // �����
        const char* days[] = {"SUNDAY", "MONDAY", "TUESDAY", "WEDNESDAY", "THURSDAY", "FRIDAY", "SATURDAY"};
        setcolor(LIGHTGREEN);
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
        outtextxy(center_x, panelY + 80, (char*)days[ltm->tm_wday]);

        // �������
        char dateStr[50];
        sprintf(dateStr, "%02d / %02d / %04d", ltm->tm_mday, ltm->tm_mon + 1, ltm->tm_year + 1900);
        setcolor(YELLOW);
        outtextxy(center_x, panelY + 115, dateStr);

        // �� ������ ���� ������
        setbkcolor(WHITE);
        setcolor(DARKGRAY);
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
        outtextxy(center_x, screenHeight - 40, (char*)"Press ESC to Exit");

        // ����� ������� �����
        setvisualpage(page);
        page = 1 - page;

        delay(50); // ����� ���� ����� �������
    }

    closegraph();
    return 0;
}
