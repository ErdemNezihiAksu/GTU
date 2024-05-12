#include "Shell.hpp"
#define DEBUG
#include <fstream>
#include <sstream>

void Shell::cp(const string &source, const string &dest)
{
    if (isDuplicate(dest, FileType::REGULAR)) //ayni isimde dosya var mi kontrol et
    {
        std::cout << "cp: " << dest << ": There is already a file with this name\n";
        return;
    }
    bool exist = false;
    std::ifstream inputFile;
    string content, temp;

    size_t found = source.find('/');
    inputFile.open(source);
    if (inputFile.is_open()) // Kendi OS unu kontrol et
    {
        while (std::getline(inputFile, temp))
        {
            content += temp;
            content += "\n";
        }
        content[content.length() - 1] = ' ';
        exist = true;
        inputFile.close();
    }
    else if (found != string::npos) // Sanal OS Pathini kontrol et
    {
        Directory *ptr;
        vector<string> path;
        std::istringstream stream(source);
        while (std::getline(stream, temp, '/'))
            path.push_back(temp);
        if (path.empty())
            exist = false;
        else if (path[0] == ".")
        {
            ptr = current_dir;
            exist = true;
        }
        else if (path[0] == "myShell")
        {
            ptr = root_dir;
            exist = true;
        }
        else
        {
            for (auto dir : *current_dir)
            {
                if (dir->getType() == FileType::DIRECTORY && dir->getName() == path[0])
                {
                    ptr = dynamic_cast<Directory *>(dir);
                    exist = true;
                    break;
                }
            }
        }
        if (exist)
        {
            int idx = 1;
            while (exist && idx < path.size())
            {
                exist = false;
                for (auto dir : *ptr)
                {
                    FileType type = dir->getType();
                    if (dir->getName() == path[idx])
                    {
                        if (idx < path.size() - 1 && type == FileType::DIRECTORY)
                        {
                            exist = true;
                            ptr = dynamic_cast<Directory *>(dir);
                            break;
                        }
                        else if (idx == path.size() - 1 && type == FileType::REGULAR)
                        {
                            exist = true;
                            Regular *temp = dynamic_cast<Regular *>(dir);
                            content = temp->getContent();
                            break;
                        }
                        else if (idx == path.size() - 1 && type == FileType::SOFT)
                        {
                            exist = true;
                            Soft *temp = dynamic_cast<Soft *>(dir);
                            content = temp->getContent();
                            break;
                        }
                    }
                }
                ++idx;
            }
        }
    }
    else // degilse bulunan sanal dizindeki dosyalari kontrol et
    {
        for (auto f : *current_dir)
        {
            if (f->getName() == source)
            {
                FileType type = f->getType();
                if (type == FileType::REGULAR)
                {
                    Regular *ptr = dynamic_cast<Regular *>(f);
                    content = ptr->getContent();
                    exist = true;
                    break;
                }
                else if (type == FileType::SOFT)
                {
                    Soft *ptr = dynamic_cast<Soft *>(f);
                    content = ptr->getContent();
                    exist = true;
                    break;
                }
            }
        }
    }
    if (exist)
    {
        if (total_size + content.size() <= 10 * 1024 * 1024) //eger dosya bulunduysa ve size 10MB i gecmiyorsa, dosyayi kopyala
        {
            Regular *temp = new Regular(dest, content);
            current_dir->push_back(temp);
            incrementSize(temp);
        }
        else
            std::cout << "Insufficient capacity!! \nTotal Capacity: 10MB\nUsed Capacity: " << total_size / (1024 * 1024) << "MB" << std::endl;
    }
    else
        std::cout << "Source file does not exist" << std::endl;
}

