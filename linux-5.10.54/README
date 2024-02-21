## How to manipulate frama-c:

### 1. Detecting explicit dependencies: 
Here we need to provide frama-c a test program where we make appear the dependency. In our case, it will be between the input parameter 
of seti_2.c and the output parameter of seti_1.c (being this parameter the one sent to seti_2.c).

This test program has been defined under the seti_2/ directory.
Then, the command needed to generate the dependency graph is: (from linux-5.10.54)

```bash
    frama-c -pdg -pdg-dot graph -pdg-print -cpp-extra-args="-I ext_include" seti_2/test_seti2.c
```
To obtain svg graph:
```bash
dot -Tsvg graph.main.dot > graph.main.svg
```

### 2. Detecting implicit dependencies: 