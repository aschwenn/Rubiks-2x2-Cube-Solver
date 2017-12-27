# Rubik's 2x2 Cube Solver
Program that outputs a solution to a 2x2 Cube given an input configuration

A work in progress

The goal of this project was to create a program that accepts as an input the current state of a 2x2 Rubik's Cube ("Pocket Cube"), and outputs a step-by-step Beginner's Method solution of that cube, in order to guide the user through solving it using the Beginner's Method. I haven't extensively tested the solutions, so if you encounter an "invalid cube" error for what you're sure is a valid input cube, let me know. The program contains 7 total files -- 3 header/cpp pairs and the runner file.

**Inputting the cube state**

The program keeps a working virtual cube in order to check the current state of the user's cube and make sure that permutations (cube turns) execute as intended. The virtual cube is implemented using 3 classes: Cube, Side, and Row. The Cube class contains 6 Side objects corresponding to each side of the cube, which in turn each contain two Row objects corresponding to the upper and lower rows. Each Row object contains two integer members, a left and a right cubie (individual squares on the cube). Using all of these as well as supporting functions which compute the result of any permutations done on a side (clockwise turn, counter-clockwise turn, or double turn), the program is able to keep a virtual cube which, ideally, mirror's the user's cube.

**Calculating the solution**

