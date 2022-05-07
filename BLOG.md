## Blog
`6/6/2022`  
Spent a stupid ammount of time making the bullets destroy the zombies. I kept getting seg faults, I am still not exactly sure how it was happening. I think it had something to do with one of the following:
- The linked list. I think somehow this was getting messed up. The change I made that ended up making everything work in the end was was making move::action return the next move, thus avoding some nonsence.
- It may have to do with virtual constructors/destructors. I am not so sure on this, but it is a thought.

It would be very useful for me to get super good at using GDB. That may have allowed me to actually find the problem and fix it, rather than just getting lucky with a workaround.

`6/5/2022`  
At first I had decided to use the visitor pattern, but there are a few issues with this. I wanted to do it to solve a circular dependency issue. I got it to work, but it is somewhat confusing. The bigger issue however, is that it leads to a God class, which has an immense amount of logic in it. I would rather the logic be put into each of the visitors, and take advantage of dynamic dispatch of pointers.  
Besides, we do not need the bigger purpose of the visitor pattern. It is meant for double dispatching, however we are always moving things relative to the map. So I just used visitor as a workaround to a circular dependency issue, which I could just forward declare in the interface (hopefully, or else I will continue to use the visitor pattern, just more sad).  
  
Very smart people exist. [Here](https://stackoverflow.com/questions/40266958/how-to-enforce-private-constructors-in-children-of-a-base-class) is something you could do to force all the constructors of your sprite implementations to have private constructors so they are all self deleting. You would then need a factory to create sprites, but that is fine.