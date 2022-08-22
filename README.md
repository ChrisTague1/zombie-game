# Zombie
## Development
### Memory Saftey
Make sure all changes are memory safe before pushing. Use the command `valgrind --log-file=".valgrind.txt" --leak-check=full ./zombie` and look inside the created `.valgrind.txt` file, make sure there are not memory leaks.  
### Debugging with curses
To use GDB, you will need two terminals.
- In terminal one, run the program normal with ./PROGRAM
- In the second, we need to programs process identifier (PID). Use `ps -few | grep PROGRAM` to get it, it will be in the second column, or Google the command if you are unsure.

**Note:** `grep` will catch multiple things, including itself. The program is uausally the top one. 

Once you have the **PID**, run `gdb PROGRAM PID`, where program is the program name (zombie), and PID is the PID you just discovered.

**Note:** you have have to use `sudo gdb PROGRAM PID`.

Use `c` to continue the execution of the program. Google GDB for how to use GDB.

## Bugs
- It is pretty common for zombies to be invisible due to how they are rendered. To avoid printing the board on every frame, you could print the cell you are going to and the cell you are leaving. Another option would be to bar you from entering the same cell as something else.