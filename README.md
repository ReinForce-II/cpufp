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
| AVX_VNNI        | INT8      | 627.56 GOPS      |
| AVX_VNNI        | INT16     | 313.99 GOPS      |
| AVX512_VNNI     | INT8      | 1063.2 GOPS      |
| AVX512_VNNI     | INT16     | 531.14 GOPS      |
| AVX512F         | FP32      | 317.87 GFLOPS    |
| AVX512F         | FP64      | 158.92 GFLOPS    |
| FMA             | FP32      | 158.94 GFLOPS    |
| FMA             | FP64      | 79.602 GFLOPS    |
| AVX             | FP32      | 119.48 GFLOPS    |
| AVX             | FP64      | 59.628 GFLOPS    |
| SSE             | FP32      | 59.405 GFLOPS    |
| SSE             | FP64      | 29.358 GFLOPS    |
| AMX             | INT8      | 10077 GOPS       |
| AMX             | BF16      | 5082 GFLOPS      |
--------------------------------------------------
</pre>

For multiple cores:

<pre>
$ ./cpufp --thread_pool=[2-35]
Number Threads: 34
Thread Pool Binding: 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35
---------------------------------------------------
| Instruction Set | Data Type | Peak Performance  |
| AVX_VNNI        | INT8      | 19069 GOPS        |
| AVX_VNNI        | INT16     | 9468.3 GOPS       |
| AVX512_VNNI     | INT8      | 31077 GOPS        |
| AVX512_VNNI     | INT16     | 15454 GOPS        |
| AVX512F         | FP32      | 9137 GFLOPS       |
| AVX512F         | FP64      | 4555.8 GFLOPS     |
| FMA             | FP32      | 4806.3 GFLOPS     |
| FMA             | FP64      | 2396.9 GFLOPS     |
| AVX             | FP32      | 3578.5 GFLOPS     |
| AVX             | FP64      | 1764.7 GFLOPS     |
| SSE             | FP32      | 1762.9 GFLOPS     |
| SSE             | FP64      | 860.52 GFLOPS     |
| AMX             | INT8      | 2.9107e+05 GOPS   |
| AMX             | BF16      | 1.4245e+05 GFLOPS |
---------------------------------------------------
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