void Shell::ls(const string &flag, const vector<string> &dirNames)
{
    file *dir;
    vector<Directory *> directories;
    string name;
    for (const string &str : dirNames) //listelenicek klasorlerin adreslerini bir vectorde toplariz
    {
        dir = nullptr;
        if (str == ".")
            dir = current_dir;
        else if (str == "..")
            dir = current_dir->getParent();
        else
        {
            for (auto f : *current_dir)
            {
                if (f->getType() == FileType::DIRECTORY && f->getName() == str)
                {
                    dir = f;
                    break;
                }
            }
        }
        if (dir != nullptr)
            directories.push_back(dynamic_cast<Directory *>(dir));
        else
            std::cout << "ls: " << str << ':' << " No such directory" << std::endl;
    }
    if (flag == "")
    {
        for (auto f : directories) //listelincek klasortlerin bastiri
        {
            if (f->getName() == current_dir->getName())
                name = ".";
            else if (current_dir->getParent() != nullptr && f->getName() == current_dir->getParent()->getName())
                name = "..";
            else
                name = f->getName();
            if (directories.size() > 1)
                std::cout << name << ':' << std::endl;
            std::cout << "D .\t" << f->getTime() << std::endl;
            if (f->getParent() != nullptr)
                std::cout << "D ..\t" << f->getParent()->getTime() << std::endl;
            for (auto it : *f)
                std::cout << static_cast<char>(it->getType()) << ' ' << it->getName() << '\t' << it->getTime() << '\t' << it->getBytes() << "Bytes" << std::endl;
        }
    }
    else if (flag == "-R") //Listelenicek klasorleri recursive olarak bastirir.
    {
        vector<Directory *> stack;
        Directory *ptr;
        for (auto dir : directories)
        {
            stack.push_back(dir);
            while (!stack.empty()) // Depth-first search e benzeyen bir algrotitmayla recursive lik saglanir
            {
                ptr = stack[stack.size() - 1];
                if (ptr->getName() == current_dir->getName())
                    name = ".";
                else if (current_dir->getParent() != nullptr && ptr->getName() == current_dir->getParent()->getName())
                    name = "..";
                else
                    name = ptr->getName();
                stack.pop_back();
                std::cout << name + ":" << std::endl;
                std::cout << "D .\t" << ptr->getTime() << std::endl;
                if (ptr->getParent() != nullptr)
                    std::cout << "D ..\t" << ptr->getParent()->getTime() << std::endl;
                for (auto f : *ptr)
                {
                    if (f->getType() == FileType::DIRECTORY)
                        stack.push_back(dynamic_cast<Directory *>(f));
                    std::cout << static_cast<char>(f->getType()) << ' ' << f->getName() << '\t' << f->getTime() << '\t' << f->getBytes() << "Bytes" << std::endl;
                }
                std::cout << std::endl;
            }
        }
    }
    else
        std::cout << "ls:" << flag << ": invalid flag" << std::endl;
}

void Shell::mkdir(const vector<string> &dirNames)
{
    bool exist;
    for (const string &str : dirNames)
    {
        if (isDuplicate(str, FileType::DIRECTORY))
            std::cout << "mkdir: " << str << ": There is already a diretory with this name\n";
        else
            current_dir->push_back(new Directory(str, current_dir));
    }
}

void Shell::rmdir(const vector<string> &dirNames)
{
    bool exist;
    for (const string &str : dirNames)
    {
        if (str == ".")
            std::cout << "rmdir: . can not be removed" << std::endl;
        else if (str == "..")
            std::cout << "rmdir: .. can not be removed" << std::endl;
        else
        {
            exist = false;
            for (auto it = current_dir->begin(); it != current_dir->end(); ++it)
            {
                if ((*it)->getType() == FileType::DIRECTORY && (*it)->getName() == str)
                {
                    decrementSize(*it);
                    current_dir->erase(it);
                    exist = true;
                    break;
                }
            }
            if (!exist)
                std::cout << "rmdir: " << str << ": directory does not exist" << std::endl;
        }
    }
}

void Shell::cd(const string &dirName)
{
    bool exist = false;

    if (dirName == ".")
        ;
    else if (dirName == "..")
    {
        if (current_dir->getParent() != nullptr)
            current_dir = current_dir->getParent();
    }
    else
    {
        for (auto dir : *current_dir)
        {
            if (dir->getType() == FileType::DIRECTORY && dir->getName() == dirName)
            {
                current_dir = dynamic_cast<Directory *>(dir);
                exist = true;
                break;
            }
        }
        if (!exist)
            std::cout << "cd:" << dirName << ": No such directory" << std::endl;
    }
}

void Shell::rm(const vector<string> &name)
{
    bool exist;
    for (const string &str : name)
    {
        exist = false;
        for (auto f = current_dir->begin(); f != current_dir->end(); ++f)
        {
            if ((*f)->getType() != FileType::DIRECTORY && str == (*f)->getName())
            {
                decrementSize(*f);
                current_dir->erase(f);
                exist = true;
                break;
            }
        }
        if (!exist)
            std::cout << "rm: " << str << ": file does not exist" << std::endl;
    }
}

void Shell::link(const string &source, const string &dest)
{
    if (isDuplicate(dest, FileType::SOFT))
    {
        std::cout << "link: " << dest << ": There is already a file with that name\n";
        return;
    }
    bool exist = false;
    for (auto file : *current_dir)
    {
        if (file->getType() == FileType::REGULAR && file->getName() == source)
        {
            Regular *temp = dynamic_cast<Regular *>(file);
            if (temp->getLinkTrace() != nullptr)
            {
                std::cout << "link: " << temp->getName() << ": There is already an existed linked file for this file\n";
                return;
            }
            current_dir->push_back(new Soft(dest, dynamic_cast<Regular *>(file)));
            exist = true;
            break;
        }
    }
    if (!exist)
        std::cout << "link: " << source << ": file doesn't exist" << std::endl;
}

