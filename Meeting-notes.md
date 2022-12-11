# Meeting Notes

In this file, you are required to take notes for your weekly meetings. In each
meeting, you are required to discuss:

1. What each member has done during the week?
2. Are there challenges or problems? Discuss the possible solutions
3. Plan for the next week for everyone
4. Deviations and changes to the project plan, if any


# Meeting 2.11.2022 2H::0M

**Participants**:

1. Roosa Ahlroos
2. Lauri Karanko
3. Severi Koivumaa
4. Karl Rass

## Summary of works

None of the members had done much prior work yet as the groups were formed a day
ago. We had all read the requirements for the project and the tower defense game
but all of us felt a little bit overwhelmed about where to begin.

## Challenges

1. The deadline for the project plan is 11th of november so a little over a week
   away. This means that we have to acquaint ourselves to what exactly has to be
   done (already written in the requirements) but more importantly what
   libraries should be used to implement those features.
2. After we have an understanding of what work needs to be done, we have to do
   the work division and write the project plan document.

## Actions

1. First we are going to reach out to our instructor to see when they could
   possibly meet with us.
2. We agreed that everyone would all research the tower defense game topic and
   try to find example implementations. This is important because it will give
   us a better understanding of the architecture of the program since none of us
   have designed a game before.
3. We will also look into the SFML and Qt libraries to see what opportunities
   they provide.

> Please reflect these action decisions in your git commit messages so that your
> group members and advisor can follow the progress.

## Project status

Short summary of current project status.

### TODOs

1. Everyone is going to research the libraries and ideas for implementation as
   identified above. We will also send out the email to our advisor before the
   end of this meeting.



# Meeting 08.11.2022 2H::49M

**Participants**:

1. Roosa Ahlroos
2. Lauri Karanko
3. Severi Koivumaa
4. Karl Rass

## Summary of works

We met in Teams and started out with creating a shared Word document to get
started with the project plan. We went over different classes and attributes
that we think would be useful in addition to general rules of the game.

## Challenges

1. How to set up libraries
2. What classes to use
3. Should we use a tile system

## Actions

We will all continue writing out the plan and research more about the subject.

> Please reflect these action decisions in your git commit messages so that your
> group members and advisor can follow the progress.

## Project status

We have currently only worked on the project plan and added meeting notes.

### TODOs

1. Continue research into the subject
2. Meet again on Thursday and hopefully finish the plan



# Meeting 11.11.2022 1H::4M

**Participants**:

1. Roosa Ahlroos
2. Lauri Karanko
3. Severi Koivumaa
4. Karl Rass

## Summary of works

We finished the project plan and divided the work between the team members. The
division is not done too strictly and will be up for discussion in the later
meetings, when we have more of an idea just how much work they require.

## Challenges

1. Dividing the work into blocks of hopefully semi equal size
2. Getting started with actual coding

## Actions

1. Roosa will start work on the GUI
2. ... And Lauri with enemies-class
3. ... And Severi with both the game loop and level & tile classes
4. ... And Karl with towers-class and level design

> Please reflect these action decisions in your git commit messages so that your
> group members and advisor can follow the progress.

## Project status

We now have a base idea about what and who will be doing what. We have made
decisions on some of the details of our game, but everything is still a work in
progress.

### TODOs

The TODOs reflect the actions listed.



# Meeting 16.11.2022 1H::17M

**Participants**:

1. Roosa Ahlroos
2. Lauri Karanko
3. Severi Koivumaa
4. Karl Rass
5. Kasper Kivimäki (advisor)

## Summary of works

1. Roosa Ahlroos

First screen in the menu. Implentation of menu which tracks users input.

2. Severi Koivumaa

Impelementation of map with level, tile, game classes.

3. Karl Rass

Implementation of tower class. Instead of abstract tower class, made a basic
tower class that can be inherited for different types. Tower have different
attributes that can be changed.

4. Lauri Karanko

Implementation of enemy classes. Three different enemy types implemented through
macros.

## Challenges

1. Problems with trying to get SFML to compile with CMake.

2. Debugger is not working.

## Actions

1. Roosa will start work on how-to menu and level selection menu.
2. Karl will implement necessary features to towers to implement them to map.
3. Lauri will implement necessary features to enemies to implement them to map.
4. Severi will add functionality to tiles to add enemies and draw them in map.

## Project status

Initial implementation of different classes have been made, but we are having
issues with compiling and debugging. Progress looks good to be in track with
plan and we should have some sort of working GUI next week.

### TODOs

1. Adding towers and enemies to level map.
2. How-to in the menu
3. Having a menu with level selection




# Meeting 23.11.2022 3H

**Participants**:

1. Roosa Ahlroos
2. Lauri Karanko
3. Severi Koivumaa
4. Karl Rass

## Summary of works

1. Roosa
Menu screen and implementation. Different level options behind a menu button.
Generic button-class for ingame buttons.

2. Severi
Further development with the map with level, game and tile classes.
Tiles can hold occupants. Enemies and towers emerge when clicked on the road or the grass.
Texture-support. Enemy damage and tower upgrade when clicked

3. Karl
Tweaking of the tower-class. New sniper-tower. Research for game audio.

4. Lauri
Tweaking of the enemy-class. Making textures for enemies and towers.

## Challenges

1. Still problems with trying to get SFML to compile with CMake.
2. Getting the game to work on everyone's computers.

## Actions

