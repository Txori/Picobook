/*
    PicobookX, by Etienne Bégué - www.txori.com
    Launch Picotron by Lexaloffle at the correct screen resolution on the
    Chuwi Minibook X, then switch back to the original resolution upon exit

    Compile using w64devkit (https://github.com/skeeto/w64devkit):
    g++ -O3 -std=c++17 -o picobook.exe picobook.cpp -lstdc++fs
*/

#include <iostream>
#include <windows.h>

// Screen resolution of the Chuwi Minibook X
constexpr int SCREEN_WIDTH = 1440;
constexpr int SCREEN_HEIGHT = 900;

// Screen resolution of the Picotron 480x270 (x3)
constexpr int PICOTRON_WIDTH = 1440;
constexpr int PICOTRON_HEIGHT = 810;

// Function prototypes
bool ChangeResolution(int width, int height);
void RestoreResolution();
bool RunApplication(const std::wstring& appPath);

int main() {
    std::cout << "Starting Picobook..." << std::endl;

    // Save the current screen resolution
    DEVMODE originalDevMode = {};
    originalDevMode.dmSize = sizeof(DEVMODE);
    if (!EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &originalDevMode)) {
        std::cerr << "Failed to retrieve current display settings. Error: " << GetLastError() << std::endl;
        return 1;
    }
    std::cout << "Current resolution: " << originalDevMode.dmPelsWidth << "x" << originalDevMode.dmPelsHeight << std::endl;

    // Change the screen resolution
    if (!ChangeResolution(SCREEN_WIDTH, SCREEN_HEIGHT)) {
        std::cerr << "Failed to change screen resolution." << std::endl;
        return 1; // Exit if resolution change failed
    }

    // Calculate the rectangle to clip the mouse cursor
    RECT clipRect;
    clipRect.left = 0;
    clipRect.top = (SCREEN_HEIGHT - PICOTRON_HEIGHT) / 2; // Adjust to center vertically
    clipRect.right = PICOTRON_WIDTH;
    clipRect.bottom = clipRect.top + PICOTRON_HEIGHT;

    // Run the Picotron application
    if (!RunApplication(L".\\picotron.exe")) {
        std::cerr << "Failed to execute picotron.exe." << std::endl;
        RestoreResolution(); // Restore resolution before exiting
        return 1;
    }

    // Restore the original screen resolution
    RestoreResolution();
    std::cout << "Screen resolution restored to " << originalDevMode.dmPelsWidth << "x" << originalDevMode.dmPelsHeight << std::endl;

    return 0;
}

// Function to change the screen resolution
bool ChangeResolution(int width, int height) {
    DEVMODE devMode = {};
    devMode.dmSize = sizeof(DEVMODE);
    devMode.dmPelsWidth = width;
    devMode.dmPelsHeight = height;
    devMode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;

    LONG result = ChangeDisplaySettings(&devMode, CDS_FULLSCREEN);
    if (result != DISP_CHANGE_SUCCESSFUL) {
        std::cerr << "Failed to change screen resolution. Error: " << result << std::endl;
        return false;
    }
    std::cout << "Resolution changed to " << width << "x" << height << std::endl;
    return true;
}

// Function to restore the original screen resolution
void RestoreResolution() {
    ChangeDisplaySettings(NULL, 0);
}

// Function to run the Picotron application
bool RunApplication(const std::wstring& appPath) {
    std::wcout << L"Running application: " << appPath << std::endl;
    int result = _wsystem(appPath.c_str());
    if (result != 0) {
        std::cerr << "Application failed with exit code " << result << std::endl;
        return false;
    }
    return true;
}
