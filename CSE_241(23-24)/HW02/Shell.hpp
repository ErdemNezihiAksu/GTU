#ifndef SHELL_HPP
#define SHELL_HPP
#include "directory.hpp"
#include "files.hpp"
#define FILENAME "OS.bin"

class Shell
{
public:
    Shell(Directory* dir): current_dir(dir) , root_dir(dir), total_size(0) {}
    ~Shell() {delete root_dir;}
    Directory* getDir() const {return current_dir;}
    void cp(const string& source, const string& dest);
    void ls(const string& flag, const vector<string>& dirNames = {"."});
    void mkdir(const vector<string>& dirNames);
    void rmdir(const vector<string>& dirNames);
    void cd(const string& dirName);
    void rm(const vector<string>& name);
    void link(const string& source, const string& dest);
    void save() const ;
    void load();
    bool isDuplicate(const string& name, FileType type) const; //Bulunan dizinde ayni turden ve isimden bir file var mi diye kontrol eder
private:
    Directory* root_dir;
    Directory *current_dir; // Suan da icinde olunan directory
    size_t total_size;
    void incrementSize (file *f) {total_size += f->getBytes();} //Byte ekle
    void decrementSize (file *f) {total_size -= f->getBytes();} //Byte cikar
    
};
#endif