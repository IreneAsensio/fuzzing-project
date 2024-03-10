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

The following command was tried to obtain the dependencies:

```bash
frama-c -pdg -pdg-dot graph -pdg-print -cpp-extra-args="-I ext_include" -main __sys_seti_1 -main __sys_seti_3 seti_1/seti_1.c seti_3/seti_3.c
```

We need to provide the entry points for both source files since there is not a test program and therefore, there is not a main. Frama-c 
looks for a main function to start the analysis. With the option -main we can indicate where to start.

Even if both source files are parsed, a .dot graph is generated only for __sys_seti_3 

Another option is to perform the analysis separately and then look for common global variables. For that case, we make:
```bash
    frama-c -pdg -pdg-dot graph -pdg-print -cpp-extra-args="-I ext_include" -main __sys_seti_1 seti_1/seti_1.c
```
```bash
    frama-c -pdg -pdg-dot graph -pdg-print -cpp-extra-args="-I ext_include" -main __sys_seti_3 seti_3/seti_3.c
```

and we obtain two independent .dot graphs