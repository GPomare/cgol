# CGOL: Conway's Game of Life
From Wikipedia, the free encyclopedia:

    The Game of Life, also known simply as Life, is a cellular automaton devised by the British mathematician John Horton Conway in 1970. The game is a zero-player game, meaning that its evolution is determined by its initial state, requiring no further input. One interacts with the Game of Life by creating an initial configuration and observing how it evolves, or, for advanced players, by creating patterns with particular properties

This is a C+++ implementation of Conway's Game of Life. It allows you to enter a text file containing '-' and 'x' characters. The evolution of the cells follows this four simple rules:

Any live cell with fewer than two live neighbors dies, as if by underpopulation.
Any live cell with two or three live neighbors lives on to the next generation.
Any live cell with more than three live neighbors dies, as if by overpopulation.
Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.


# Usage
Usage of cgol:

    cl.exe cgol.cpp -o cgol.exe
    ./cgol.exe <board file e.g glider.txt> <optional iterations>
