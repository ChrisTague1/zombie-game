## Blog
`6/9/2022`  
The printing of the board needs to be handled better. Currently, the board doesn't refresh, which has been causing some issues. I should prevent the spawner from putting zombies with a radius of the player. Zombies should also not be able to stack on top of eachother.

`6/8/2022`  
Got zombies to follow the player using dikstras algorithm. I wasn't super careful porting it over from an old project I had which caused some problems. Previously, I gave each cell a 'to' addribute, which told it where the most efficient place to go to next was. This would help with preformance, so I may add it back, but for now I am keeping it gone. I also want to use A* instead, with a pretty heavy emphasis on getting closer to the player each time rather than taking the most efficient route. This will make them feel more like zombies.

Previously I had used the visitor pattern for actions against the map, but ditched that idea. I think I will need to use it again for the terrain, however. I would like the player and zombies (and in the future different types of zombies) to have different movement costs on the terrain.

Here are some more things I need to do:
- Make the terrain more interesting. It is really boring right now.
- Add damage and health. Right now the bullets instantly kill, and zombies do no damage. Since everything is a pizzel, colisions shouldn't be too hard to do.
- Make zombies not pile on top of eachother
- Add different weapons and the ability to switch between them
- Add the ability to upgrade weapons, and maybe explosive weapons
- Add different ammo types
- Add different zombies with different health and movement
- Add a menu
- Add the ability for zombies to break certain types of terrain
- Add doors that the player can buy open
- Allow the player to buy placeable/breakable terrain
- Long term: Add the ability to save your game and come back later
- Long term: Add the ability to play with other people

You could use a maze generation algorithm to generate terrain. Then, you could blast some big holes in it and put things there, like zombie spawners or goods for the player. Somehow incentivies them to move from patch to patch through the maze in the map

`6/6/2022`  
Spent a stupid ammount of time making the bullets destroy the zombies. I kept getting seg faults, I am still not exactly sure how it was happening. I think it had something to do with one of the following:
- The linked list. I think somehow this was getting messed up. The change I made that ended up making everything work in the end was was making move::action return the next move, thus avoding some nonsence.
- It may have to do with virtual constructors/destructors. I am not so sure on this, but it is a thought.

It would be very useful for me to get super good at using GDB. That may have allowed me to actually find the problem and fix it, rather than just getting lucky with a workaround.

`6/5/2022`  
At first I had decided to use the visitor pattern, but there are a few issues with this. I wanted to do it to solve a circular dependency issue. I got it to work, but it is somewhat confusing. The bigger issue however, is that it leads to a God class, which has an immense amount of logic in it. I would rather the logic be put into each of the visitors, and take advantage of dynamic dispatch of pointers.  
Besides, we do not need the bigger purpose of the visitor pattern. It is meant for double dispatching, however we are always moving things relative to the map. So I just used visitor as a workaround to a circular dependency issue, which I could just forward declare in the interface (hopefully, or else I will continue to use the visitor pattern, just more sad).  
  
Very smart people exist. [Here](https://stackoverflow.com/questions/40266958/how-to-enforce-private-constructors-in-children-of-a-base-class) is something you could do to force all the constructors of your sprite implementations to have private constructors so they are all self deleting. You would then need a factory to create sprites, but that is fine.