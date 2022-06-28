

#include <iostream>
#include <queue>
#include <map>
#include <string.h>

using namespace std;
using std::string;

/* to map each character its huffman value*/
map<char, string> codes;

/* to store the frequency of character of the input data */
map<char, int> char_freq;

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
        codes[root->data] = str;
    }
    storeCodes(root->left, str + '0');
    storeCodes(root->right, str + '1');
}

void calcFreq(string str)
{
    for (int i = 0; i < str.size(); i++)
    {
        char_freq[str[i]]++;
    }
}

priority_queue<HuffmanNode *, vector<HuffmanNode *>, compare> pQueue;
void HuffmanCodes(int size)
{
    struct HuffmanNode *left, *right, *top;
    for (auto it : char_freq)
    {
        pQueue.push(new HuffmanNode(it.first, it.second));
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

    storeCodes(pQueue.top(), "");
}

string decode_huffman(HuffmanNode *root, string encoded_str)
{
    string result;
    struct HuffmanNode *temp = root;

    for (int i = 0; i < encoded_str.size(); i++)
    {
        if (encoded_str[i] == '0')
        {
            temp = temp->left;
        }
        else if (encoded_str[i] == '1')
        {
            temp = temp->right;
        }

        if ((temp->left == NULL) && (temp->right == NULL))
        {
            result += temp->data;
            temp = root;
        }
    }
    return result;
}

int main()
{
    string str = "abcdef abcde abcd abc aa!";
    string encodedString, decodedString;
    calcFreq(str);

    /*Huffman encoding*/
    HuffmanCodes(str.length());

    for (int i = 0; i < str.length(); i++)
    {
        encodedString += codes[str[i]];
    }

    cout << "Character Frequencies:\n";
    for (auto it : char_freq)
    {
        cout << it.first << ": " << it.second << endl;
    }

    cout << "********" << endl;
    cout << "Huffman encoding\n";

    for (auto it : codes)
    {
        cout << it.first << ": " << it.second << endl;
    }
    cout << "Encoding result: " << encodedString << endl;
    cout << endl;
    cout << "********" << endl;
    cout << "Huffman decoding:" << endl;
    decodedString = decode_huffman(pQueue.top(), encodedString);
    cout << decodedString << endl;
    return 0;
}