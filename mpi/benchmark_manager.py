import os

path = "/Users/rfischer/Dropbox/Studium_Sem5/PC/Project/mpi/cmake-build-debug/mpi"


def benchmark(matrix, func, iteration_count, thread_count):
    cmd = "/usr/local/Cellar/open-mpi/1.8.4_1/bin/orterun -np %d %s big_matrix %d %d %d %d >> result.csv" % (thread_count, path, iteration_count, matrix[0], matrix[1], func)
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

try:
    os.remove('result.csv')
except:
    pass

count = 0
max_count = 319
for matrix in matrices:
    for iteration_count in iteration_counts:
        for func in stencil_functions:
            for thread_count in thread_counts:
                print "Benchmarking %d of %d" % (count, max_count)
                benchmark(
                    matrix=matrix,
                    iteration_count=iteration_count,
                    thread_count=thread_count,
                    func=func,
                )
                count = count + 1
