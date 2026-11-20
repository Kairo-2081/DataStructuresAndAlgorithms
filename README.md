# Data Structures and Algorithms

C++ (and some C) implementations of the data structures and algorithms from my university coursework: lists, stacks and queues, binary search trees, AVL trees, heaps, binomial heaps, hashing, graphs, divide and conquer, dynamic programming and maximum flow. Each topic folder holds the assignment PDF next to the code written for it.

## Topics

| Topic | Folder | What is implemented | Language |
| --- | --- | --- | --- |
| Array list and linked list | `Array List and Linked list/` | A resizable array list and a linked list with `insert`, `append`, `delete_cur`, `delete_item`, `search`, `swap_ind`, `prev`/`next`, `clear` and `print`. The array list also has `trim`, `reverse` and capacity growing and shrinking. | C |
| Stack and queue | `Stack And Queue/` | A `Queue` interface with an array-based `ArrayQueue` and a linked `ListQueue`, plus a bracket-matching syntax checker for expressions. | C++ |
| Binary search tree | `BST/` | A pointer-based BST (`listBST.hpp`) built on the `BST.hpp` interface, with two driver programs. | C++ |
| AVL trees | `AVL Trees/` | An AVL tree and an interval scheduler tree, both with timing output. | C++ (Windows) |
| Heaps | `Heaps/` | A min-heap (`MinHeap.h`) with insert, get-min, extract-min, decrease-key, delete and print, driven by `main.cpp`. | C++ |
| Binomial heaps | `Binomial Heaps/` | A binomial heap (`BinomialHeap.h`) driven by commands read from standard input. | C++ |
| Hashing | `Hashing/` | A hash table with two string hash functions and three collision strategies (chaining, double hashing, custom probing), with a collision and average-hits comparison. | C++ |
| Graphs | `Graphs/` | Reads a tournament as an undirected graph and prints the groups of connected teams. | C++ |
| Divide and conquer | `Divide and Conquer/` | Connects cities given by coordinates with a minimum-cost set of edges, using divide and conquer with a configurable base case of 2 to 50 cities. | C++ |
| Dynamic programming | `Dynamic Programming/` | Weighted edit distance between two sequences, with separate insert, delete and replace costs, and the sequence of operations. Includes a PDF report. | C++ |
| Maximum flow | `Maximum Flow/` | `1.cpp`: Ford-Fulkerson maximum flow. `2.cpp`: the minimum number of aircraft needed to operate a set of flights, modelled as a flow problem. | C++ |

## Repository layout

- Each folder is one assignment and contains its PDF.
- Files next to the PDF, and in folders such as `codes_student/`, are the starter code supplied with the assignment.
- My solutions are the subfolders named `2405010` (my student ID). In `Hashing/`, `Graphs/`, `Binomial Heaps/` and `Divide and Conquer/` the solution is a single file named `2405010.cpp` (or similar) in the folder itself.
- Sample inputs and expected outputs live in `in_*.txt` / `out_*.txt` files and in folders such as `binomial_heap_sample_io/` and `Sample IO/`.

## Build and run

Everything except the AVL programs compiles with g++ 13 (`-std=c++17`) on Linux; the C programs use gcc. Compile and run each program from its own folder, because several of them read files from the current directory. File and folder names contain spaces, so keep the quotes.

### Array list and linked list

```bash
cd "Array List and Linked list/2405010"
gcc skeleton_main.c -o lists
./lists < in.txt
```

### Stack and queue

```bash
cd "Stack And Queue/2405010"
g++ -std=c++17 arrayqueue.cpp arrayqueue_tester.cpp -o arrayqueue_test && ./arrayqueue_test
g++ -std=c++17 listqueue.cpp listqueue_tester.cpp -o listqueue_test && ./listqueue_test
g++ -std=c++17 syntax_checker.cpp syntax_checker_tester.cpp -o syntax_test && ./syntax_test
```
