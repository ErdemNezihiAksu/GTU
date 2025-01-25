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
- exit (exits the program)
- cat
- cp
  You can either copy your actual files in your computer or copy the abstract files.
  
  NOTE:
  - If you don't have a saved shell, you have to copy an actual file from your computer to begin since there is no touch command.
  - Directories can not be coppied.

### Explanation

  All 3 files types are a class inherited from file abstract class (FILE.HPP). 
  File class has an template iterator class implemented. For directories, it allows you to traverse the files and directories inside. For files, it allows you to read the context by traversing char by char. Linked files are only a pointer to the real file, every command works the same on them as the real files. 

  The Directories and the files you have created during the program run are saved to OS.bin, so when you run the program again you can pick up from where you have left.

### How to Run

  Jut enter "make" command. It will load the saved files and directories (if any) to the system.

### Example Usage

  - At first, we dont have an empty shell.
    
  ![Screenshot 2025-01-25 at 10 46 31](https://github.com/user-attachments/assets/0ee25c6b-327d-4968-8d6e-98e3f7200ff7)

  - Let's create a directory.

  ![Screenshot 2025-01-25 at 10 47 08](https://github.com/user-attachments/assets/067ab9c7-fc9f-42d9-a549-91fba10bee46)

  - Let's copy an actualy file from our local machine. Since there is no touch command, this is the only way to add the inital file to the system.

  ![Screenshot 2025-01-25 at 10 47 45](https://github.com/user-attachments/assets/1d0b6573-b125-4e43-aae6-67145a21b375)

  - Then we can copy this file again to the directory we have just created using the abstract path of the file.

  ![Screenshot 2025-01-25 at 10 49 57](https://github.com/user-attachments/assets/0986c1a8-be98-4071-bf07-648277585eb0)

  - Finally we can see all the files and directories we have created with ls command with -R flag.

  ![Screenshot 2025-01-25 at 10 51 03](https://github.com/user-attachments/assets/5c2286e3-6787-4482-b8ab-a27e2650b90e)

  
