# Lagrange Interpolation with MSE Analysis

## Description
Implements Lagrange polynomial interpolation and analyzes interpolation accuracy using Mean Squared Error (MSE). Tests optimal number of interpolation nodes for the Runge function f(x) = 1/(1+x²).

## Features
- Lagrange polynomial interpolation
- Mean Squared Error calculation
- Optimal node count determination
- Runge function analysis (demonstrates Runge's phenomenon)
- File-based data input processing

## Mathematical Background
- **Lagrange Interpolation**: Constructs polynomial passing through given points
- **Runge Function**: f(x) = 1/(1+x²), classic example showing interpolation challenges
- **MSE Analysis**: Quantifies interpolation accuracy for different node counts

## Usage
Requires "dane.txt" with interpolation data in format:
```
xi: [x values]
f(xi): [corresponding function values]
