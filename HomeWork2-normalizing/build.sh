//!/bin/bash

echo "====Compiling main.cpp===="
g++ -Wall -Wextra -pedantic -Werror -v main.cpp -o main

echo "====Running compiled program====" 
./main

echo "====Cleaning up===="
rm main

echo "====Showing image===="
display *.ppm

echo "====All tasks completed!===="
