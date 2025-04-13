# Scalable Gradient Descent on Large Datasets

## Overview
This project implements and benchmarks scalable gradient descent using linear regression on a large dataset (~9.8 million points). The experiments explore serial execution, OpenMP parallelization, and strong-scaling performance analysis on Purdue’s Anvil HPC system and a MacBook Pro (Apple Silicon).

## Dataset
- **Data**: `BigData.csv` (9.8 million rows of (x, y) data points)

## Methods
### Serial Implementation
- Linear regression gradient descent algorithm in C++
- Dynamically allocates arrays on the heap to manage large dataset
- Parameters: 
  - Epochs: `10,000`
  - Learning rate (`α`): `0.00002`
  - Initial coefficients (`m`, `b`): `0`

### OpenMP Parallelization
- Implemented OpenMP parallel for-loop with reduction to ensure thread-safe gradient updates and MSE calculation
- Tested thread scalability from `1` to `128` threads

## Results
- Verified correctness (no difference between serial and parallel outputs)
- Achieved ~6.7x speedup on Anvil’s HPC nodes at `16` cores
- Observed diminishing returns beyond 16 cores due to overhead and limitations defined by Amdahl’s Law