void Shell::save() const
{
    std::ofstream outFile(FILENAME, std::ios::binary);
    if (!outFile.is_open())
    {
        std::cerr << "Error opening file for saving.\n";
        return;
    }

    vector<Directory *> stack;
    Directory *written;
    FileType type;
    string str;
    size_t size;
    int dir_size;

    outFile.write(root_dir->getTime(), 20 * sizeof(char)); // root directory time
    stack.push_back(root_dir);
    while (!stack.empty())
    {
        written = stack[stack.size() - 1];
        stack.pop_back();
        dir_size = written->fileCount();
        outFile.write(reinterpret_cast<const char *>(&dir_size), sizeof(int)); // directory file count
        for (auto file : *written)
        {
            type = file->getType();
            str = file->getName();
            size = str.size();
            outFile.write(reinterpret_cast<const char *>(&type), sizeof(FileType)); // type
            outFile.write(reinterpret_cast<const char *>(&size), sizeof(size_t));   // name size
            outFile.write(str.c_str(), size);              // file veya dir name
            outFile.write(file->getTime(), 20 * sizeof(char));                      // time
            if (type == FileType::REGULAR)
            {
                Regular *temp = dynamic_cast<Regular *>(file);
                str = temp->getContent();
                size = str.size();
                outFile.write(reinterpret_cast<const char *>(&size), sizeof(size_t)); // size of content
                outFile.write(str.c_str(), size);            // content
            }
            else if (type == FileType::SOFT)
            {
                Soft *temp = dynamic_cast<Soft *>(file);
                if (temp->getLink() != nullptr)
                {
                    str = temp->getLink()->getName();
                }
                else
                {
                    str = "nullptr";
                }
                size = str.size();
                outFile.write(reinterpret_cast<const char *>(&size), sizeof(size_t)); // name size
                outFile.write(str.c_str(), size);            // link name
            }
            else
                stack.push_back(dynamic_cast<Directory *>(file));
        }
    }
    outFile.close();
}

void Shell::load()
{
    std::ifstream inFile(FILENAME, std::ios::binary | std::ios::ate); //file pointer sonda olacak sekilde dosyayi ac.
    if (!inFile.is_open())
    {
        std::cerr << "Error opening file!\n";
        return;
    }
    if (inFile.tellg() == 0) // dosya bos mu diye kontrol.
        return;

    delete root_dir;
    root_dir = nullptr;
    inFile.seekg(0, std::ios::beg); // file pointer a basa dondur.

    vector<Directory *> stack;
    string name, content, str;
    char time[20];
    FileType type;
    int dir_size;
    size_t size;

    inFile.read(time, 20 * sizeof(char)); // read root_dir time
    root_dir = new Directory("myShell", time);
    stack.push_back(root_dir);
    while (!stack.empty())
    {
        current_dir = stack[stack.size() - 1];
        stack.pop_back();
        inFile.read(reinterpret_cast<char *>(&dir_size), sizeof(int)); // read dir file count
        for (int i = 0; i < dir_size; ++i)
        {
            inFile.read(reinterpret_cast<char *>(&type), sizeof(FileType)); // read type
            inFile.read(reinterpret_cast<char *>(&size), sizeof(size_t));   // read size of name
            name.resize(size);
            inFile.read(&name[0], size); // read name
            inFile.read(time, 20 * sizeof(char));               // read time
            if (type == FileType::DIRECTORY)
            {
                Directory *temp = new Directory(name, time, current_dir);
                current_dir->push_back(temp);
                stack.push_back(temp);
            }
            else if (type == FileType::REGULAR)
            {
                inFile.read(reinterpret_cast<char *>(&size), sizeof(size_t)); // read content size
                content.resize(size);
                inFile.read(&content[0], size); // read content
                Regular *temp = new Regular(name, time, content);
                current_dir->push_back(temp);
            }
            else
            {
                inFile.read(reinterpret_cast<char *>(&size), sizeof(size_t)); // name size;
                str.resize(size);
                inFile.read(&str[0], size); // link name
                if (str != "nullptr")
                {
                    for (auto file : *current_dir)
                    {
                        if (file->getType() == FileType::REGULAR && file->getName() == str)
                        {
                            current_dir->push_back(new Soft(name, dynamic_cast<Regular *>(file), time));
                            break;
                        }
                    }
                }
                else
                    current_dir->push_back(new Soft(name, nullptr, time));
            }
        }
    }
    inFile.close();
    current_dir = root_dir;
}

bool Shell::isDuplicate(const string &name, FileType type) const
{
    for (auto file : *current_dir)
    {
        if (file->getName() == name && file->getType() == type)
            return true;
    }
    return false;
}