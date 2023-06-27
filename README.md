# cpufp

This is a cpu tool for benchmarking the floating-points peak performance. Now it supports linux and x86-64 platform. It can automatically sense the local SIMD ISAs while compiling.

## How to use

build:

`./build.sh`

benchmark:

`./cpufp --thread_pool=[xxx]`

clean:

`./clean.sh`

xxx indicates that all the cores defined by xxx will be used for benchmarking(by affinity setting). For example, [0,3,5-8,13-15].

## Support x86-64 SIMD ISA

|ISA|Data Type|Description|
| ------------ | ------------ | ------------ |
|SSE|fp32/fp64|Before Sandy Bridge|
|AVX|fp32/fp64|From Sandy Bridge|
|FMA|fp32/fp64|From Haswell/Zen|
|AVX512f|fp32/fp64|From Skylake X/Zen4|
|AVX512_VNNI|int8/int16|From IceLake|
|AVX_VNNI|int8/int16|From Alder Lake|
|AMX|int8/bf16|From Sapphire Rapids|

## Some benchmark results

### Intel Sapphire Rapids w9-3475X

For single core:

<pre>
$ ./cpufp --thread_pool=[0]
Number Threads: 1
Thread Pool Binding: 0
--------------------------------------------------
| Instruction Set | Data Type | Peak Performance |
| AVX_VNNI        | INT8      | 650.72 GOPS      |
| AVX_VNNI        | INT16     | 326.56 GOPS      |
| AVX512_VNNI     | INT8      | 1104.1 GOPS      |
| AVX512_VNNI     | INT16     | 550.56 GOPS      |
| AVX512F         | FP32      | 331.01 GFLOPS    |
| AVX512F         | FP64      | 164.96 GFLOPS    |
| FMA             | FP32      | 165.54 GFLOPS    |
| FMA             | FP64      | 82.895 GFLOPS    |
| AVX             | FP32      | 123.92 GFLOPS    |
| AVX             | FP64      | 58.035 GFLOPS    |
| SSE             | FP32      | 62.009 GFLOPS    |
| SSE             | FP64      | 30.862 GFLOPS    |
| AMX             | INT8      | 663.56 GOPS      |
| AMX             | BF16      | 663.11 GFLOPS    |
--------------------------------------------------
</pre>

For multiple cores:

<pre>
$ ./cpufp --thread_pool=[0-35]
Number Threads: 36
Thread Pool Binding: 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35
--------------------------------------------------
| Instruction Set | Data Type | Peak Performance |
| AVX_VNNI        | INT8      | 17665 GOPS       |
| AVX_VNNI        | INT16     | 8718.8 GOPS      |
| AVX512_VNNI     | INT8      | 30483 GOPS       |
| AVX512_VNNI     | INT16     | 15163 GOPS       |
| AVX512F         | FP32      | 7412.2 GFLOPS    |
| AVX512F         | FP64      | 3617.4 GFLOPS    |
| FMA             | FP32      | 4470 GFLOPS      |
| FMA             | FP64      | 2232.8 GFLOPS    |
| AVX             | FP32      | 3108.5 GFLOPS    |
| AVX             | FP64      | 1571 GFLOPS      |
| SSE             | FP32      | 1724.4 GFLOPS    |
| SSE             | FP64      | 861.43 GFLOPS    |
| AMX             | INT8      | 15613 GOPS       |
| AMX             | BF16      | 14617 GFLOPS     |
--------------------------------------------------
</pre>

### Intel Alder Lake i7-1280p

For single Golden Cove(big) core:

<pre>
$ ./cpufp --thread_pool=[0]
Number Threads: 1
Thread Pool Binding: 0
--------------------------------------------------
| Instruction Set | Data Type | Peak Performance |
| AVX_VNNI        | INT8      | 590.31 GOPS      |
| AVX_VNNI        | INT16     | 295.06 GOPS      |
| FMA             | FP32      | 149.87 GFLOPS    |
| FMA             | FP64      | 74.931 GFLOPS    |
| AVX             | FP32      | 112.39 GFLOPS    |
| AVX             | FP64      | 56.203 GFLOPS    |
| SSE             | FP32      | 56.054 GFLOPS    |
| SSE             | FP64      | 28.001 GFLOPS    |
--------------------------------------------------
</pre>

For multiple big cores:

<pre>
$ ./cpufp --thread_pool=[0,2,4,6,8,10]
Number Threads: 6
Thread Pool Binding: 0 2 4 6 8 10
--------------------------------------------------
| Instruction Set | Data Type | Peak Performance |
| AVX_VNNI        | INT8      | 2636.8 GOPS      |
| AVX_VNNI        | INT16     | 1319.1 GOPS      |
| FMA             | FP32      | 670.05 GFLOPS    |
| FMA             | FP64      | 335 GFLOPS       |
| AVX             | FP32      | 502.4 GFLOPS     |
| AVX             | FP64      | 251.2 GFLOPS     |
| SSE             | FP32      | 250.42 GFLOPS    |
| SSE             | FP64      | 125.16 GFLOPS    |
--------------------------------------------------
</pre>

For single Gracemont(little) core:

<pre>
$ ./cpufp --thread_pool=[12]
Number Threads: 1
Thread Pool Binding: 12
--------------------------------------------------
| Instruction Set | Data Type | Peak Performance |
| AVX_VNNI        | INT8      | 114.89 GOPS      |
| AVX_VNNI        | INT16     | 57.445 GOPS      |
| FMA             | FP32      | 57.444 GFLOPS    |
| FMA             | FP64      | 28.723 GFLOPS    |
| AVX             | FP32      | 28.723 GFLOPS    |
| AVX             | FP64      | 14.362 GFLOPS    |
| SSE             | FP32      | 28.312 GFLOPS    |
| SSE             | FP64      | 14.361 GFLOPS    |
--------------------------------------------------
</pre>

For multiple little cores:

<pre>
$ ./cpufp --thread_pool=[12-19]
Number Threads: 8
Thread Pool Binding: 12 13 14 15 16 17 18 19
--------------------------------------------------
| Instruction Set | Data Type | Peak Performance |
| AVX_VNNI        | INT8      | 867.99 GOPS      |
| AVX_VNNI        | INT16     | 434 GOPS         |
| FMA             | FP32      | 434 GFLOPS       |
| FMA             | FP64      | 217 GFLOPS       |
| AVX             | FP32      | 217.01 GFLOPS    |
| AVX             | FP64      | 108.5 GFLOPS     |
| SSE             | FP32      | 216.39 GFLOPS    |
| SSE             | FP64      | 108.5 GFLOPS     |
--------------------------------------------------
</pre>

### AMD Ryzen9 6900HX(Zen3+)

For single core:

<pre>
$ ./cpufp --thread_pool=[0]
Number Threads: 1
Thread Pool Binding: 0
--------------------------------------------------
| Instruction Set | Data Type | Peak Performance |
| FMA             | FP32      | 156.18 GFLOPS    |
| FMA             | FP64      | 78.371 GFLOPS    |
| AVX             | FP32      | 156.55 GFLOPS    |
| AVX             | FP64      | 78.256 GFLOPS    |
| SSE             | FP32      | 78.219 GFLOPS    |
| SSE             | FP64      | 38.99 GFLOPS     |
--------------------------------------------------
</pre>

For multi-cores:

<pre>
$ ./cpufp --thread_pool=[0,2,4,6,8,10,12,14]
Number Threads: 8
Thread Pool Binding: 0 2 4 6 8 10 12 14
--------------------------------------------------
| Instruction Set | Data Type | Peak Performance |
| FMA             | FP32      | 1151.2 GFLOPS    |
| FMA             | FP64      | 569.89 GFLOPS    |
| AVX             | FP32      | 1088.7 GFLOPS    |
| AVX             | FP64      | 536.37 GFLOPS    |
| SSE             | FP32      | 541.35 GFLOPS    |
| SSE             | FP64      | 269.56 GFLOPS    |
--------------------------------------------------
</pre>

### Intel Celeron N5105(Jasper Lake)

For single core:

<pre>
$ ./cpufp --thread_pool=[0]
Number Threads: 1
Thread Pool Binding: 0
--------------------------------------------------
| Instruction Set | Data Type | Peak Performance |
| SSE             | FP32      | 23.102 GFLOPS    |
| SSE             | FP64      | 11.564 GFLOPS    |
--------------------------------------------------
</pre>

For multi_cores:

<pre>
$ ./cpufp --thread_pool=[0-3]
Number Threads: 4
Thread Pool Binding: 0 1 2 3
--------------------------------------------------
| Instruction Set | Data Type | Peak Performance |
| SSE             | FP32      | 89.327 GFLOPS    |
| SSE             | FP64      | 44.664 GFLOPS    |
--------------------------------------------------
</pre>

## TODO

The next version may support ARMv7 and ARMv8 architectures.

Welcome for bug reporting.