1. Roosa: Menu and game interface and communication
2. Karl will look more into audios and also towers detection range if needed
3. Lauri will help with game class and do more textures. (Also maybe compiling research.)
4. Severi will implement enemy-movement.

## Project status

Game has placeable towers and enemies. Enemies can be killed and towers can be upgraded by clicking them.
Menu looks good and has interacable buttons, but doesn't yet connect to the game-object. 
(We also asked Kasper help with CMake and compiling.)

### TODOs

1. Add a wallet for storing cash
2. Button from the menu starts a game
3. Enemies emerge and go towards the end through the path
4. Two different phases: fighting and shopping
5. Towers detecting enemies




# Meeting 28.11.2022 0H::40M

**Participants**:

1. Roosa Ahlroos
2. Severi Koivumaa
3. Karl Rass

## Summary of works

1. Roosa

   Worked on combining the menu together with the game

2. Lauri

   Added more pictures in the pics-folder and worked on the building process for mac

3. Severi

   Added the movement of the rabbit and the implementation of creating damage

4. Karl

   Work involving implementing audio

## Challenges

1. Looping the game for different rounds
2. How to extend the game window to add a sidebar
3. How to add audio
4. Problems with cMake

## Actions

1. Roosa is going to start working on adding a sidebar for the game window
2. Lauri might (since this meeting was a last minute decision and the timing of the meeting didn't work for him) start work on the background for the menu
3. Severi is going to work on implementing the repeating rounds
4. Karl will work on the maps for different levels

> Please reflect these action decisions in your git commit messages so that your
> group members and advisor can follow the progress.

## Project status

The project has most of the basic elements done but needs still some work

### TODOs

Reflected in the actions-section




# Meeting 30.11.2022 1:30

**Participants**:

1. Roosa Ahlroos
2. Severi Koivumaa
3. Karl Rass
4. Lauri Karanko

## Summary of works

1. Roosa
   Worked on adding background image to menu screen

2. Lauri
   Menu screen image

3. Severi
   wave implementation and working money usage
   Spawning enemies during waves

4. Karl
   Implementing nonhardcoded levels and a function to read them from a file
   Creating a few level types

5. During the meeting: Some start/ideas on reading files and creating levels based on it

## Challenges

1. Sidebar
2. How/where to read the level-design files

## Actions

1. Roosa: Looking into getting the sidebar to the game.
2. Lauri: Looking into pop up -windows / other additional features.
3. Severi: Adding the animations for the snowballs and features regarding the winning/losing condition.
4. Karl: Balancing values for money and HP etc. so that game dynamic works better. Also sound effects.

> Please reflect these action decisions in your git commit messages so that your
> group members and advisor can follow the progress.

## Project status

The project has large portion of the mandatory features in it, although values for damage, HP and speed need adjusting.
Animations for towers shooting the enemies would be nice.

### TODOs

Some changes are needed also in upgrading process of the towers.
Animation, sounds, moving projectiles.
Maybe multiple paths for enemies.
Other TODOs reflected in the actions-section.


# Meeting 7.12.2022 01::53

**Participants**:

1. Roosa Ahlroos
2. Severi Koivumaa
3. Karl Rass
4. Lauri Karanko

## Summary of works

1. Roosa Ahlroos

   - Implemented sidebar with a go button to start a round.
   - Implemented tower selling (and deletion).

2. Severi Koivumaa

   - Implemented towers turning towards enemies they are targeting
   - Implemented snowballs to fly from snowmen to rabbits when they are shooting

3. Karl Rass

- Added different level designs with 

4. Lauri Karanko

- Made documentation file and started work on it with initial version

## Challenges

1. Game is still quite unbalanced
2. We cannot figure out how to have the whole game not close with level window closing.
3. Upgrade don't take money away

## Actions

1. Severi will get rid of debug menus and try to move them elsewhere. Also he will disable enemy spawning and killing by clicking.
2. Karl will attempt to add music.
3. Everyone will write the documentation.
4. Everyone will work on the game balance.
5. Roosa will change max rounds on sidebar.
6. Severi will change enemy types in a round.
7. Everyone will comment code.
8. Lauri will update Readme file.

## Project status

Actual game is basically ready. We still have to balance the game and during the meeting we agreed on prices for enemies.

### TODOs

1. Get rid of the debug info from the top left corner and move necessary info to somewhere else (or just make it prettier)
2. General game balancing
3. Game documentation
4. Plan the demo
5. Disable enemy spawning on clicking
6. Try adding music
7. Implement different types of levels
8. Tower building cost the same for every tower
9. Different tower types and attributes for them should have their own constructors somewhere














# Meeting dd.mm.2022 HH::MM

**Participants**:
1. Member 1
2. Member 2
3. Member 3
4. Member 4

## Summary of works
1. Member 1
   Implementing the class XX. Tested the class XX. Results are in
   `tests/<class-xx-tests>`. Resolved the identified problems.
2. Member 2
   Same as above
3. ...

## Challenges
1. The integration of UI with the monsters requires an abstract interface.
2. ...

## Actions
1. Member 1 is going to look into defining an abstract interface for monsters to
   enable easy UI integration.
2. Member 2 is going to work with Member 1 to use abstract interface in derived
   monster classes.
3. Member 2 is going to test the interface.
4. Member 3 is going to use ...

## Project status
Short summary of current project status.

### TODOs
1. Member 1: Write an action.
2. ...
