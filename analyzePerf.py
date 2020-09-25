import numpy as np
import matplotlib.pyplot as plt


def readCSV(fileName):
    with open(fileName, 'r') as file:
        allData = [line.strip('\n').split(',') for line in file]
    allData = np.array(allData)
    return allData


def main():
    contents = readCSV("PerfTest.csv")
    numIter = contents[1:, 0]
    strcat = contents[1:, 1].astype(float)
    modstrcat = contents[1:, 2].astype(float)
    fig, ax = plt.subplots(figsize=(10, 6))
    ax.set_xlabel('Number Concatenations')
    ax.set_ylabel('Time (seconds)')
    ax.set_title('Performance of String Concatenation')
    ax.scatter(numIter, strcat, c="orange", marker="D", label="strcat")
    ax.scatter(numIter, modstrcat, c="blue", label="modstrcat")
    ax.legend()
    plt.xticks(numIter[1::2], rotation=30)
    ax.set_yscale('log', basey=2)
    plt.show()
    print()


main()
