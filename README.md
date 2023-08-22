# DART
DART: DAta stRuctures Tester

## Build
Build `DART` using the Makefile
```
$ make
```

## Run
### Arguments
Example run:
```
.\main.exe -i testdir -c "g++ -o sol solution.cpp" -t "g++ -o stu student.cpp" -a "1 2 3"
```
`-i`: the directory path that contains test input files<br>
* Assumes no subdirectories

`-c`: the compilation arguments for the solution<br>
`-t`: the compilation arguments for the student's code<br>
`-a`: the command-line arguments for the exe files
* The last three arguments (`-c`, `-t`, `-a`) must be wrapped in quotations

## Test Run
Test run using files for [nowic](https://github.com/idebtor/nowic), psets/pset9/
```
$ make test
```

## Grading Policy
Current: exact match, binary-decision (pass or fail)<br>
Considering more lenient grading policies
* Make test cases that test 1 specific functionality each
    * Grades by deducting points from failing test cases
