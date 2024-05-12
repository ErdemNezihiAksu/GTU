#include "directory.hpp"

Directory::~Directory()
{
    for(auto f : *this)
    {
        delete f;
    }
}

void Directory::cat() const
{
    std::cout << "Showing directory " << ' ' << this->getName() << '\t' << this->getTime() << " :" << std::endl;
    for(auto f : files)
    {
        if(f != nullptr && f->getType() != FileType::DIRECTORY)
            f->cat();
    }
}

void Directory::push_back(file* f)
{
    files.push_back(f);
    Directory* ptr = dynamic_cast<Directory*>(f);
    if(ptr == nullptr)
        bytes += f->getBytes();
}

void Directory::erase(Iterator<file*> f)
{
    delete *f;
    size_t pos = &(*f) - &files[0];
    files.erase(files.begin() + pos);
}
