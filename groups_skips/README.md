---

## Results

**via groups**
```
❯ mpicc -o via_groups ./via_groups.c
❯ mpirun -n 3 ./via_groups
Total sum: 18405487053891215360.000000
❯ mpirun -n 5 ./via_groups
Total sum: 18405487053891217408.000000
❯ mpirun -n 7 ./via_groups
Total sum: 18405487053891219456.000000
❯ mpirun -n 13 ./via_groups
Total sum: 18405487053891217408.000000
❯ mpirun -n 14 ./via_groups
Total sum: 18405487053891217408.000000
```

**via skips**
```
❯ mpirun -np 3 ./via_skips
Total sum: 18405487053891217408.000000
❯ mpirun -np 7 ./via_skips
Total sum: 18405487053891215360.000000
❯ mpirun -np 10 ./via_skips
Total sum: 18405487053891215360.000000
❯ mpirun -np 22 ./via_skips
Total sum: 18405487053891217408.000000
```
