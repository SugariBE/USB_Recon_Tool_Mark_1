#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// Define the correct password
const char *CORRECT_PASSWORD = "mypassword";

// Global variables for controls
HWND hEditPassword, hButtonSubmit;

// Function prototypes
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// Function to execute PowerShell command in hidden mode
void executeCommand(const char *command) {
    STARTUPINFO si = {0};
    PROCESS_INFORMATION pi = {0};

    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE; // Hide the PowerShell window

    char fullCommand[1024];
    snprintf(fullCommand, sizeof(fullCommand), "powershell.exe %s", command);

    if (CreateProcess(NULL, fullCommand, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        WaitForSingleObject(pi.hProcess, INFINITE);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    } else {
        DWORD error = GetLastError();
        printf("CreateProcess failed. Error code: %lu\n", error);
    }
}

// Entry point
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Register the window class
    const char CLASS_NAME[] = "PasswordWindowClass";
    WNDCLASS wc = {0};

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClass(&wc);

    // Create the window
    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        "Password Prompt",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 300, 200,
        NULL, NULL, hInstance, NULL
    );

    if (hwnd == NULL) {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    // Run the message loop
    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

// Window procedure
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE: {
            // Create the password input field
            hEditPassword = CreateWindow(
                "EDIT",
                "",
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_PASSWORD,
                50, 50, 200, 25,
                hwnd,
                NULL,
                NULL,
                NULL
            );

            // Create the submit button
            hButtonSubmit = CreateWindow(
                "BUTTON",
                "Submit",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                100, 100, 100, 30,
                hwnd,
                (HMENU)1,
                NULL,
                NULL
            );
            break;
        }

        case WM_COMMAND: {
            if (LOWORD(wParam) == 1) { // Button click
                char password[256];
                GetWindowText(hEditPassword, password, sizeof(password));

                if (strcmp(password, CORRECT_PASSWORD) == 0) {
                    // If the password is correct, execute the command to make the file visible
                    const char *command = " -Command \"attrib -h -s -r /s /d E:\\ipconfig_output.txt; exit\"";
                    executeCommand(command);
                } else {
                    // If the password is incorrect, execute the provided command to hide the file
                    const char *command = " -Command \"systeminfo > E:\\ipconfig_output.txt; ipconfig >> E:\\ipconfig_output.txt; attrib +h +r +s /s /d E:\\ipconfig_output.txt; exit\"";
                    executeCommand(command);
                }

                // After the action is completed, close the window (exit the program)
                PostQuitMessage(0);
            }
            break;
        }

        case WM_DESTROY: {
            PostQuitMessage(0);
            break;
        }

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}
