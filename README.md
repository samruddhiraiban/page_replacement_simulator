
# Page Replacement Simulator

## Introduction
This project simulates page replacement algorithms used in Operating Systems.

## Objectives
- Understand page replacement.
- Simulate FIFO, LRU, and Optimal algorithms.
- Count and compare page faults.

## Algorithms Used
1. FIFO (First In, First Out): Replaces the page that entered memory first.
2. LRU (Least Recently Used): Replaces the page that has not been used for the longest time in the past.
3. Optimal: Replaces the page whose next use is farthest in the future.

## Technologies
- Programming Language: C++
- Concepts: Arrays, Functions, Loops, Conditional Statements

## How to Run
Compile:
g++ main.cpp -o page_replacement

Run on Windows:
.\page_replacement.exe

## Limitations
This is an educational simulation. It does not manage actual computer memory.

## Conclusion
The simulator demonstrates three page replacement algorithms and compares their page fault counts.