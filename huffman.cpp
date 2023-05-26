#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <chrono>
using namespace std;

typedef std::chrono::high_resolution_clock Clock;

auto start_time = Clock::now();

struct MinHeapNode
{
    char d;
    unsigned frequency;
    MinHeapNode *lChild, *rChild;

    MinHeapNode(char d, unsigned frequency)

    {

        lChild = rChild = NULL;
        this->d = d;
        this->frequency = frequency;
    }
};

//function to compare
struct compare
{
    bool operator()(MinHeapNode *l, MinHeapNode *r)
    {
        return (l->frequency > r->frequency);
    }
};

void printCodes(struct MinHeapNode *root, string str)
{
    if (!root)
        return;

    if (root->d != '$')
        cout << root->d << ": " << str << "\n";

    printCodes(root->lChild, str + "0");
    printCodes(root->rChild, str + "1");
}

void HuffmanCodes(char d[], int frequency[], int size)
{
    struct MinHeapNode *lChild, *rChild, *top;

    priority_queue<MinHeapNode *, vector<MinHeapNode *>, compare> minHeap;

    for (int i = 0; i < size; ++i)
        minHeap.push(new MinHeapNode(d[i], frequency[i]));

    while (minHeap.size() != 1)
    {
        lChild = minHeap.top();
        minHeap.pop();

        rChild = minHeap.top();
        minHeap.pop();

        top = new MinHeapNode('$', lChild->frequency + rChild->frequency);

        top->lChild = lChild;
        top->rChild = rChild;

        minHeap.push(top);
    }
    printCodes(minHeap.top(), "");
}

int main()
{

  char arr[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
  int frequency[] = {1, 2, 3, 4, 5, 6, 7, 8};
  int size = sizeof(arr) / sizeof(arr[0]);
  HuffmanCodes(arr, frequency, size);
  
  auto end_time = Clock::now();
  std::cout << "Time difference for Worst Case: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end_time    - start_time).count() << " nanoseconds" << std::endl;
  
  return 0;
}
