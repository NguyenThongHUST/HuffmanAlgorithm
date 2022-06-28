
#include <iostream>
#include <queue>
#include <map>
#include <string.h>

using namespace std;
using std::string;

/* to map each character its huffman value*/
map<char, string> codes;

// to store the frequency of character of the input data
map<char, int> freq;

struct HuffmanNode
{
    char data;
    unsigned freq;
    HuffmanNode *left, *right;

    HuffmanNode(char data, unsigned freq)
    {
        left = right = NULL;
        this->data = data;
        this->freq = freq;
    }
};

struct compare
{

    bool operator()(HuffmanNode *l, HuffmanNode *r)

    {
        return (l->freq > r->freq);
    }
};

void printCodes(HuffmanNode *root, string str)
{
    if (!root)
    {
        return;
    }
    if (root->data != '$')
    {
        cout << root->data << ": " << str << endl;
    }
    printCodes(root->left, str + '0');
    printCodes(root->right, str + '1');
}

void storeCodes(HuffmanNode *root, string str)
{
    if (!root)
    {
        return;
    }
    if (root->data != '$')
    {
        cout << root->data << ": " << str << endl;
    }
    storeCodes(root->left, str + '0');
    storeCodes(root->right, str + '1');
}

void HuffmanCodes(char data[], int freq[], int size)
{
    struct HuffmanNode *left, *right, *top;

    priority_queue<HuffmanNode *, vector<HuffmanNode *>, compare> pQueue;

    for (int i = 0; i < size; i++)
    {
        pQueue.push(new HuffmanNode(data[i], freq[i]));
    }

    while (pQueue.size() != 1)
    {
        left = pQueue.top();
        pQueue.pop();
        right = pQueue.top();
        pQueue.pop();

        top = new HuffmanNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        pQueue.push(top);
    }

    printCodes(pQueue.top(), "");
}

int main()
{
    char arr[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    int freq[] = {5, 9, 12, 13, 16, 45};

    int size = sizeof(arr) / sizeof(arr[0]);

    HuffmanCodes(arr, freq, size);

    return 0;
}