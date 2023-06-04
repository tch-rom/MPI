---
## Results
```
❯ mpirun -n 3 ./array_sum
[+] rank 0      sum 561 start position 0        end position 33
[+] rank 1      sum 1650        start position 0        end position 33
[+] rank 2      sum 2839        start position 0        end position 34

Total sum: 5050
❯ mpirun -n 4 ./array_sum
[+] rank 0      sum 325 start position 0        end position 25
[+] rank 1      sum 950 start position 0        end position 25
[+] rank 2      sum 1575        start position 0        end position 25
[+] rank 3      sum 2200        start position 0        end position 25

Total sum: 5050
❯ mpirun -n 12 ./array_sum
[+] rank 2      sum 164 start position 0        end position 8
[+] rank 8      sum 548 start position 0        end position 8
[+] rank 5      sum 356 start position 0        end position 8
[+] rank 6      sum 420 start position 0        end position 8
[+] rank 1      sum 100 start position 0        end position 8
[+] rank 3      sum 228 start position 0        end position 8
[+] rank 4      sum 292 start position 0        end position 8
[+] rank 7      sum 484 start position 0        end position 8
[+] rank 0      sum 36  start position 0        end position 8
[+] rank 9      sum 612 start position 0        end position 8
[+] rank 10     sum 676 start position 0        end position 8
[+] rank 11     sum 1134        start position 0        end position 12

Total sum: 5050
❯ mpirun -n 2 ./array_sum
[+] rank 0      sum 1275        start position 0        end position 50
[+] rank 1      sum 3775        start position 0        end position 50

Total sum: 5050
```
