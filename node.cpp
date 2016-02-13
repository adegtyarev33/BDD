#include "node.h"

/**
 * @brief Создает узел без пометки и без связей
 */
Node::Node()
{
  setLowConnection(nullptr);
  setHighConnection(nullptr);
}

/**
 * @brief Создает узел с заданными пометкой и связями
 * @param _data Пометка узла
 * @param low Указатель на младшего потомка
 * @param high Указатель на старшего потомка
 */
Node::Node(QString _data, Node *low, Node *high)
{
  data = _data;
  setLowConnection(low);
  setHighConnection(high);
}

/**
 * @brief Задает адрес младшего потомка
 * @author Александр Митюнин
 */
void Node::setLowConnection(Node *node)
{
  lowConnection = node;
}

/**
 * @brief Создает узел с заданной пометкой без связей и назначает
 * его младшим потомком
 * @author Александр Митюнин
 */
void Node::setLowConnection(QString _data)
{
  lowConnection = new Node(_data, nullptr, nullptr);
}

/**
 * @brief Задает адрес старшего потомка
 * @author Александр Митюнин
 */
void Node::setHighConnection(Node *node)
{
  highConnection = node;
}

/**
 * @brief Создает узел с заданной пометкой без связей и назначает
 * его старшим потомком
 * @author Александр Митюнин
 */
void Node::setHighConnection(QString _data)
{
  highConnection = new Node(_data, nullptr, nullptr);
}

/**
 * @brief Возвращает указатель на старшего потомка
 * @author Александр Митюнин
 */
Node* Node::getHigh()
{
  return highConnection;
}

/**
 * @brief Возвращает указатель на младшего потомка
 * @author Александр Митюнин
 */
Node* Node::getLow()
{
  return lowConnection;
}

/**
 * @brief Возвращает строку, содержащую пометку узла
 * @author Александр Митюнин
 */
QString Node::getData()
{
  return data;
}

/**
 * @brief Изменяет пометку узла на заданную
 * @author Александр Митюнин
 */
void Node::setData(QString _data)
{
  data = _data;
}
