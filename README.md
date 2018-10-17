# FIT2097_Assignment2

As all the requirements listed in the brief "marked [No Change] are optional and do NOT need to be included in your submission", they are not included in this project. 
(Moodle Forum post "[Please Read] Assignment 2 Requirements Clarification" posted by Chris Nelson - Tuesday, 16 October 2018, 11:08 AM, https://moodle.vle.monash.edu/mod/forum/discuss.php?d=1491574)

Left click is used for all interactions in the game.

How To Play:

Room 1
 - Pick up fuse
 - Player that has fuse must put into fuse box
 - Any player can now pull the switch which will open Door 1
 
Room 2
 - One player must stand on the white pressure plate
 - While that player is on the pressure plate, the other player must go through the door and stand on the opposite pressure plate
	to allow the first player to walk through the door

What Works:

- UI Displays the different items the relevant player has, such as keys, fuses etc
- UI Displays the relevant player’s health
- UI Shows relevant messages on screen such as when a door has been unlocked (Messages shown to all players)
- All existing gameplay actors support multiplayer replication
- Character and GameMode classes written in C++
- Interaction with game objects driven by a Trace written in C++ rather than collision boxes. The debug trace line left ON.
- Fuse to a powered door – the player must find a fuse for a powerbox. Once the fuse is placed they can flip the switch and the 
  door will open.
- A particle emitter and a sound are played when the fuse is placed in the power box
- Remote Unlock for co-op play – one player must activate a switch at a remote location, which opens a door. When the switch
  is released the door closes. There is a second identical switch on the other side of the door to allow the second player to 
  get through the door. Players must cooperate to get through the door.


References:
Electric Spark Sound provided by JoelAudio from freesounds.org
(https://freesound.org/people/JoelAudio/sounds/136542/)
