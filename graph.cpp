#include "graph.h"

/**
 * @brief Инициализация ключевых узлов БДР
 * (0-терминальный узел, 1-терминальный узел, корень диаграммы)
 */
Graph::Graph()
{
  root = new Node();
  low = new Node("0", nullptr, nullptr);
  high = new Node("1", nullptr, nullptr);
}

/**
 * @brief Удаление диаграммы
 */
Graph::~Graph()
{
  root->delink(low);
  root->delink(high);
  delete low;
  delete high;
  delete root;
}

/**
 * @brief Добавление узла с заданным адресом в БДР
 * @param parent "Родитель" добавляемого узла
 * @param address Указатель на узел
 * @param highConnected true, если узел является старшим потомком
 */
void Graph::addNode(Node *parent, Node *address, bool highConnected)
{
  if (highConnected)
  {
    parent->setHighConnection(address);
  }
  else
    parent->setLowConnection(address);
}

/**
 * @brief Создание узла и добавление его в БДР
 * @param parent "Родитель" добавляемого узла
 * @param _data Пометка узла
 * @param lowConnection Младший потомок
 * @param highConnection Старший потомок
 * @param highConnected true, если узел является старшим потомком
 */
void Graph::addNode(Node *parent, QString _data, Node *lowConnection,
                    Node *highConnection, bool highConnected)
{
  Node *child = new Node(_data, lowConnection, highConnection);
  addNode(parent, child, highConnected);
}

/**
 * @brief Построение БДР булевой функции по ее вектору значений
 * @param values Вектор значений функции в форме машинного слова
 * @param variables Число переменных
 * @param node Корень диаграммы
 * @param number Индекс текущей переменной
 */
void Graph::buildBdd(int values, int variables, Node *node, int number)
{
  int mask  = UINT32_MAX ^ (UINT32_MAX << (1 << (variables - 1)));

  if ((values & mask) == 0)
    node->setHighConnection(low);
  else
  {
    if ((values & mask) == mask)
      node->setHighConnection(high);
    else
    {
      Node *newNode = new Node();
      node->setHighConnection(newNode);
      buildBdd((values & mask), variables - 1, newNode, number + 1);
    }
  }

  mask = mask << (1 << (variables - 1));
  if ((values & mask) == 0)
    node->setLowConnection(low);
  else
  {
    if ((values & mask) == mask)
      node->setLowConnection(high);
    else
    {
      Node *newNode = new Node();
      node->setLowConnection(newNode);
      int shift = 1 << (variables - 1);
      buildBdd((values & mask) >> shift, variables - 1, newNode, number + 1);
    }
  }

  QString _data = QString("x%1").arg((QChar)(0x2080 + number));
  node->setData(_data);
}
