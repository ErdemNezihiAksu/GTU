# File Types

- Directory
- File
- Linked File

## Commands

- ls (-R)
  -R: prints the directories recursivly.
- mkdir
- rmdir
- cd
- rm
- save (saves current shell to OS.bin file)
- load (loads the saved shell)
- cat
- cp
  You can either copy your actual files in your computer or copy the abstract files.
  
  NOTE:
  - If you don't have a saved shell, you have to copy an actual file from your computer to begin since there is no touch command.
  - Directories can not be coppied.

### Explanation

    All 3 files types are a class inherited from file abstract class (FILE.HPP).

    file class has an template iterator class implemented. For directories, it allows you to traverse the files and directories inside. For files, it allows you to read the context by traversing char by char.

    Linked files are only a pointer to the real file, every command works the same on them as the real files.
