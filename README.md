# Genetic Algorithm Implementation

This project implements a genetic algorithm framework designed to solve optimization problems. The algorithm evolves populations of candidate solutions over generations by applying selection, crossover, and mutation operations to find optimal or near-optimal solutions.

---

## Features

- **Flexible Candidate Types:** Supports different problem formulations through polymorphic candidate classes.
- **Configurable Parameters:** Adjustable population size, stopping conditions, and genetic operation settings.
- **Multiple Stopping Criteria:**
  - Maximum number of generations
  - Minimum improvement threshold (percentage)
- **Genetic Operations:**
  - Roulette wheel selection
  - Single-point crossover
  - Bit-flip mutation
- **Problem Types:**
  - Two-variable optimization (`TCandidate_Zad1`)
  - Alternative two-variable optimization (`TCandidate_Zad2`)
  - Three-variable optimization (`TCandidate_Zad3`)

---

## How to Use

### Build the program with CMake

1. Create and enter the build directory:

```bash
mkdir build
cd build
```
2. Generate the build system with CMake:

```bash

cmake ..
```
3. Build the executable:

```bash

cmake --build .
```
4. Run the program
From the build directory run:

```bash

./genetic_algorithm
```
### When prompted, choose a problem type:

1 for TCandidate_Zad1 (2 variables: x1, x2)

2 for TCandidate_Zad2 (function: x1 * x2 + x2)

3 for TCandidate_Zad3 (function: x1 + x2 + x3)

## Configuration

Algorithm parameters can be adjusted in `main.cpp`:

| Parameter             | Description                                  |
|-----------------------|----------------------------------------------|
| `candidates_count`    | Number of candidates in each population      |
| `max_population_count`| Maximum number of generations                 |
| `min_improvment_proc` | Minimum improvement percentage threshold     |
| `pop_check`           | Number of previous generations considered for improvement |

---

## Implementation Details

### Key Classes

- `TCandidate`: Abstract base class for candidate solutions.
- `TCandidate_Zad1`, `TCandidate_Zad2`, `TCandidate_Zad3`: Concrete implementations for different optimization problems.
- `TParam`: Represents a single parameter with a value range.
- `TPopulation`: Manages a collection of candidates.
- `TAlgorithm`: Controls the evolutionary process.

### Genetic Operations

- **Selection:** Roulette wheel selection based on fitness.
- **Crossover:** Single-point crossover with 25% chance.
- **Mutation:** Bit-flip mutation with 5% chance per bit.

---

## Example Output

The program will display:

- Current generation number and best fitness value.
- Final best candidate details.
- Best value found overall.

---

## Future Improvements

- Add more problem types.
- Implement additional selection methods (e.g., tournament, rank-based).
- Add configuration file support.
- Implement parallel processing for fitness evaluation.

---

## Example Output

The program outputs:

- Current generation number and the best fitness value found.
- Details of the best candidate solution in the current generation.
- The overall best solution found after termination.

![Example output screenshot](assets/demoss)
