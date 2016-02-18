#ifndef NODE_H
#define NODE_H

#include <QString>

/**
 * @brief Узел БДР
 * @author Александр Митюнин
 */
class Node
{
public:
  Node();
  Node(QString _data, Node *low, Node *high);
  ~Node();
  QString getData();
  void setData(QString _data);
  void setLowConnection(Node *node); //!< Задает адрес младшего потомка
  void setLowConnection(QString _data);
  void setHighConnection(Node *node);
  void setHighConnection(QString _data);
  Node* getHigh();
  Node* getLow();
  void delink(Node *address);

private:
  QString data;
  Node *lowConnection;  // Младший потомок
  Node *highConnection; // Старший потомок
};

#endif // NODE_H
