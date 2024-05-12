#include "Shell.hpp"
using std::cin;
using std::cout;
using std::endl;

vector<string> splitString(const string &str)
{
    vector<string> words;
    string token = "";
    for (char c : str)
    {
        if (c != ' ' && c != '\t' && c != '\n' && c != '\r' && c != '\v' && c != '\f')
            token += c;
        else
        {
            if (token != "")
            {
                words.push_back(token);
                token = "";
            }
        }
    }
    words.push_back(token);
    return words;
}

int main()
{
    string input, command, flag;
    vector<string> words, fileNames;
    int index;
    Shell shell(new Directory("myShell"));
    shell.load();
    do
    {
        cout << endl << shell.getDir()->getName() << endl << "> ";
        std::getline(cin, input);
        words = splitString(input); // her bir kelimeyi vektore al
        command = words[0]; // ilk kelime komut olur
        if (command != "") // eger bos bir string girildiyse komut "" olur
        {
            if (words.size() > 1) // eger 1 den fazla kelime varsa komutun yanindaki parameterelere bak
            {
                flag = words[1];
                if (flag[0] != '-')
                {
                    flag = "";
                    index = 1;
                }
                else
                    index = 2;
                for (; index < words.size(); ++index) // flag i kesinlestirdikten sonra parametre isimlerini bir vektore al
                    fileNames.push_back(words[index]);
            }
            if (command == "cp")
            {
                if (flag != "")
                    cout << "cp: doesnt accept any flags" << endl;
                else if (fileNames.size() != 2)
                    cout << "cp: takes 2 parameters source file and destination file" << endl;
                else
                    shell.cp(fileNames[0], fileNames[1]);
            }
            else if (command == "cat")
            {
                if (flag != "")
                    cout << "cat: doesn't accept any flags" << endl;
                else if (fileNames.empty())
                    cout << "cat: needs arguments(file or directory)" << endl;
                else
                {
                    bool exist;
                    for (const string &str : fileNames)
                    {
                        exist = false;
                        if(str == "."){
                            shell.getDir()->cat();
                            exist = true;
                        }
                        else if(str == ".."){
                            if(shell.getDir()->getParent() != nullptr)
                                shell.getDir()->getParent()->cat();
                            exist = true;
                        }
                        else
                       {
                            for (auto f : *(shell.getDir()))
                            {
                                if(f->getName() == str)
                                {
                                    f->cat();
                                    exist = true;
                                }
                            }
                        }
                        if(!exist)
                            cout << "cat: " << str << " : " << "No such file or directory" << endl;
                    }
                }
            }
            else if (command == "ls")
            {
                if(fileNames.empty())
                    shell.ls(flag);
                else
                    shell.ls(flag,fileNames);
            }
            else if (command == "mkdir")
            {
                if(flag != "")
                    cout << "mkdir: doesn't accept any flags" << endl;
                else if (fileNames.empty())
                    cout << "mkdir: needs arguments (directory name(s))" << endl;
                else
                    shell.mkdir(fileNames);
            }
            else if (command == "rmdir")
            {
                if(flag != "")
                    cout << "rmdir: doesn't accept any flags" << endl;
                else if(fileNames.empty())
                    cout << "rmdir: needs arguments (directory name(s))" << endl;
                else
                    shell.rmdir(fileNames);
            }
            else if (command == "cd")
            {
                if(flag != "")
                    cout << "cd: doesn't accept any flags" << endl;
                else if(fileNames.size() != 1)
                    cout << "cd: only accepts 1 argument" << endl;
                else
                    shell.cd(fileNames[0]);
            }
            else if(command == "rm")
            {
                if(flag != "")
                    cout << "rm: doesn't accept any flags" << endl;
                else if (fileNames.empty())
                    cout << "rm: needs arguments" << endl;
                else
                    shell.rm(fileNames);
            }
            else if (command == "link")
            {
                if(flag != "")
                    cout << "link: doesn't accept any flags" << endl;
                else if (fileNames.size() != 2)
                    cout << "link: needs 2 arguments (source file and dest file)" << endl;
                else
                    shell.link(fileNames[0],fileNames[1]);
            }
            else if(command != "exit")
                cout << "Invalid command!!" << endl;
        }
        words.clear();
        fileNames.clear();
        flag = "";
    } while (command != "exit");
    shell.save();
}