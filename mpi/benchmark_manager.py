import subprocess
import sys

#path = "/Users/rfischer/Dropbox/Studium_Sem5/PC/Project/mpi/cmake-build-debug/mpi"
#srun -p q_student -N 10 --ntasks-per-node=1 ./mpi big_matrix 20 1 50000
path = "srun -p q_student -N 10 --ntasks-per-node=1 ./mpi big_matrix 20 1 50000"

def benchmark(matrix, func, iteration_count, thread_count):
    #cmd = "/usr/local/Cellar/open-mpi/1.8.4_1/bin/orterun -np %d %s big_matrix %d %d %d %d >> result.csv" % (thread_count, path, iteration_count, matrix[0], matrix[1], func)
    return "srun -p q_student -N %d --output=result.%d.out  --ntasks-per-node=1 /home/students/e1425684/project/mpi/mpi big_matrix %d %d %d %d" % (thread_count, count, iteration_count, matrix[0], matrix[1], func)
    #pid = subprocess.Popen([sys.executable, cmd], stdout=subprocess.PIPE, stderr=subprocess.PIPE, stdin=subprocess.PIPE)
    #result = os.popen(cmd).read()
    #print "python: ", result


"""matrices = (
    (1, 1),
    (10, 10),
    (100, 100),
    (500, 500),
    (1, 500),
    (500, 1),
    (2, 3),
    (491, 499)
)"""
matrices = (
    #(1000, 1000),
    #(5000, 5000),
    #(100000,1),
    (1,1000000),
)

stencil_functions = (1, 2)

iteration_counts = (1, 5)

thread_counts = (1, 8, 16, 34,)

#try:
    #os.remove('result.csv')
#except:
#    pass

count = 1000
max_count = 127
cmd = ""
for matrix in matrices:
    for iteration_count in iteration_counts:
        for func in stencil_functions:
            for thread_count in thread_counts:
                #print "Benchmarking %d of %d" % (count, max_count)
                cmd = cmd + " & " +benchmark(
                    matrix=matrix,
                    iteration_count=iteration_count,
                    thread_count=thread_count,
                    func=func,
                )
                count = count + 1
print cmd
