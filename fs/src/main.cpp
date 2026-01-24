#include "../include/FileManager.h"
#include "../include/DisplayManager.h"

int main() {
    FileManager file_manager;
    DisplayManager display(file_manager);

    display.show_folders();
    display.show_files();
}
