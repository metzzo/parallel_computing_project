import pandas
import matplotlib.pyplot as plt
import numpy as np
import random

csv = pandas.read_csv("total_result.csv", header=None)
csv.columns = ("type", "row_count", "column_count", "thread_count", "iteration_count", "func", "time", "max_time", "min_time")

def draw_plot(csv, row_count, column_count, iteration_count, func):
    csv = csv.where(csv.row_count == row_count).dropna()
    csv = csv.where(csv.column_count == column_count).dropna()
    csv = csv.where(csv.iteration_count == iteration_count).dropna()
    csv = csv.where(csv.func == func).dropna()

    sequential_df = csv.where(csv.type == 'sequential') \
        .dropna() \
        .head(1)

    pthread_df = csv.where(csv.type == 'pthread')\
        .dropna() \
        .head(4)

    openmp_df = csv.where(csv.type == 'openmp')\
        .dropna() \
        .head(1)

    cilk_df = csv.where(csv.type == 'cilk')\
        .dropna() \
        .head(4)

    mpi_df = csv.where(csv.type == 'mpi') \
        .dropna()\
        .head(4)

    mpi_df.thread_count = pandas.Series([1, 8, 16, 34])
    #cilk_df.thread_count = pandas.Series([1, 8, 16, 34])
    #pthread_df.thread_count = pandas.Series([1, 8, 16, 34])

    sequential_df.set_index(np.array(["Sequential"]), inplace=True)
    pthread_df.set_index(np.array(["1 Thread", "8 Threads", "16 Threads", "34 Threads"]), inplace=True)
    openmp_df.set_index(np.array(["OpenMP"]), inplace=True)
    cilk_df.set_index(np.array(["1 Thread", "8 Threads", "16 Threads", "34 Threads"]), inplace=True)
    mpi_df.set_index(np.array(["1 Thread", "8 Threads", "16 Threads", "34 Threads"]), inplace=True)

    plot_df = pandas.concat([
        sequential_df.time,
        sequential_df.max_time,
        sequential_df.min_time,
        pthread_df.time,
        pthread_df.max_time,
        pthread_df.min_time,
        openmp_df.time,
        openmp_df.max_time,
        openmp_df.min_time,
        cilk_df.time,
        cilk_df.max_time,
        cilk_df.min_time,
        mpi_df.time,
        mpi_df.max_time,
        mpi_df.min_time,
    ], axis=1)

    plot_df.columns = ("Sequential - avg", "Sequential - max", "Sequential - min",
                       "pThread - avg", "pThread - max", "pThread - min",
                       "OpenMP", "OpenMP - max", "OpenMP - min",
                       "Cilk", "Cilk - max", "Cilk - min",
                       "MPI", "MPI - max", "MPI - min",)

    plot_df = plot_df.reindex(["Sequential", "OpenMP", "1 Thread", "8 Threads", "16 Threads", "34 Threads"])

    title = "%dx%d matrix, iteration count %d, stencil %s" % (
        row_count,
        column_count,
        iteration_count,
        "Simple" if func == 1 else "Complex"
    )

    fig = plot_df.plot.bar(
        grid=True,
        figsize=(30,10)
    )
    fig.set_title(title)
    fig.set_ylabel("Time in ms")
    fig.get_figure().savefig("figures/" + title,
                             bbox_inches='tight')
"""
        (1, 1),
    (10, 10),
    (100, 100),
    (500, 500),
    (1, 500),
    (500, 1),
    (2, 3),
    (491, 499),
    (10000, 1),
    (1, 10000),
    (1000, 1000),
    (5000, 5000),
    (100000, 1),
    (1, 100000),"""
matrices = (
    (491, 499),
    #(1, 1000000),
)

stencil_functions = (1, 2)
#stencil_functions = (2,)

iteration_counts = (1, 5)
#iteration_counts = (5,)

for matrix in matrices:
    for icount in iteration_counts:
        for f in stencil_functions:
            try:
                draw_plot(csv,
                          row_count=matrix[0],
                          column_count=matrix[1],
                          iteration_count=icount,
                          func=f)
            except:
                print("Exception")

#plt.show()