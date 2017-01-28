import os
def benchmark(matrix, func, iteration_count, thread_count):
    os.system("/Users/rfischer/Dropbox/Studium_Sem5/PC/Project/cmake-build-debug/Project  %d %d %d %d %d >> result.csv" % (1, 1, iteration_count, thread_count, func))


matrices = (
    (1, 1),
    (10, 10),
    (100, 100),
    (500, 500),
    (1, 500),
    (500, 1),
    (2, 3),
    (491, 499)
)

stencil_functions = (1, 2)

iteration_counts = (1, 5)

thread_counts = (1, 8, 16, 48)

count = 0
max_count = 128
for matrix in matrices:
    for func in stencil_functions:
        for iteration_count in iteration_counts:
            for thread_count in thread_counts:
                print "Benchmarking %d of %d" % (count, max_count)
                benchmark(
                    matrix=matrix,
                    iteration_count=iteration_count,
                    thread_count=thread_count,
                    func=func,
                )
                count = count + 1
