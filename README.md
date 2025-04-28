# Efficient Algorithms for Densest Subgraph Discovery

This repository contains implementations of several algorithms for densest subgraphs in graphs, along with datasets and their analysis.

## Team Details

| Name | ID | Email |
|------|-------|-------|
| Sai Adithya Kothamasu | 2022A7PS0076H | f20220076@hyderabad.bits-pilani.ac.in |
| R.Ravikanth Reddy | 2022A7PS0068H | f20220068@hyderabad.bits-pilani.ac.in |
| Chanukya Chowdhary | 2022A7PS0131H | f20220131@hyderabad.bits-pilani.ac.in |
| Bharadwaj Thummalapalli | 2022A7PS1537H | f20221537@hyderabad.bits-pilani.ac.in |
| Mynampati Rithvik Sriranga | 2022A7PS0162H | f20220162@hyderabad.bits-pilani.ac.in |

## Individual Contributions

- R.Ravikanth Reddy - Implementation of Exact algorithm 
- Chanukya Chowdhury - Implementation of CoreExact algorithm
- Bharadwaj Thummalapalli - Implementation of Exact algorithm
- Mynampati Rithvik Sriranga - Implementation of CoreExact algorithm and Report 
- Sai Adithya Kothamasu - Project Webpage and Report

## Project Webpage

(https://adithyakothamasu.github.io/DAA_assignment-website/)

## Code Execution Instructions

### Compiling the C++ Implementations

Each algorithm is implemented as a standalone C++ program. To compile any of the implementations, use the following commands:
* Ensure your datasets are in the same directory as the source code.
* Before compilation, you need to modify the input file path in the source code to choose which dataset you want to run your algorithm on.

```bash
# Compile CoreExact algorithm
g++ -O3 -o coreexact CoreExact.cpp.cpp

# Compile Exact algorithm
g++ -O3 -o exact ExactAlgo.cpp

```

The `-O3` flag enables optimizations, which are essential for performance.

### Running the Algorithms

```bash

#  Run the executable
# run CoreExact algorithm
./coreexact <name_of_input_file>
# run Exact algorithm
./exact <name_of_input_file>
```

Each algorithm reads the graph data from the file path specified in the source code. Make sure to update this path before compilation.

### Example

```bash
# 1. Change dataset file path in source code to yeast.txt

# 2. Compile ELS implementation
g++ -O3 -o exact ExactAlgo.cpp

# 3.Run on WikiVote dataset
./exact 

# Expected output will include density and execution time statistics
```

## Dataset Preparation

The algorithms expect input graphs in the following format:
1. First line of each .txt file has number of nodes number of edges followed by h value . 
2. Each line represents a node and its neighbors
3. The first number in each line is the node ID
4. Subsequent numbers are the IDs of its neighbors

### preprocessing dataset for chiba algorithm:
- In the .txt file before running... Ensure that all the comments are removed ... And first line contains number of nodes number of edges and h value
### Datasets Used in This Project

1. **Yeast**:
2. **Ca-Hepth**
3. **Net-Science**
4. **As-Caida**5. **As-733**


