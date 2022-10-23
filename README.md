# System-Calls
Revesing large files using system calls only

## 1. Reversing a large file(could be greater than RAM size)
- Compline and run this program by giving it an input file path
  ./a.out < input f ile path >
- The revesed input file will be created in a directory named "Outputs" it's name will be 1_< input f ile name >

## 2. Reversing part of a file
- Compline and run this program by giving it an input file path and starting and ending index
  ./a.out < input f ile path > start_idx end_idx
- In output everything will be reversed except the part between given two indices.
- The revesed input file will be created in a directory named "Outputs" it's name will be 2_< input f ile name >

## 3. Cheching if given files are reverse of each other
- Compline and run this program by giving it two input files and a directory name
  ./a.out < newf ile > < oldf ile > < directory >
- The progams checks if file contents are revesed in new file and checks permissions of both files and the directory and prints them.
