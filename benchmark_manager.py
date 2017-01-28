import os

path = "/Users/rfischer/Dropbox/Studium_Sem5/PC/Project/cmake-build-debug/Project"

def benchmark(impl, matrix, func, iteration_count, thread_count):
    cmd = "%s %s %d %d %d %d %d >> result.csv" % (path, impl, matrix[0], matrix[1], iteration_count, thread_count, func)
    print "Cmd", cmd
    result = os.popen(cmd).read()
    #print "python: ", result


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

impls = (
    "sequential",
    "pthread",
    "openmp",
    "cilk"
)
try:
    os.remove('result.csv')
except:
    pass

count = 0
max_count = 319
for matrix in matrices:
    for iteration_count in iteration_counts:
        for func in stencil_functions:
            for impl in impls:
                if impl == "sequential" or impl == "openmp":
                    print "Benchmarking %d of %d" % (count, max_count)
                    benchmark(
                        impl=impl,
                        matrix=matrix,
                        iteration_count=iteration_count,
                        thread_count=1,
                        func=func,
                    )
                    count = count + 1
                else:
                    for thread_count in thread_counts:
                        print "Benchmarking %d of %d" % (count, max_count)
                        benchmark(
                            impl=impl,
                            matrix=matrix,
                            iteration_count=iteration_count,
                            thread_count=thread_count,
                            func=func,
                        )
                        count = count + 1
