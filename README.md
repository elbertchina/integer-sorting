# integer-sorting
Parallel Algorithm
The Shared Memory Sample Sort algorithm is an implementation of Sample Sort for shared memory machines.
The idea behind Sample Sort is to find a set of p − 1 elements from the array, called splitters, which
partition the n input elements into p groups set0 ... setp−1. In particular, every element in seti
is smaller than
every element in seti+1. The partitioned sets are then sorted independently.
The input is an unsorted array A. The output is returned in array Result. Let p be the number of processors.
We will assume, without loss of generality, that N is divisible by p. An overview of the Shared Memory
Sample Sort algorithm is as follows:
Step 1. In parallel, a set S of s × p random elements from the original array A is collected, where p is the
number of TCUs available and s is called the oversampling ratio. Sort the array S, using an algorithm
that performs well for the size of S. Select a set of p − 1 evenly spaced elements from it into
S’: S’ = {S[s],S[2s],... ,S[(p − 1) × s]}
These elements are the splitters that are used below to partition the elements of A into p sets (or
partitions) seti
, 0 ≤ i < p. The sets are set0 = {A[i] | A[i] < S’[0]}, set1 = {A[i] | S’[0] ≤ A[i] < S’[1]},
... , setp−1 = {A[i] | S’[p − 2] ≤ A[i]}

Step 2. Consider the input array A divided into p subarrays,
B0 = A[0,... ,(N/p) − 1], B1 = A[N/p,..., 2(N/p) − 1] etc. The ith TCU iterates through subarray
Bi and for each element executes a binary search on the array of splitters S’, for a total of N/p binary
searches per TCU. The following quantities are computed:

• ci j - the number of elements from Bi that belong in partition setj

• partitionk - the partition (i.e. the seti) in which element A[k] belongs. Each element is tagged
with such an index.

• serialk - the number of elements in Bi
that belong in setpartitionk but are located before A[k] in Bi

For example, if B0 = [105,101,99,205,75,14] and we have S’ = [100,150,... ] as splitters, we will
have c0,0 =3, c0,1 =2 etc., partition0 =1, partition2 =0 etc. and serial0 =0, serial1 =1,serial5 =2.

Step 3. Compute prefix-sums psi, j for each column of the matrix C. For example, ps0, j
,ps1, j,... ,psp−1, j are the prefix-sums of c0, j,c1, j,. . . ,cp−1, j.
Also compute the sum of column i, which isstored in sumi
. Compute the prefix sums of the sum1,... ,sump
into global_ps0,..., p−1 and the total sum of sumi
in global_psp. This definition of globalps turns out
to be a programming convenience

Step 4. Each TCU i computes: for each element A[ j] in segment Bi
, i· N ≤ j < (i +1)N/p

posj = global_pspartitionj + psi,partitionj +serialj

Copy Result[posj] = A[j].

Step 5. TCU i executes a (serial) sorting algorithm on the elements of seti
, which are now stored in
Result[global_psi,... ,global_psi+1 − 1].

At the end of Step 5, the elements of A are stored in sorted order in Result.
