/*
    PicobookX, by Etienne Bégué - www.txori.com
    Launch Picotron by Lexaloffle at the correct screen resolution on the
    Chuwi Minibook X, then switch back to the original resolution upon exit

    Compile using w64devkit (https://github.com/skeeto/w64devkit):
    g++ -O3 -std=c++17 -o picobookx.exe picobookx.cpp -lstdc++fs
*/

#include <iostream>
#include <windows.h>
#include <winuser.h>

// Screen resolution of the Chuwi Minibook X
constexpr int SCREEN_WIDTH = 1440;
constexpr int SCREEN_HEIGHT = 900;

// Screen resolution of the Picotron 480x270 (x3)
constexpr int PICOTRON_WIDTH = 1440;
constexpr int PICOTRON_HEIGHT = 810;

// Function prototypes
bool ChangeResolution(int width, int height);
void RestoreResolution();

int main() {
    // Change the screen resolution
    if (!ChangeResolution(SCREEN_WIDTH, SCREEN_HEIGHT)) {
        std::cerr << "Failed to change screen resolution." << std::endl;
        return 1; // Exit if resolution change failed
    }

    // Run the program
    if (system("picotron.exe") != 0) {
        std::cerr << "Failed to execute picotron.exe." << std::endl;
        RestoreResolution(); // Restore resolution before exiting
        return 1;
    }

    // Restore the original screen resolution
    RestoreResolution();

    return 0;
}

// Function to change the screen resolution
bool ChangeResolution(int width, int height) {
    DEVMODE devMode = {};
    devMode.dmSize = sizeof(DEVMODE);
    devMode.dmPelsWidth = width;
    devMode.dmPelsHeight = height;
    devMode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;

    return ChangeDisplaySettings(&devMode, CDS_FULLSCREEN) == DISP_CHANGE_SUCCESSFUL;
}

// Function to restore the original screen resolution
void RestoreResolution() {
    ChangeDisplaySettings(NULL, 0);
}
