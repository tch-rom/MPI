---

##Results
```
❯ mpirun -n 7 ./matrix
        1       1       1       1
        0       2       2       2
        0       0       3       3
        0       0       0       4
[Rank 0] Received data: 1 1 
[Rank 1] Received data: 1 1 
[Rank 2] Received data: 0 2 
[Rank 4] Received data: 0 0 
[Rank 5] Received data: 3 3 
[Rank 3] Received data: 2 2 
[Rank 6] Received data: 0 0 0 4 
❯ mpirun -n 4 ./matrix
        1       1       1       1
        0       2       2       2
        0       0       3       3
        0       0       0       4
[Rank 0] Received data: 1 1 1 1 
[Rank 1] Received data: 0 2 2 2 
[Rank 2] Received data: 0 0 3 3 
[Rank 3] Received data: 0 0 0 4 
❯ mpicc -o matrix ./matrix.c
❯ mpirun -n 4 ./matrix
        7       49      73      58
        0       30      72      44
        0       0       78      23
        0       0       0       9
[Rank 0] Received data: 7 49 73 58 
[Rank 1] Received data: 0 30 72 44 
[Rank 2] Received data: 0 0 78 23 
[Rank 3] Received data: 0 0 0 9 
❯ mpirun -n 3 ./matrix
        7       49      73      58
        0       30      72      44
        0       0       78      23
        0       0       0       9
[Rank 0] Received data: 7 49 73 58 0 
[Rank 1] Received data: 30 72 44 0 0 
[Rank 2] Received data: 78 23 0 0 0 9 
❯ mpirun -n 2 ./matrix
        7       49      73      58
        0       30      72      44
        0       0       78      23
        0       0       0       9
[Rank 0] Received data: 7 49 73 58 0 30 72 44 
[Rank 1] Received data: 0 0 78 23 0 0 0 9 
❯ mpirun -n 1 ./matrix
        7       49      73      58
        0       30      72      44
        0       0       78      23
        0       0       0       9
[Rank 0] Received data: 7 49 73 58 0 30 72 44 0 0 78 23 0 0 0 9 
❯ mpirun -n 5 ./matrix
        7       49      73      58
        0       30      72      44
        0       0       78      23
        0       0       0       9
[Rank 0] Received data: 7 49 73 
[Rank 1] Received data: 58 0 30 
[Rank 2] Received data: 72 44 0 
[Rank 3] Received data: 0 78 23 
[Rank 4] Received data: 0 0 0 9 
❯ mpirun -n 7 ./matrix
        7       49      73      58
        0       30      72      44
        0       0       78      23
        0       0       0       9
[Rank 0] Received data: 7 49 
[Rank 1] Received data: 73 58 
[Rank 2] Received data: 0 30 
[Rank 4] Received data: 0 0 
[Rank 3] Received data: 72 44 
[Rank 5] Received data: 78 23 
[Rank 6] Received data: 0 0 0 9 
```
