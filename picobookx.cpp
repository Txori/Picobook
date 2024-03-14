/*
    PicobookX, by Etienne Bégué - www.txori.com
    Launch Picotron by Lexaloffle at the correct screen resolution on the
    Chuwi Minibook X, then switch back to the original resolution upon exit

    Compile using w64devkit (https://github.com/skeeto/w64devkit):
    g++ -O3 -std=c++17 -o picobookx.exe picobookx.cpp -lstdc++fs
*/

#include <iostream>
#include <windows.h>

// Function to change the screen resolution
bool ChangeResolution(int width, int height) {
    DEVMODE devMode;
    devMode.dmSize = sizeof(DEVMODE);
    devMode.dmPelsWidth = width;
    devMode.dmPelsHeight = height;
    devMode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;

    if (ChangeDisplaySettings(&devMode, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL) {
        std::cerr << "Failed to change screen resolution." << std::endl;
        return false;
    }

    return true;
}

// Function to restore the original screen resolution
void RestoreResolution() {
    ChangeDisplaySettings(NULL, 0);
}

int main() {
    // Change the screen resolution to 1440x900
    // Picotron resolution is 480x270, x3 = 1440x810
    if (!ChangeResolution(1440, 900)) {
        return 1; // Exit if resolution change failed
    }

    // Run the program
    system("picotron.exe");

    // Restore the original screen resolution
    RestoreResolution();

    return 0;
}
