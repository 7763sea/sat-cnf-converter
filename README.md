# sat-cnf-converter
A small utility for conversion of Boolean formulae from DIMACS SAT to DIMACS CNF format. The program is a part of MSc thesis "Contributions to the Solver of Boolean Problems".

# Features
* MIT-licensed
* Written in C++ language
* Uses only standard C++ library. No additional frameworks are required
* Compilation is tested for Windows and Linux systems
* The result of conversion might be processed by such SAT solvers like UBCSAT, Sat4j, sharpSAT, RELSAT, RSat, etc

# Building
The project is written using Qt Creator http://qt-project.org/ .
Open a file "project.pro" in Qt Creator and build the project using top menu ("Build" - "Build Project") or pressing \<Ctrl\> + \<B\>.

# Running the program
Assume that the name of the program is "sat_to_cnf.exe" and the name of input file is "sample.sat".
```
sat_to_cnf.exe sample.sat
```
If conversion was successful, the program will produce a file "sample.cnf"

# Sample input
```
c Sample SAT format
c
p sat 4
(*(+(1 3 -4)
   +(4)
   +(2 3)))
```

# Sample output
```
c Generated at: 27.09.2014 15:21:2
c Original comments: 
c Some SAT file
c 
p cnf 4 3
1 3 -4 0
4 0
-3 0
```
