#include <filesystem>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

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
      std::cout << "📁 " << std::left << std::setw(20) << folder.name
                << std::right << std::setw(10) << "\n";
    }

    for (const auto &folder : folder_empty_names) {
      std::cout << "📂 " << std::left << std::setw(20) << folder.name
                << std::right << std::setw(10) << "\n";
    }
  }

  void display_file() {
    for (const auto &file : file_names) {
      std::cout << "📄 " << std::left << std::setw(20) << file.name
                << std::setw(10);
      std::cout << std::right;

      if (file.size > 1099511627776ULL)
        std::cout << std::setw(10) << (file.size / 1024 / 1024 / 1024 / 1024)
                  << " TB\n";
      else if (file.size > 1073741824ULL)
        std::cout << std::setw(10) << (file.size / 1024 / 1024 / 1024)
                  << " GB\n";
      else if (file.size > 1048576ULL)
        std::cout << std::setw(10) << (file.size / 1024 / 1024) << " MB\n";
      else if (file.size > 1024ULL)
        std::cout << std::setw(10) << (file.size / 1024) << " KB\n";
      else
        std::cout << std::setw(10) << file.size << " BT\n";
    }
  }
};

int main() { Manager manager; }
