<p align="center">
    <table>
        <tr>
            <td><a href="./step-2.md">🡐 Previous step</a></td>
            <td><a href="./step-4.md">Next step  🡒</a></td>
        </tr>
    </table>
</p>


&nbsp;
&nbsp;

# Step 3
## Moving the player
We now have a background working, and a camera system which moves the camera relative to the player. However, the player currently can't really move. The turret moves correctly, and we can rotate the tank body with the `A` and `D` keys. But we can't really move the tank; this doesn't make for a great game experience.

Let's add some movement. To do this, firstly open `PlayerObject.cpp` and navigate to the `HandlePlayerMovement` (`PlayerObject::HandlePlayerMovement`) function. You will see there is currently a bit of code in here which does:

1) Find the current movement vector based on WASD. If we press `A`, this would be -1 on `x` and 0 on `y` (-1, 0). If we press `S` this would be 0 on `x` and 1 on `y` (0, 1), etc.
2) If there is no movement, skip the rest of this function.
3) Get the tank's current rotation angle and move towards a target angle based on the movement vector. 
4) Calculate some vectors which we will use to move the tank.

To move the tank, we want to move its position forward/back relative to it's orientation. If we press `W`, the tank should move forward, and `S` for backwards. This is what `tankMoveVec` is.

Find the comment this point:

```cpp
//Add code to calculate new player position, and move them, here.
```

And paste the following code below this line:

```cpp
Vector2 targetPos = tankPos + tankMoveVec * movementVec.y * Time::deltaTime * tankMoveSpeed;

//Set the position of the player to this target position
SetPosition(targetPos);
```

Save the file with `Ctrl+S` and press the **Play button**. The tank should move forwards and backwards when you use `WASD`!

Things to do:
- Try change the `tankRotationSpeed` value to lower (try `50`) and higher (try `300`) values. How does this affect the tank?
- Try change the `tankMoveSpeed` value to lower (try `25`) and higher (try `100`) values. How does this affect the tank?
- Play with these values until you get something that feels nice.
- What happens when you try move outside the walls of the map?

### Collisions!
As you might have experienced, the player currently can move outside the map -- there is no collision. Let's add some code to deal with this.

Between the two lines you just pasted (`SetPosition` and `Vector2 targetPos = ...`), paste the following code:

```cpp
//If the new position is intersecting a wall.. we can't move!
if (tilemap->CollidingWithPoint(targetPos))
    return;
```

This simply checks the tilemap at the new position, and if it is impassable, skips the `SetPosition` call. This means the player doesn't move. Try it out!


## Firing bullets
What good is a tank which doesn't shoot bullets? Let's now consider the possibility of letting the player shoot. This will eventually be useful when we add enemies later in this session. There are two types of gun on the tank:

1) The main shell (`Left click`): this spawns an explosion at the reticle's position and kills enemies within the radius. 
2) The gun (`Right click`, hold): this spawns many bullets over time, emitting from the turret. 

We have to consider two parts to the code here. Namely, we need to write some code to trigger the `FireBullet` and `FireShell` methods. For the gun, this will involve a timer, as bullets should be spawned over time. For the shell, this will involve spawning a certain object in the world. Secondly we need to write the code to actually fire a bullet and shell.

### Gun timer
Find the `HandlePlayerFiring` function and navigate to it. Just below the first comment, paste the code:

```cpp
if (inputManager.GetRightMouseDown())
{
    if (gunTimer.Tick())
    {
        FireBullet();
    }
}
```

This checks if the right mouse is held down. If it is, it increments the timer. If the gun needs to fire based on this timer, it will call the `FireBullet` function which will (eventually) spawn a bullet.

Below the second comment, paste:

```cpp
if (inputManager.GetLeftMouseDownThisFrame())
{
    if (Time::elapsedTime - lastShellTime >= 2.0f)
    {
        lastShellTime = Time::elapsedTime;
        FireShell();
    }
}
```

This check if the left mouse is down -- if it is, it checks the time between the last shot and now. If this is over 2 seconds (`2.0f`), it sets the last shot time to now, and (eventually) fires the shell.

