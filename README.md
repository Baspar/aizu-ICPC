<p align="center">
  <h2 align=center>Aizu ICPC</h2>

  <h4 align=center>Repo for http://judge.u-aizu.ac.jp</h4>
</p>

# Usage

## Add problems
To add a problem given its id:
```bash
./add.sh PROBLEM_ID
```

## Test problems
To test a problem on defined tests:
```bash
./test.sh Graph/Articulation Points/
```
or any other directory containing a main.cpp

## Provide new manual tests
To add new tests to a problem, just create:
 - `<TEST_NAME>.data` containing the STDIN inputs
 - `<TEST_NAME>.result` containing the expected answer

You'll then be able to test it with:
```bash
./test.sh FOLDER/PROBLEM
```
