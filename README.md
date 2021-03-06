# Implementing the du Utility

## Description
This program provides the functionality of the du utility in Unix. `du` provides an approximation of the disk usage of a given directory.
For this implementation the disk usage was approximated using by using the block size and number of blocks allocated. To change this to The
apparent disk usage (similar to running du -b), an alternate size calculation has been commented out within the function getSize(), (lines 149 & 155).

## How to run
To compile, cd into the directory containing du and run:

`make du` or `make`

To remove old executables run:

`make clean`

## How to run
The du utility works with the following formats:

- `du [pathname]` or `du`

The pathname can be relative or absolute.
