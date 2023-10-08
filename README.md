# Building

```
$ mkdir build
$ cd build
$ cmake /path/to/source/dir -GNinja
```

## Benchmarks
```
$ ninja square_equation
$ ./benchmarks/square_equation
```

## Tests

Please, be sure you have installed GoogleTest library.

```
$ ninja mipt_vm_unit_tests
$ ./tests/mipt_vm_unit_tests
```