#ifndef DIRECTORY_HPP
#define DIRECTORY_HPP
#include "FILE.hpp"
#include <vector>
using std::vector;

class Directory: public file
{
    public:
        Directory(const string& name_, Directory* parent=nullptr): file(name_), bytes(0), parentDir(parent) {type = FileType::DIRECTORY;}
        Directory(const string& name_, const char* time, Directory* parent=nullptr): file(name_,time), bytes(0), parentDir(parent) {type = FileType::DIRECTORY;}
            // OS.bin den okumak icin kullanilan constructer.
        ~Directory() override;
        Iterator<file*> begin() {return Iterator<file*>(&files[0]);}
        Iterator<file*> end() {return Iterator<file*>(&files[files.size()]);}
        Directory* getParent() const {return parentDir;}
        void push_back(file* f); //klasore file ekle
        void erase(Iterator<file*> f); // klasorden file sil
        void cat() const override; // klasorun icindeki dosyalarin icerigini bastir
        int fileCount() const {return files.size();} // klasorun kac tane file barindirdigini dondur
        size_t getBytes() const override {return bytes;} // klasorun toplam byte ini dondur

    private:
        vector<file*> files;
        Directory* parentDir;
        size_t bytes;
};

#endif