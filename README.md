# os-shell
Simple Shell written in C for OS Project.  
This project is part of the Operating Systems course offered to us ISI Kolkata in Spring Semester, 2024, taught to us by Prof. Mandar Mitra.

We used GNU `flex` as the lexer and GNU `bison` as the parser for this project.  
This helped us learn about the inner workings of the shell as well as basics of `flex` and `bison` which form a powerful lexer-parser pair.

## Instructions
```
sudo apt install flex bison
make
./shell
```

## Format of command
The basic format of a command is:
```
a1 | a2 | ... | an <inFile >outFile &>errFile
```
`inFile` would be provided as input to command `a1` and the final output will be redirected to `outFile`. Also, the error would be redirected to `errFile`.  
Also, `>>outFile` and `&>>errFile` are also supported for appending to output or error files.

## Requirements
`flex`, `bison`, `gcc`, `make`

## References
- https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf

## Team Members
- Aditya Dutta
- Shince K. Baby
- Tanmay Karmakar

We have named the shell `tash` (stands for **T**anmay, **A**ditya and **Sh**ince).
