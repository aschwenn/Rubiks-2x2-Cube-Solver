# Rubik's 2x2 Cube Solver
Program that outputs a solution to a 2x2 Cube given an input configuration

A work in progress

The goal of this project was to create a program that accepts as an input the current state of a 2x2 Rubik's Cube ("Pocket Cube"), and outputs a step-by-step Beginner's Method solution of that cube, in order to guide the user through solving it using the Beginner's Method. I haven't extensively tested the solutions, so if you encounter an "invalid cube" error for what you're sure is a valid input cube, let me know. The program contains 7 total files -- 3 header/cpp pairs and the runner file.

**Inputting the cube state**

There are 3,674,140 possible positions that a 2x2 Rubik's cube can be in, meaning it would be infeasible for the solver to have an algorithm saved for every possible combination. Therefore, the program keeps a working virtual cube in order to check the current state of the user's cube and make sure that cube turns execute as intended. The virtual cube is implemented using 3 classes: Cube, Side, and Row. The Cube class contains 6 Side objects corresponding to each side of the cube, which in turn each contain two Row objects corresponding to the upper and lower rows. Each Row object contains two integer members, a left and a right cubie (individual squares on the cube). Using all of these as well as supporting functions which compute the result of any permutations done on a side (clockwise turn, counter-clockwise turn, or double turn), the program is able to keep a virtual cube which, ideally, mirror's the user's cube. When inputting a cube state, the user is presented with a visual aid and is asked for the color of each individual cubie. These can be inputted by typing 'r' for red, 'w' for white, 'b' for blue, 'g' for green, 'o' for orange, and 'y' for yellow. The user will be allowed the chance to confirm that the entered cube state is correct before proceeding.

**Notation**

The notation commonly used for Rubik's Cube algorithms is as follows: F corresponds to the front side, B to the back side, L to the left side, R to the right side, U to the up side, and D to the down side, with regards to how the user is holding the cube. Turns are assumed to be clockwise by default (F is a clockwise turn of the front side/face), but a counter-clockwise turn is denoted by a ' (prime). Likewise, a double-turn is denoted by a 2 (it does not matter which direction the user turns in). For example, a clockwise turn of the front face followed by a counter-clockwise turn of the front face followed by two turns of the front face would be written as F, F', F2. This is the notation used in this program. It's important to keep in mind which direction is clockwise -- R corresponds to a downward turn on the right side as viewed from the front face, but L corresponds to an upward turn on the left side as viewed from the front face. Since these mistakes are easy to make, the program displays the current state the cube should be in along the way, so that the user can compare their cube to prevent any mistakes.

**Calculating the solution**

