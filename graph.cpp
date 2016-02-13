#include "graph.h"

/**
 * @brief Инициализация ключевых узлов БДР
 * (0-терминальный узел, 1-терминальный узел, корень диаграммы)
 * @author Александр Митюнин
 */
Graph::Graph()
{
  QString str = QString("x%1").arg((QChar)0x2081); // x1
  root = new Node(str, nullptr, nullptr);
  low = new Node("0", nullptr, nullptr);
  high = new Node("1", nullptr, nullptr);
}

/**
 * @brief Удаление диаграммы
 * @todo Реализовать алгоритм удаления
 * (прим.: эффективность не в приоритете! нужен сам алгоритм!)
 */
Graph::~Graph()
{
}

/**
 * @brief Добавление узла с заданным адресом в БДР
 * @author Александр Митюнин
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
 * @author Александр Митюнин
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
 * @brief Построение БДР булевой функции
 * @author Александр Митюнин
 * @param values Вектор значений функции в форме машинного слова
 * @param variables Количество переменных функции
 *
 * @todo Написать функцию
 */
void Graph::buildBdd(int values, int variables)
{
}
