# Zombie
## Development
### Memory Saftey
Make sure all changes are memory safe before pushing. Use the command `valgrind --log-file="output" --leak-check=full ./zombie` and look inside the created `output` file, make sure there are not memory leaks.  
### Visitor Pattern
All objects that interact with the map must be forward declared in visitor, such as zombie in `visitor.h`
```cpp
class Zombie;
```