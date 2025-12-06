#include <filesystem>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <map>

namespace fs = std::filesystem;

struct FolderInfo {
    std::string name;
};

struct FileInfo {
    std::string name;
    std::uintmax_t size;
};

class Manager {
protected:
    std::vector<FolderInfo> folder_names;
    std::vector<FolderInfo> folder_empty_names;
    std::vector<FileInfo> file_names;

    std::map<std::string, std::string> extension_emoji = {
        {"mp4", "🎬"}, {"mov", "🎬"}, {"mkv", "🎬"},
        {"mp3", "🎵"}, {"wav", "🎵"}, {"flac", "🎵"},
        {"jpg", "🖼️"}, {"jpeg", "🖼️"}, {"png", "🖼️"},
        {"gif", "🖼️"}, {"svg", "🖼️"},
        {"txt", "📄"}, {"md", "📝"}, {"json", "🗃️"},
        {"xml", "📄"}, {"yaml", "📜"}, {"yml", "📜"}, {"csv", "📊"},
        {"zip", "🗜️"}, {"rar", "🗜️"}, {"7z", "🗜️"},
        {"html", "🌐"}, {"css", "🎨"}, {"js", "📜"}, {"ts", "🔵"},
        {"cpp", "💻"}, {"c", "💻"}, {"py", "🐍"}, {"java", "☕"},
        {"rb", "💎"}, {"php", "🐘"}, {"go", "🐹"}, {"rs", "🦀"},
        {"kt", "💙"}, {"swift", "🍎"}, {"sh", "🐚"}
    };

public:
    Manager() {
        fs::path path = fs::current_path();

        if (fs::exists(path) && !fs::is_empty(path)) {
            for (const auto &element : fs::directory_iterator(path)) {
                if (fs::exists(element) && !fs::is_regular_file(element)) {
                    if (!fs::is_empty(element))
                        folder_names.push_back({element.path().filename().string()});
                    else
                        folder_empty_names.push_back({element.path().filename().string()});
                } else if (fs::exists(element)) {
                    file_names.push_back(
                        {element.path().filename().string(),
                         static_cast<std::uintmax_t>(fs::file_size(element))});
                }
            }

            display_folder();
            display_file();
        } else {
            std::cout << "Текущая директория пуста или не существует.\n";
        }
    }

private:
    void display_folder() {
        for (const auto &folder : folder_names) {
            std::cout << "📁 " << std::left << std::setw(20) << folder.name << "\n";
        }

        for (const auto &folder : folder_empty_names) {
            std::cout << "📂 " << std::left << std::setw(20) << folder.name << "\n";
        }
    }

    void display_file() {
        for (const auto &file : file_names) {
            std::string ext = fs::path(file.name).extension().string();
            if (!ext.empty() && ext[0] == '.') ext.erase(0, 1);

            std::string emoji = "📄";
            if (extension_emoji.count(ext)) {
                emoji = extension_emoji[ext];
            }

            std::cout << emoji << " " << std::left << std::setw(20) << file.name;

            if (file.size > 1099511627776ULL)
                std::cout << std::setw(10) << (file.size / 1024 / 1024 / 1024 / 1024) << " TB\n";
            else if (file.size > 1073741824ULL)
                std::cout << std::setw(10) << (file.size / 1024 / 1024 / 1024) << " GB\n";
            else if (file.size > 1048576ULL)
                std::cout << std::setw(10) << (file.size / 1024 / 1024) << " MB\n";
            else if (file.size > 1024ULL)
                std::cout << std::setw(10) << (file.size / 1024) << " KB\n";
            else
                std::cout << std::setw(10) << file.size << " BT\n";
        }
    }
};

int main() {
    Manager manager;
}


