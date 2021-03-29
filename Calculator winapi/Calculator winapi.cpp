#include <windows.h>
#include <string>
#include <vector>
#include <iomanip> 
#include <math.h>

//NUMBERS def
    #define BTN1 1
    #define BTN2 2
    #define BTN3 3
    #define BTN4 4
    #define BTN5 5
    #define BTN6 6
    #define BTN7 7
    #define BTN8 8
    #define BTN9 9
    #define BTN0 0
    #define BTN_DOT 10
//ACTIONS def
    #define BTN_ADD 11
    #define BTN_SUB 12
    #define BTN_MULTI 13
    #define BTN_DIV 14
    #define BTN_PERC 15
    #define BTN_EQUALS 16
    #define BTN_CH 17
    #define BTN_MODULO 18
    #define BTN_POW 19
    #define BTN_SQRT 20

//MENU def
#define BTN_C 21
#define BTN_BACK 22
//!buttons def

HWND outWindow;
HMENU hMenu;

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
void addControls(HWND);
std::wstring calculate(std::wstring ws);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow)
{
    WNDCLASSW wc = { 0 };

    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;  // windows bg colour
    wc.hCursor = LoadCursor(NULL, IDC_ARROW); //default cursor
    wc.hInstance = hInst;
    wc.lpszClassName = L"myWindowClass";
    wc.lpfnWndProc = WindowProcedure;

    if (!RegisterClassW(&wc)) return -1;

    CreateWindowW(L"myWindowClass", L"CALCULATOR", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 275, 340, NULL, NULL, NULL, NULL);

    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, NULL, NULL))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg)
    {
        case WM_COMMAND:
        {
            wchar_t text[50];
            GetWindowTextW(outWindow, text, 50);
;
            std::wstring ws(text);
            
            switch (wp)
            {
                //BUTTONS
                case BTN1: ws += L"1"; break;
                case BTN2: ws += L"2"; break;
                case BTN3: ws += L"3"; break;
                case BTN4: ws += L"4"; break;
                case BTN5: ws += L"5"; break;
                case BTN6: ws += L"6"; break;
                case BTN7: ws += L"7"; break;
                case BTN8: ws += L"8"; break;
                case BTN9: ws += L"9"; break;
                case BTN0: ws += L"0"; break;
                //!BUTTONS

                //ACTIONS
                case BTN_ADD: ws += L" + "; break;
                case BTN_SUB: ws += L" - "; break;
                case BTN_MULTI: ws += L" * "; break;
                case BTN_DIV: ws += L" / "; break;
                case BTN_PERC: ws += L" % "; break;
                case BTN_DOT: ws += L","; break;
                case BTN_MODULO: ws += L" & "; break;
                case BTN_POW: ws += L" ^ "; break;
                case BTN_SQRT: ws += L" SQRT "; break;
                case BTN_EQUALS:
                {
                    ws = calculate(ws);
                }break;
                //!ACTIONS
               
                //MENU
                case BTN_C: ws = L""; break;
                case BTN_BACK: ws = ws.substr(0, ws.size() - 1); break;
                //!MENU

            }
            //Setting value of output window
            SetWindowTextW(outWindow, ws.c_str());

        }break;
        case WM_CREATE:
        {
            addControls(hWnd);
        } break;
        case WM_DESTROY:
        {
            PostQuitMessage(0);
        } break;

        default:
            return DefWindowProcW(hWnd, msg, wp, lp);
    }
}

