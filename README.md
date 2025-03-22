# Maximal Clique Enumeration Algorithms

This repository contains implementations of several algorithms for maximal clique enumeration in graphs, along with datasets and their analysis.

## Team Details

| Name | ID | Email |
|------|-------|-------|
| Sai Adithya Kothamasu | 2022A7PS0076H | f20220076@hyderabad.bits-pilani.ac.in |
| R.Ravikanth Reddy | 2022A7PS0068H | f20220068@hyderabad.bits-pilani.ac.in |
| Chanukya Chowdhury | 2022A7PS0131H | f20220131@hyderabad.bits-pilani.ac.in |
| Bharadwaj Thummalapalli | 2022A7PS1537H | f20221537@hyderabad.bits-pilani.ac.in |
| Mynampati Rithvik Sriranga | 2022A7PS0162H | f20220162@hyderabad.bits-pilani.ac.in |

## Individual Contributions

- R.Ravikanth Reddy - Implementation of ELS and Chiba algorithm
- Chanukya Chowdhury - Implementation of Tomita algorithm
- Bharadwaj Thummalapalli - Implementation of ELS algorithm
- Mynampati Rithvik Sriranga - Implementation of Chiba algorithm
- Sai Adithya Kothamasu - Project Webpage and Report

## Project Webpage

(https://adithyakothamasu.github.io/DAA_assignment-website/)

## Code Execution Instructions

### Compiling the C++ Implementations

Each algorithm is implemented as a standalone C++ program. To compile any of the implementations, use the following commands:
* Ensure your datasets are in the same directory as the source code.
* Before compilation, you need to modify the input file path in the source code to choose which dataset you want to run your algorithm on.

```bash
# Compile ELS algorithm
g++ -O3 -o els ELS.cpp

# Compile Tomita algorithm
g++ -O3 -o tomita Tomita.cpp

# Compile Chiba-Nishizeki algorithm 
g++ -O3 -o chiba chiba.cpp
```

The `-O3` flag enables optimizations, which are essential for performance.

### Running the Algorithms

```bash

#  Run the executable
# run ELS algorithm
./els
# run Tomita algorithm
./tomita
# run Chiba-Nishizeki algorithm 
./chiba
```

Each algorithm reads the graph data from the file path specified in the source code. Make sure to update this path before compilation.

### Example

```bash
# 1. Change dataset file path in source code to WikiVote.txt

# 2. Compile ELS implementation
g++ -O3 -o els ELS.cpp

# 3.Run on WikiVote dataset
./els 

# Expected output will include clique size distribution and execution time statistics
```

## Dataset Preparation

The algorithms expect input graphs in the following format:

1. Each line represents a node and its neighbors
2. The first number in each line is the node ID
3. Subsequent numbers are the IDs of its neighbors

### Converting Edge List Format

If your dataset is in edge list format (each line contains a pair of nodes that form an edge), you can convert it using the following Python script:

```python
import sys

def convert_to_adjacency_list(input_file, output_file):
    adjacency_list = {}
    
    with open(input_file, 'r') as f:
        for line in f:
            # Skip comments and empty lines
            if line.startswith('#') or line.strip() == '':
                continue
            
            parts = line.strip().split()
            if len(parts) >= 2:
                u, v = int(parts[0]), int parts[1])
                
                if u not in adjacency_list:
                    adjacency_list[u] = []
                if v not in adjacency_list:
                    adjacency_list[v] = []
                
                adjacency_list[u].append(v)
                adjacency_list[v].append(u)  # For undirected graphs
    
    with open(output_file, 'w') as f:
        for node in sorted(adjacency_list.keys()):
            f.write(f"{node} {' '.join(map(str, adjacency_list[node]))}\n")

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python convert.py <input_file> <output_file>")
        sys.exit(1)
    
    convert_to_adjacency_list(sys.argv[1], sys.argv[2])
    print(f"Converted {sys.argv[1]} to {sys.argv[2]} in adjacency list format.")
```

### Datasets Used in This Project

1. **WikiVote**: Wikipedia voting network
2. **Email-Enron**: Email communication network from Enron
3. **Skitter**: Internet topology graph

These datasets can be downloaded from our project webpage or the Stanford Large Network Dataset Collection (SNAP):
1. https://snap.stanford.edu/data/email-Enron.html
2. https://snap.stanford.edu/data/as-Skitter.html
3. https://snap.stanford.edu/data/wiki-Vote.html



