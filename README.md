**Author:** Austin Brennan  
**Date:** 10/24/2016  
**Course:** [CPSC 8170 - Physically Based Animation (Dr. Donald House)](https://people.cs.clemson.edu/~dhouse/courses/817/)    
**Institution:** Clemson University  
**Repository:** https://github.com/awbrenn/rigid-body

# Squishy Mesh
A rigid object that is connected to a springy string rendered in OpenGL.

## Assignment
This week, you are to redo your springy object simulation, or do an 
entirely new configuration, but this time using rigid body simulation. 
You should build one or more simple rigid polyhedral structures, and 
have them behave dynamically in a simulated environment.

Connect a springy strut to the ceiling and hang a rigid body from it. 
Start it bouncing around, and the strut forces on the rigid body should 
cause it to bounce around and induce rotations.

##Features
* Obj loader for arbitrary mesh
* Ability to interact with the object

## Compilation
```
$> cmake CMakeLists.txt
$> make
```


## Usage
```
$> RigidBody parameters
```

## Interaction
```
w/a/s/d - move the ball around
g       - Toggle grid
esc     - Quit the program
q       - Quit the program
```

## Acknowledgements
Vector Class - Donald House

Matrix Class - Donald House

Camera Class - Christopher Root, Donald House, Yujie Shu
