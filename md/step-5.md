<p align="center">
    <table>
        <tr>
            <td><a href="./README.md"><b>🡐 Back to start</b></a></td>
            <td><a href="../step-4.md">🡐 Previous step</a></td>
        </tr>
    </table>
</p>


&nbsp;
&nbsp;

# You're done!
Congratulations, you've made it to the end of all the tasks! You can either finish up now and save everything. Feel free to show off what you've made today to us, we're always happy to see your spin on it. 😊 

Thank you for coming along today, we really appreciate your time. We hope to see you soon if you choose to join us at the University of Staffordshire. We're an institute passionate about games, and this taster session is just a small example of what is to come if or when you join us!

If you have some time left, you might be wondering what you can do until the end of the session. The following are some ideas depending on what you want to do, and how you feel.

## Tag us on social media
If you enjoyed today, tell us about it! We'd love to hear from you both in the class and on social media. We always enjoy hearing your thoughts on the experience you had today. You can find all our social media pages at:

https://www.staffs.ac.uk/socialmedia/home

## Browse our games courses
See more about our games courses [here](https://www.staffs.ac.uk/courses/undergraduate/study/games), if you're interested. We are also happy to answer any questions you might have about our courses. Grab one of us before you leave and we'll answer any queries you may have!


## I want to continue working on this at home
Feel free to save up your project and load it onto a USB drive if you have it available. We also have `git` installed on these machines if you wish to push it to your Github repository.

If you want to re-do this activity at home, you can visit https://github.com/StaffsUniGames/sdl-topdown-game, which contains all these instructions and the starter files. A QR code link for this is below.

![](qr.png)

Don't forget to star this repository on Github if you enjoyed today, or fork the repostiryo if you want to use it to explore more of SDL and C++. 😊

## I want to try another taster activity
We have two other taster day activities which you can try, both at home, and here today:

- [In-browser 2D platformer activity](https://staffsunigames.github.io/ohd-editor/#/): An online taster activity you can access from a browser, with no IDE! *(approx 30 mins completion time)*
- [S2DPlatformer](https://github.com/StaffsUniGames/S2DPlatformer): Another 2D C++ taster day activity built with OpenGL. *(approx 45 mins completion time)*


## I want more tasks to complete today
There are lots of things you can work on until the session end:

- So far, we've only touched files in the `Source Files > game` filter in the solution explorer panel. However, this game is built atop of a small component-based 2D engine. If you're curious, why not start by opening up some of the engine files, and poking around? Here are some things you can start with:
    - What does the `Rigidbody` class do?
    - Examine the `Game.cpp` file -- this is where you will find the main initialisation for the engine and the underlying SDL calls for initialisation. It also gives you a high-level overview of what the engine is doing.
    - Examine the `main.cpp` file; you may notice it is similar in nature. This is the backbone of the entire game loop.
- Having explored `main.cpp`, try change the game window size from `800x600` to something larger, e.g. `1064 x 798`.
    - What does the third parameter do in the constructor of `Game`? Currently `false` is being passed in (ln 7, `main.cpp`). What if you change this to `true`?
- Add more spawnpoints to the JSON file, so enemies have
- Explore the `VFXManager` class. Then, look in `Game.cpp` to see what textures are being loaded.
    - Explore what `DrawLine` does; try draw lines from each enemy to the player, for example. 
    - Add more particle effects throughout the game at various points (e.g. when an enemy dies, when the player hits a wall, etc) to make the game more "juicy".
- The player's health is currently at 100.0 by default. Add a variable max player HP and update the healthbar to match it.
    - Can you change the colour over time, e.g. red when low HP and green when high?

## I want more challenging tasks to complete at home.. what are some directions I could take this in?
- Make it your own!
    - Change the tilemap, change the sprites, make your own art, change everything you want! 😊
- Make the game harder by decreasing the enemy spawn time over time.
- Add different enemy types, e.g. enemies with different sprites and parameterised damage values
- Build a wave spawner. Currently enemies spawn over time. What if waves of enemies could be specified in a JSON file and loaded into the game?
- Build a more realistic tank controller.
    - At the moment, the tank accelerates immediately. Can you make the controller feel more realistic?
- Examine the `Text` class and note how it can be used to render text effects.
    - Add a debug mode where `D` can be pressed. 
    - When activated, it should render the bounding boxes of every `BoxCollider` in the scene.
    - It should also display the name and position above each `GameObject` in the scene.
- Add to the engine:
    - You may notice that the tilemap uses a streaming system to reduce the rendering overhead. It is also static, there are no moving elements. This can therefore be further optimised by rendering the entire map to a separate texture (see render targets in SDL2), avoiding the need to loop over each tile. 
    - Add spatial hashing methods for `Rigidbody` $	\Leftrightarrow$ `Rigidbody` collisions, as currently, the time complexity is $\mathcal{O}(n^2)$. This is notably quite slow for much higher entity counts.
    - Enemies are still updated and processed even if they're off screen. Think about how you could optimise with this in mind.
    - Refactor parts of the code; some significant parts of this engine could do with some quality-of-life features and polish!
    - Add [imgui](https://github.com/ocornut/imgui) for more elaborate UI.
    - Add sounds with `SDL_mixer`.
    - Add joypad support.
    - Add an option to render sprite "shadows", which are just masks of the sprite but tinted a dark colour. 
    - Add parallax support for sprites.
    - Add a decorative layer atop the current tilemap system, such that the tiles can be rendered over `GameObject`.
    - Add pathfinding support.

## I want to learn more about C++ and SDL! Where would I go from here?
There are a number of C++ and SDL resources which can get you started.

- If you prefer video tutorials, [@TheCherno](https://www.youtube.com/@TheCherno) on YouTube has a good series on C++ to start with.
- [learncpp.com](https://www.learncpp.com/) and [w3schools](https://www.w3schools.com/cpp/default.asp) are good C++ starters.
- [Lazy Foo Productions](https://lazyfoo.net/tutorials/SDL/) is a great starter resource for SDL.
- Optimisation is a huge part of C++. Learn about it in [Nystrom's book](https://gameprogrammingpatterns.com/) on programming patterns, or in [Gregory's engine architecture book](https://www.gameenginebook.com/), or [Fabian's DOD book](https://www.dataorienteddesign.com/dodmain/).

The best resource to learn C++ for games is right here at the University of Staffordshire. We cover C++ from scratch at the start of year #1, in [GDEV40024: Programming Fundamentals](https://evision.staffs.ac.uk/module_descriptors/GDEV40024.html). Throughout your three years here, we go from the basics to building entire 3D engines. Talk to one of us for more info, or visit our [site](https://www.staffs.ac.uk/courses/undergraduate/study/games)!



<p align="right" style="float: right;">
    <table>
        <tr>
            <td><a href="./README.md"><b>🡐 Back to start</b></a></td>
            <td><a href="../step-4.md">🡐 Previous step</a></td>
        </tr>
    </table>
</p>
