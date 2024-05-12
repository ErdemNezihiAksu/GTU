#include "files.hpp"

Regular::~Regular()
{
    if (link_trace != nullptr) // Eger kendisini gosteren bir linked file varsa, silinirken link file a nullptr gostertir.
        link_trace->NullLink();
}

Soft::~Soft()
{
    if (link != nullptr) // Gosterdigi dosyanin linktrace i ne nullptr gostertir.
        link->setLinkTrace(nullptr);
}

Soft::Soft(const string& name_, Regular* file_, const char* time): file(name_,time),link(file_)
{
    type = FileType::SOFT; 
    if(file_ != nullptr) 
        file_->setLinkTrace(this);
}

void Soft::cat() const
{
    if (link != nullptr)
        link->cat();
    else
        std::cout << "cat: " << this->getName() << ": is not valid" << std::endl;
}