Things to note:
- Later when we spawn the shell, this `2.0f` value is the value to change if you want to increase the time between shots. Changing it to `0.5f`, for example, will be half a second (500ms).
- When we spawn the bullet later, the gun's timer can be changed in the constructor of `PlayerObject`. Find the line `gunTimer = Timer(0.1f)`. Changing this `0.1f` to, for example, `1.0f`, will fire a bullet every 1 second. Be careful with this value: setting it very low values might crash the game!

Testing this out won't result in much, as the two methods currently do nothing. Let's change that!

### Firing bullets
Find the `FireBullet` method in `PlayerObject.cpp`. Below the first comment, paste:

```cpp
//For calculating angles
Vector2 playerPos = GetPosition();
Vector2 mousePosWorld = GetMousePosWorld();

//Find angle from player -> mouse, add a random amount to introduce
//inaccuracies. Change -2.0 and 2.0 to higher values for higher 
//inaccuracy!
float origAngle = Math::AngleBetween(mousePosWorld, playerPos);
float angle = origAngle + Random::Range(-2.0f, 2.0f);

//Find the direction to fire in, as a vector
float bulletSpeed = 250.0f;
Vector2 fireDirection = Vector2::FromPolar(angle, 1.0f).Normalized() * bulletSpeed;

//Fire the bullet
Vector2 spawnPos = GetBulletSpawnPos();
BulletManager::FireBullet(spawnPos, fireDirection);

//----
//VFX

Vector2 direction = GetFireDirection() * 3;
DrawMuzzleFlash(spawnPos + direction, origAngle);

Vector2 fireDir = fireDirection.Normalized();
DrawTracerLines(spawnPos, fireDir);	
```

Save the file and press the **Play button**. Hold down right click and see if it works!

Things to note:
- The lines of code below `// VFX` are optional -- they just provide visual feedback to show the player the gun is firing.
- The `bulletSpeed` variable controls how fast the bullet fires out of the turret. Change this to something you like.
- The `angle` variable controls the degree of inaccuracy when spawning bullets. Try change the values in `Random::Range(-2.0f, 2.0f)` to `-10.0f` and `10.0f` to see a wildly different result!
- The actual bullet spawning method is `BulletManager::FireBullet` which takes a spawn position (1st param) and spawn direction (2nd param). If you wanted to, for example, fire bullets in multiple directions, you could call this method a few times in succession.

### Firing shells
Navigate to the `FireShell` method in the same file. Under the first comment, paste:

```cpp
//Get positions for calculating explosion position
Vector2 playerPos = GetPosition();
Vector2 mousePosWorld = GetMousePosWorld();

//Find angle to mouse
float angle = Math::AngleBetween(mousePosWorld, playerPos) + 90;

//And add a shell at the mouse position
parentScene->AddObject(new ShellCollisionObject(inputManager.GetMousePos(), 30, parentScene));

//VFX
//---

//Spawn some explosions
Vector2 explosionPos = GetShellSpawnPos(3);
VFXManager::SpawnEffect(explosionPos, "muzzleFlashBig", 24, 1.0f, angle);
VFXManager::SpawnEffect(explosionPos, "explosion-1", 24, 1.0f, angle);

//Shake the camera
VFXManager::CameraShake(0.25f, 10);
```

Try it out by pressing play and click the left mouse button in the game!

Things to note:
- As with the previous example, everything below `// VFX` is optional. Here we have the `SpawnEffect` which spawns a temporary particle effect. In these examples, `24` is the animation speed, `1.0f` is the size, and `angle` is the rotation.
- The `CameraShake` method does just that: shake the camera. In this case, it shakes it for `0.25f` seconds with an intensity of 10.
- We make the shell explosion object with the `parentScene->AddObject(...)`. This works by spawning a rigidbody for a few frames, detecting collision with enemies, and destroying them. The value `30` on this line is the radius -- how big the explosion is. Later, you may want to tweak this value to something you like.

<p align="right" style="float: right;">
    <table>
        <tr>
            <td><a href="./step-2.md">🡐 Previous step</a></td>
            <td><a href="./step-4.md"><b>Next step  🡒</b></a></td>
        </tr>
    </table>
</p>
