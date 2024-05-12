#ifndef REGULAR_HPP
#define REGULAR_HPP
#include "FILE.hpp"

class Soft;

class Regular: public file
{
    public:
        Regular(const string& name_, const string& content_ = ""): file(name_), content(content_) {type = FileType::REGULAR;}
        Regular(const string& name_, const char* time, const string& content_ = ""): file(name_,time), content(content_) {type = FileType::REGULAR;}
            // OS.bin den okumak icin kullanilan constructer
        Iterator<char> begin() {return Iterator<char>(&content[0]);}
        Iterator<char> end() {return Iterator<char>(&content[content.size()]);}
        string getContent() const {return content;}
        void cat() const override {std::cout << static_cast<char>(this->getType()) << ' ' << this->getName() << '\t' << this->getTime() << "\n" << content << std::endl << std::endl;}
        size_t getBytes() const override {return content.size();}
        void setLinkTrace(Soft *obj) {link_trace = obj;} //Yalnizca softlink constructer inda kullanilacak
        Soft* getLinkTrace() const {return link_trace;}
        ~Regular() override;
    private:
        string content;
        Soft* link_trace = nullptr; // Eger kendisini gosteren bir soft linked file varsa, onu gosterir.
};


class Soft: public file
{
    public:
        Soft(const string& name_, Regular* file_): file(name_), link(file_) {type = FileType::SOFT; file_->setLinkTrace(this);}
        Soft(const string& name_, Regular* file_, const char* time); // OS.bin den okumak icin
        Iterator<char> begin() {return (link!= nullptr) ? Iterator<char>(&link->getContent()[0]) : Iterator<char>(nullptr);}
        Iterator<char> end() {return (link!= nullptr) ? Iterator<char>(&link->getContent()[link->getContent().size()]) : Iterator<char>(nullptr);}
        string getContent() const {return (link!= nullptr) ? link->getContent() : "";}
        void cat() const override;
        size_t getBytes() const override {return 0;}
        void NullLink() {link = nullptr;} // Gosterdigi regula file silinirse nullptr gosterir
        const Regular* getLink() const {return link;}
        ~Soft() override;
    private:
        Regular* link;
};
#endif