void addControls(HWND hWnd)
{
    outWindow = CreateWindowW(L"static", L" ", WS_BORDER | WS_VISIBLE | WS_CHILD | SS_RIGHT | SS_CENTERIMAGE, 0, 0, 250, 50, hWnd, NULL, NULL, NULL);
    
    //NUMERIC BUTTONS
    CreateWindowW(L"button", L" 7 ", WS_BORDER | WS_VISIBLE | WS_CHILD | SS_CENTER, 0, 100, 50, 50, hWnd, (HMENU)BTN7, NULL, NULL);
    CreateWindowW(L"button", L" 8 ", WS_BORDER | WS_VISIBLE | WS_CHILD | SS_CENTER, 50, 100, 50, 50, hWnd, (HMENU)BTN8, NULL, NULL);
    CreateWindowW(L"button", L" 9 ", WS_BORDER | WS_VISIBLE | WS_CHILD | SS_CENTER, 100, 100, 50, 50, hWnd, (HMENU)BTN9, NULL, NULL);

    CreateWindowW(L"button", L" 4 ", WS_BORDER | WS_VISIBLE | WS_CHILD | SS_CENTER, 0, 150, 50, 50, hWnd, (HMENU)BTN4, NULL, NULL);
    CreateWindowW(L"button", L" 5 ", WS_BORDER | WS_VISIBLE | WS_CHILD | SS_CENTER, 50, 150, 50, 50, hWnd, (HMENU)BTN5, NULL, NULL);
    CreateWindowW(L"button", L" 6 ", WS_BORDER | WS_VISIBLE | WS_CHILD | SS_CENTER, 100, 150, 50, 50, hWnd, (HMENU)BTN6, NULL, NULL);

    CreateWindowW(L"button", L" 1 ", WS_BORDER | WS_VISIBLE | WS_CHILD | SS_CENTER, 0, 200, 50, 50, hWnd, (HMENU)BTN1, NULL, NULL);
    CreateWindowW(L"button", L" 2 ", WS_BORDER | WS_VISIBLE | WS_CHILD | SS_CENTER, 50, 200, 50, 50, hWnd, (HMENU)BTN2, NULL, NULL);
    CreateWindowW(L"button", L" 3 ", WS_BORDER | WS_VISIBLE | WS_CHILD | SS_CENTER, 100, 200, 50, 50, hWnd, (HMENU)BTN3, NULL, NULL);

    CreateWindowW(L"button", L" +/- ", WS_BORDER | WS_VISIBLE | WS_CHILD | SS_CENTER, 0, 250, 50, 50, hWnd, (HMENU)BTN_CH, NULL, NULL);
    CreateWindowW(L"button", L" 0 ", WS_BORDER | WS_VISIBLE | WS_CHILD | SS_CENTER, 50, 250, 50, 50, hWnd, (HMENU)BTN0, NULL, NULL);
    CreateWindowW(L"button", L".", WS_BORDER | WS_VISIBLE | WS_CHILD | SS_CENTER, 100, 250, 50, 50, hWnd, (HMENU)BTN_DOT, NULL, NULL);

    //ACTIONS
    CreateWindowW(L"button", L" + ", WS_BORDER | WS_VISIBLE | WS_CHILD | SS_CENTER, 150, 200, 100, 50, hWnd, (HMENU)BTN_ADD, NULL, NULL);
    CreateWindowW(L"button", L" - ", WS_BORDER | WS_VISIBLE | WS_CHILD | SS_CENTER, 150, 150, 50, 50, hWnd, (HMENU)BTN_SUB, NULL, NULL);
    CreateWindowW(L"button", L" * ", WS_BORDER | WS_VISIBLE | WS_CHILD | SS_CENTER, 150, 100, 50, 50, hWnd, (HMENU)BTN_MULTI, NULL, NULL);
    CreateWindowW(L"button", L" / ", WS_BORDER | WS_VISIBLE | WS_CHILD | SS_CENTER, 100, 50, 50, 50, hWnd, (HMENU)BTN_DIV, NULL, NULL);
    CreateWindowW(L"button", L" % ", WS_BORDER | WS_VISIBLE | WS_CHILD | SS_CENTER, 50, 50, 50, 50, hWnd, (HMENU)BTN_PERC, NULL, NULL);
    CreateWindowW(L"button", L"Mod.", WS_BORDER | WS_VISIBLE | WS_CHILD | SS_CENTER, 200, 50, 50, 50, hWnd, (HMENU)BTN_MODULO, NULL, NULL);
    CreateWindowW(L"button", L"POW", WS_BORDER | WS_VISIBLE | WS_CHILD | SS_CENTER, 200, 100, 50, 50, hWnd, (HMENU)BTN_POW, NULL, NULL);
    CreateWindowW(L"button", L"SQRT", WS_BORDER | WS_VISIBLE | WS_CHILD | SS_CENTER, 200, 150, 50, 50, hWnd, (HMENU)BTN_SQRT, NULL, NULL);
    CreateWindowW(L"button", L" = ", WS_BORDER | WS_VISIBLE | WS_CHILD | SS_CENTER, 150, 250, 100, 50, hWnd, (HMENU)BTN_EQUALS, NULL, NULL);

    //MENU
    CreateWindowW(L"button", L" C ", WS_BORDER | WS_VISIBLE | WS_CHILD | SS_CENTER, 0, 50, 50, 50, hWnd, (HMENU)BTN_C, NULL, NULL);
    CreateWindowW(L"button", L"<--", WS_BORDER | WS_VISIBLE | WS_CHILD | SS_CENTER, 150, 50, 50, 50, hWnd, (HMENU)BTN_BACK, NULL, NULL);
    
}

std::wstring calculate(std::wstring operation)
{
    std::wstring ws = operation;
    std::vector<float> numbers;
    float result = 0.f;
    std::setprecision(3);

    for (int i = 0; i < ws.size(); i++)
    {
        switch(ws[i])
        {
        case '+':
            {
                numbers.push_back(std::stoi(ws.substr(0, i)));
                numbers.push_back(std::stoi(ws.substr(i+1, ws.size())));
                ws = std::to_wstring(numbers[0] + numbers[1]).c_str();
            }
            break;
        case '-':
                numbers.push_back(std::stoi(ws.substr(0, i)));
                numbers.push_back(std::stoi(ws.substr(i + 1, ws.size())));
                ws = std::to_wstring(numbers[0] - numbers[1]).c_str();
            break;
        case '*':
                numbers.push_back(std::stoi(ws.substr(0, i)));
                numbers.push_back(std::stoi(ws.substr(i + 1, ws.size())));
                ws = std::to_wstring(numbers[0] * numbers[1]).c_str();;
            break;
        case '/':
                numbers.push_back(std::stoi(ws.substr(0, i)));
                numbers.push_back(std::stoi(ws.substr(i + 1, ws.size())));
                ws = std::to_wstring(numbers[0] / numbers[1]).c_str();
            break;
        case '%':
                numbers.push_back(std::stoi(ws.substr(0, i)));
                numbers.push_back(std::stoi(ws.substr(i + 1, ws.size())));
                ws = std::to_wstring((numbers[0] / 100) * numbers[1]).c_str();
            break;

        case '&':
            numbers.push_back(std::stoi(ws.substr(0, i)));
            numbers.push_back(std::stoi(ws.substr(i + 1, ws.size())));
            ws = std::to_wstring(numbers[0] / numbers[1]).c_str();
            break;
        case '^':
            numbers.push_back(std::stoi(ws.substr(0, i)));
            numbers.push_back(std::stoi(ws.substr(i + 1, ws.size())));
            ws = std::to_wstring(std::pow(numbers[0], numbers[1])).c_str();
            break;
        case 'S':
            numbers.push_back(std::stoi(ws.substr(0, i)));
            ws = std::to_wstring(std::sqrt(numbers[0])).c_str();
            break;
        }
    }

    return ws;
}
