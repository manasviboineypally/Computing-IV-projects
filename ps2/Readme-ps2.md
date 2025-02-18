# PS2: Pentaflake

## Contact
Name: Manasvi Boineypally
Section: 202

Partner Name: -
Partner Section: -

Time to Complete: 6.5hrs


## Description

This program generates and displays a Pentaflake fractal, a geometric figure composed of pentagons in a recursive pattern.
The fractal is created using the SFML (Simple and Fast Multimedia Library) for graphics and audio.
The fractal begins with a central pentagon, and smaller pentagons are recursively added around it to form a symmetric, snowflake-like pattern.
The program also includes interactive features for rotating the fractal in both clockwise and counterclockwise directions and zooming in and out.
Additionally, background audio plays as soon as the window opens, enhancing the user experience.


### Features

a) Fractal and Child Generation:
    The FractalShape class generates the fractal pattern using recursive logic in createFractal.
    The maxDepth value, provided as an argument, controls the depth of recursion, which in turn affects the level of detail of the fractal.
    Higher depth values generate a more intricate fractal.
    The positioning of child pentagons in the Pentaflake fractal is determined recursively based on geometric principles, primarily using the golden ratio. The main idea is to position smaller pentagons around a central pentagon while reducing their size at each recursive level.

    Each pentagon’s size is determined by a ratio based on the golden ratio, calculated as:
           
            double ratio = length / (1 + (1.0 + std::sqrt(5.0)) / 2.0);

    This ratio ensures that each child pentagon is smaller than its parent. The position of child pentagons is calculated using polar coordinates. Two radii are important: the **main radius**, which is the distance from the center to the vertices of the pentagon, and the **inner radius**, used to position smaller pentagons around the central one.
    Child pentagons are placed around the parent at angles of \( \frac{2\pi}{5} \), corresponding to the five vertices of the pentagon. The offsets in x and y directions are calculated as:

            double offsetX = (mainRadius - innerRadius) * std::cos(angle);
            double offsetY = (mainRadius - innerRadius) * std::sin(angle);

    This recursive process places smaller pentagons at each level, forming the fractal. The recursion continues until the desired depth is reached, creating the intricate self-similar structure of the Pentaflake.

b) Rotation
    The fractal can rotate in both directions:
    Pressing the L key toggles clockwise rotation.
    Pressing the R key toggles counterclockwise rotation.
    The rotation is achieved by modifying the currentRotation angle, and the fractal rotates around the center of the screen.

c) Color Gradient
    The fractal has a vibrant color gradient that transitions smoothly across the pentagons based on their horizontal position (x). The color gradient transitions between purple, cyan, orange, and lime green, creating a visually dynamic effect.
    The calculateColor function handles these transitions by interpolating between colors at various position ranges, resulting in a gradual shift.

d) Background Audio
    Background music automatically plays when the window opens.
    The audio file sound.ogg (which should be in the same directory as the executable) plays on a loop using the sf::Music class from SFML. The audio adds an immersive element to the program.

### Issues
    none

### Extra Credit
a)Color Interpolation:
    The calculateColor function performs gradient-based color blending, giving the fractal an appealing and complex color scheme. This isn’t just an aesthetic choice—it also illustrates creative use of color interpolation based on position.

b) Audio Integration:
    The background music, added with SFML’s audio library, gives the project a more complete and professional feel.

c) Rotation Control:
    Both clockwise(R key) and counterclockwise(L key) rotation options provide users with a better interactive experience, allowing them to appreciate the fractal from multiple angles.

## Pair Programming

## Acknowledgements
1.SFML Documentation.
2.ps2.pdf from Blackboard

## changes:
1. In detail explanation of the child rotation.
2. Rotation of the pentaflake with control.
3. Coloring to the pentaflake 
4. Audio Intergration
