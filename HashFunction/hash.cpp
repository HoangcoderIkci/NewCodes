#include <iostream>
#include <vector>
#define M 11

#define H(k) (k % M)
#define H2(k) (1 + (k % (M - 1)))
#define P(k, idx) ((H(k) + idx * H2(k)) % M)
#define loop(i, bg, end) for (int i = bg; i < end; i++)
#define U32 unsigned int
#define U8 unsigned char
using namespace std;
// Структура для обычного узла в связном списке
struct Node
{
    int key;    // Ключ узла
    Node *next; // Указатель на следующий узел
    Node(int newKey = 0) : key(newKey), next(NULL) {}
};

// Структура для связного списка
struct list
{
    Node *root; // Корневой узел списка
    int length; // Длина списка
    list() : root(NULL), length(0) {}

    // Деструктор для освобождения памяти
    ~list()
    {
        Node *current = root;
        while (current != NULL)
        {
            Node *next = current->next;
            delete current;
            current = next;
        }
        root = NULL;
        length = 0;
    }

    // Добавление узла в начало списка
    void addHead(int newKey)
    {
        length++;
        if (root == NULL)
        {
            root = new Node(newKey);
        }
        else
        {
            Node *temp = new Node(newKey);
            temp->next = root;
            root = temp;
        }
    }

    // Вывод всех элементов списка
    void printList()
    {
        if (root == NULL)
            return;
        Node *temp = root;
        while (temp != NULL)
        {
            cout << temp->key << " ";
            temp = temp->next;
        }
        cout << "\n";
        // cout << endl;
    }
};
vector<int> arrayIndex;

list hashTableGlobal[M];
int current_length_hash = 0;
// Создание обычной хеш-таблицы
void insertToHashTableWithHashFunc2(int newKey)
{
    int k;
    int flag = 1;
    Node *ptr = NULL;
    if (current_length_hash >= M)
    {
        k = P(newKey, 0);
        loop(i, 0, M)
        {
            if (hashTableGlobal[i].length)
            {
                ptr = hashTableGlobal[i].root;
                while (ptr)
                {
                    if (ptr->key == newKey)
                    {
                        flag = 0;
                        break;
                    }
                    ptr = ptr->next;
                }
            }
            if (flag)
            {
                hashTableGlobal[k].addHead(newKey);
                ++current_length_hash;
            }
        }
    }
    else
    {
        int id = 0;
        int flag = 0;
        while (flag == 0)
        {
            flag = 1;
            k = P(newKey, id);
            // cout << "k: " << k << "   id: " << id << " " << endl;
            id++;
            for (auto x : arrayIndex)
            {
                if (x == k)
                {
                    flag = 0;
                    break;
                }
            }
        }
        arrayIndex.push_back(k);

        // cout << newKey << " " << k << endl;
        if (hashTableGlobal[k].length == 0)
        {
            hashTableGlobal[k].addHead(newKey);
        }
        else
            loop(i, 0, M)
            {
                if (hashTableGlobal[i].length == 0)
                {
                    hashTableGlobal[i].addHead(newKey);
                    current_length_hash++;
                    break;
                }
            }
    }
}

int main()
{
    U8 arrKey[] = {78, 100, 76, 12, 7, 30, 87, 14, 96, 79};
    int sz = sizeof(arrKey) / sizeof(arrKey[0]);
    loop(i, 0, sz)
    {
        insertToHashTableWithHashFunc2(arrKey[i]);
        cout << "new Table\n";
        for (int i = 0; i < M; i++)
        {
            if (hashTableGlobal[i].length != 0)
                cout << hashTableGlobal[i].root->key << " ";
            else
                cout << " empty ";
        }
        cout << endl;
    }
    return 0;
}
