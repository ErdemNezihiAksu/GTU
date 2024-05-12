#ifndef FILE_HPP
#define FILE_HPP
#include <string>
#include <cstring>
#include <ctime>
#include <iostream>
using std::string;

enum class FileType : char
{
    REGULAR = 'F',
    DIRECTORY = 'D',
    SOFT = 'S'
};

class file
{
public:
    file(const string& name_) : name(name_)
    {
        time_t t = std::time(nullptr);
        auto ti = std::localtime(&t);
        std::strftime(creation_time, 20, "%b %d %H:%M", ti);
        creation_time[sizeof(creation_time) - 1] = '\0';
    }
    file(const string& name_, const char* time) : name(name_) {strcpy(creation_time,time);} // OS.bin den okurken kullanmak icin olan constructer.
    virtual ~file() = default;

    template <typename T>
    class Iterator
    {
    public:
        Iterator(T *p) : ptr(p) {}
        Iterator(): ptr(nullptr) {}
        Iterator &operator++()
        {
            ++ptr;
            return *this;
        }

        Iterator operator++(int)
        {
            Iterator temp = *this;
            ++ptr;
            return temp;
        }

        Iterator& operator+(int a)
        {
            ptr += 2;
            return *this;
        }

        T& operator*() const
        {
            return *ptr;
        }

        T* operator->() const
        {
            return ptr;
        }
        bool operator==(const Iterator &obj) const
        {
            return ptr == obj.ptr;
        }

        bool operator!=(const Iterator &obj) const
        {
            return ptr != obj.ptr;
        }

        Iterator& operator=(const T *obj)
        {
            ptr = obj;
            return *this;
        }

    private:
        T *ptr;
    };
    virtual void cat() const = 0;
    virtual size_t getBytes() const = 0;
    string getName() const {return name;}
    const char* getTime() const {return creation_time;}
    FileType getType() const {return type;}

protected:
    string name;
    char creation_time[20];
    FileType type;
};
#endif