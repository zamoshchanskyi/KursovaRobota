#include <iostream>
#include <filesystem>
#include <map>
#include <Windows.h>

std::vector<std::string> nameFolder;
std::map<std::string, intmax_t> sizeFolder;

std::uintmax_t directorySize(const std::filesystem::path& directory)
{
    std::uintmax_t size{ 0 };
    for (const auto& entry : std::filesystem::recursive_directory_iterator(directory))
    {
        if (entry.is_regular_file() && !entry.is_symlink())
        {
            size += entry.file_size();
        }
    }
    return size;
}

void ls_recursive(const std::filesystem::path& path)
{
    int_fast64_t count = 0;
    for(const auto& p: std::filesystem::recursive_directory_iterator(path,std::filesystem::directory_options::skip_permission_denied))
    {
        if (std::filesystem::is_directory(p)) 
        {
            uintmax_t temp = 0;
            temp = directorySize(p.path());
            sizeFolder[p.path().filename().string()] = temp;
        }
    }
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::string path;
    std::cout << "Вкажіть шлях до диску або каталогу: " << std::endl;
    std::getline(std::cin,path);

    while (!std::filesystem::exists(path))
    {
        std::cout << "Шлях не вказано АБО вказано не правильно!" << std::endl;
        std::cout << "Вкажіть шлях до диску або каталогу: " << std::endl;
        std::getline(std::cin, path);
    }

    ls_recursive(path);
    std::cout<<std::endl;

    intmax_t maxSizeFolder = 0;
    std::string maxNameFolder ;
    std::cout << "Список каталогів: " << std::endl;

    for(auto it: sizeFolder)
    {
        std::cout << "Ім'я каталогу: " << it.first << "\tРозмір каталогу :" << it.second << std::endl;
    }

    std::cout << "\n-------------------------------------------------------------------" << std::endl;

    for(auto it: sizeFolder)
    {
        if(it.second > maxSizeFolder)
        {
            maxSizeFolder = it.second;
            maxNameFolder = it.first;
        }
    }

    std::cout << "Максимальний розмір має каталог: "<< std::endl;
    std::cout << "Ім'я каталогу: " << maxNameFolder << "\tРозмір : " << maxSizeFolder << std::endl;

    return 0;
}