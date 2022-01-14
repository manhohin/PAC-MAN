# multiplayer_pacman



NOTE:
When compiling the game, please compile it in the same folder as map.txt so that the program can read the map. In Qt, please press "Build" on the top panel and press all of the "Clean" in the panel before compiling. Also please make sure Qt:multimedia library has been installed.


The elements of this game was a modification of the original Pac-Man game. The difference between this game and the original Pac-man game is that this game is a multiplayer game compared to the original one.

After the "Start game" button was pressed. The two players will have to control the two "Pac-man"s by using the WASD and arrow keys on the keyboard. Similar to the original Pac-man game, "small dots" will be spawned around the map for the players to eat. Normally, for each dots eaten, 1 score will be added to the respective player. 4 "ghosts" will be spawned at the beginning of the game and under normal conditions, the 4 ghosts will wander around the map looking for the players. When the players touch one of the ghosts, score will be lose and the player will be teleported to the starting point of the player. There will be 3 power-ups spawned at random position around the map at all times. Players can consume the powerups and gain advantage of the game when the power-ups are in effect (for 10 seconds). The power-ups and effects are:

1. Attack---The player who consumes this power-up gains the ability to "eat" the other player. When the player "eats" another player, 5 points will be transferred from the player who got eaten and the player who eats the other player.
2. ScoreBuff---The player who consumes this power-up can gain 2 points instead of 1 when they eat a "small dot"
3. Speed Up---The player who consumes this power-up can move faster
4. Speed Down---The player who consumes this power-up can cause the other player to move slower

There will also be 4 "bigdots" in total spawned at fixed location at the start of the game. When one of the players consume a "bigdot", players can "eat" the ghosts instead. Extra scores will be given for the player who eats a ghost. The ghost who was eaten will go back the center of the map.

The ultimate goal is to gain a higher score. When all of the "small dots" on the map has been eaten, the game will end and the player who got a higher score wins.
