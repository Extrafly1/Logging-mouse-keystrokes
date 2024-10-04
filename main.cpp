#include <Windows.h>
#include <iostream>
using namespace std;

int main()
{
    HWND hwnd = GetForegroundWindow();
    ShowWindow(hwnd, SW_SHOWMAXIMIZED);
   
    HANDLE hin = GetStdHandle(STD_INPUT_HANDLE); // получаем дескриптор
    INPUT_RECORD InputRecord; // используется для возвращения информации о входных сообщениях в консольном входном буфере
    DWORD Events; // unsigned long
    COORD coord; // для координат X, Y

    /*Запретить выделение консоли*/
    DWORD prev_mode;
    GetConsoleMode(hin, &prev_mode);
    SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_EXTENDED_FLAGS | (prev_mode & ~ENABLE_QUICK_EDIT_MODE));

    SetConsoleMode(hin, ENABLE_MOUSE_INPUT); // разрешаем обработку мыши

    short mas[160][40] = { 0 };

    while (true)
    {
        HANDLE hd = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD cd;
        cd.X = 0;
        cd.Y = 0;
        SetConsoleCursorPosition(hd, cd);

        for (int i = 0; i < 40; i++) {
            for (int j = 0; j < 160; j++) {
                switch (mas[j][i])
                {
                case 1: {cout << "1"; break; }
                case 2: {cout << "2"; break; }
                case 3: {cout << "3"; break; }
                default: {cout << " "; break; }
                }
            }
           cout << endl;
        }

        ReadConsoleInput(hin, &InputRecord, 1, &Events); // считывание 

        if (InputRecord.Event.MouseEvent.dwButtonState == MOUSE_WHEELED) // нажато колесико
        {
            coord.X = InputRecord.Event.MouseEvent.dwMousePosition.X;
            coord.Y = InputRecord.Event.MouseEvent.dwMousePosition.Y;
            if (coord.Y < 40 && coord.X < 160) mas[coord.X][coord.Y] = 1;
        }
        else if (InputRecord.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED) // правая кнопка
        {
            coord.X = InputRecord.Event.MouseEvent.dwMousePosition.X;
            coord.Y = InputRecord.Event.MouseEvent.dwMousePosition.Y;
            if (coord.Y < 40 && coord.X < 160) mas[coord.X][coord.Y] = 2;
        }
        else if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) // левая кнопка
        {
            coord.X = InputRecord.Event.MouseEvent.dwMousePosition.X;
            coord.Y = InputRecord.Event.MouseEvent.dwMousePosition.Y;
            if (coord.Y < 40 && coord.X < 160) mas[coord.X][coord.Y] = 3;
        }
        
    }

    return 0;
}
