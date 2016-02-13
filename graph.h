#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

#include "node.h"

using namespace std;

/**
 * @brief Сокращенная упорядоченная бинарная диаграмма
 * решений,
 * представленная в виде графа
 * @author Александр Митюнин
 * @todo Создать класс Tree и сделать класс Graph private-наследником
 */
class Graph
{
public:
  Graph();
  ~Graph();
  void buildBdd(int values, int variables);

private:
  Node *root; // корень диаграммы
  Node *low;  // 0-терминальный узел
  Node *high; // 1-терминальный узел

  void addNode(Node *parent, Node *address, bool highConnected);
  void addNode(Node *parent, QString _data,
               Node *lowConnection, Node *highConnection,
               bool highConnected);
};

#endif // GRAPH_H
