# Zombie
## Development
### Memory Saftey
Make sure all changes are memory safe before pushing. Use the command `valgrind --log-file="output" --leak-check=full ./zombie` and look inside the created `output` file, make sure there are not memory leaks.  
### Visitor Pattern
All objects that interact with the map must be forward declared in visitor, such as zombie in `visitor.h`
```cpp
class Zombie;
```

## Blog  
`6/5/2022`  
At first I had decided to use the visitor pattern, but there are a few issues with this. I wanted to do it to solve a circular dependency issue. I got it to work, but it is somewhat confusing. The bigger issue however, is that it leads to a God class, which has an immense amount of logic in it. I would rather the logic be put into each of the visitors, and take advantage of dynamic dispatch of pointers.  
Besides, we do not need the bigger purpose of the visitor pattern. It is meant for double dispatching, however we are always moving things relative to the map. So I just used visitor as a workaround to a circular dependency issue, which I could just forward declare in the interface (hopefully, or else I will continue to use the visitor pattern, just more sad).  
  
Very smart people exist. [Here](https://stackoverflow.com/questions/40266958/how-to-enforce-private-constructors-in-children-of-a-base-class) is something you could do to force all the constructors of your sprite implementations to have private constructors so they are all self deleting. You would then need a factory to create sprites, but that is fine.