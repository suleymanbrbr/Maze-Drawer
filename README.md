# Maze-Drawer


Create a program that generates a random maze of size MxN, where M is the number of rows and N is the number of columns. Additionally, implement a function that finds the path between specified entry and exit points in the generated maze.

# CS300 – Spring 2023-2024 - Sabancı University
# Homework #1 – Maze

**Due Date:** March 21, 2024, Thursday, 22:00

## Brief Description
In this project, I will implement a program that generates a random maze of size MxN (where M is the number of rows and N is the number of columns) and a function to find the path between designated entry and exit points in the maze. You are required to implement a stack using a LinkedList data structure (not using vectors). The stack class must be template-based.

## Requirements
1. **Maze Generation:** 
   - Create a maze with M rows and N columns.
   - Ensure the maze has a random structure.
   
2. **Path Finding:**
   - Implement a function to find a path from the entry point to the exit point.
   - Use a stack implemented with a LinkedList data structure.
   
3. **Stack Implementation:**
   - Implement a template-based stack class.
   - Do not use vectors; use LinkedList for stack operations.

## Program Flow
1. Prompt the user to enter the number of mazes.
2. For each maze, prompt the user to enter the number of rows (M) and columns (N).
3. Generate the mazes and display them.
4. Prompt the user to enter the maze ID to find a path.
5. Prompt the user to enter the entry (x, y) and exit (x, y) coordinates.
6. Display the path if found or a message indicating no path exists.

