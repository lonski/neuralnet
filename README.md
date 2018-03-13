# Neuronomator

[![Build Status](https://travis-ci.org/lonski/neuronomator.svg?branch=master)](https://travis-ci.org/lonski/neuronomator)

Neural network backpropagation alghoritm implementation.

## Building

```
mkdir build && cd build && cmake .. && make
```

## Running

### Main

```
./neuralnet
```

### Tests

```
./neuralnet_test
```

### Example usage

```
 :: Neuronomator 6000 ::
-----Menu-----------------------------------------------------------------------
1. Enter network parameters
2. Use example parameter set
0. Exit

>2
 Input    H00  H01   Output 
          |o|  |o|          
|0.05  |  |o|  |o|  |0.01  |
|0.1   |  |o|  |o|  |0.99  |
Ok? [y/n]
>y
Enter maximum number of iterations
>100000
Enter tolerated error value
>0.001
Iteration 413/100000 : error = 0.000997115
Total error within limit: 0.000997115 < 0.001
-----Calculated weights---------------------------------------------------------
L1-L2
        N0:   0.70818129646193329   0.28991160405044919   0.36845534285269632
        N1:   0.58265748857947874   0.92867341240701751   0.37830406670933309
L2-L3
        N0:   0.31950618187155677   0.92496142058125586   0.91754462174863538
        N1:   0.84652228351692893   0.92066530327170304   0.88987503253055944
        N2:   1.09533649074747652   0.85369947045951666   0.61092234974724191
L3-L4
        N0:  -1.23037948338282388   1.37654671507389459
        N1:  -1.50171192202838699   1.68943349636888884
        N2:  -1.24469424458893374   0.96181922732506664
```
