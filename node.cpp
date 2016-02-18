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

Node::~Node()
{
  if (lowConnection)
    delete lowConnection;
  if (highConnection)
    delete highConnection;
}

/**
 * @brief Задает адрес младшего потомка
 */
void Node::setLowConnection(Node *node)
{
  lowConnection = node;
}

/**
 * @brief Создает узел с заданной пометкой без связей и назначает
 * его младшим потомком
 */
void Node::setLowConnection(QString _data)
{
  lowConnection = new Node(_data, nullptr, nullptr);
}

/**
 * @brief Задает адрес старшего потомка
 */
void Node::setHighConnection(Node *node)
{
  highConnection = node;
}

/**
 * @brief Создает узел с заданной пометкой без связей и назначает
 * его старшим потомком
 */
void Node::setHighConnection(QString _data)
{
  highConnection = new Node(_data, nullptr, nullptr);
}

/**
 * @brief Возвращает указатель на старшего потомка
 */
Node* Node::getHigh()
{
  return highConnection;
}

/**
 * @brief Возвращает указатель на младшего потомка
 */
Node* Node::getLow()
{
  return lowConnection;
}

/**
 * @brief Возвращает строку, содержащую пометку узла
 */
QString Node::getData()
{
  return data;
}

/**
 * @brief Изменяет пометку узла на заданную
 */
void Node::setData(QString _data)
{
  data = _data;
}

/**
 * @brief Удаление связей с заданным узлом
 * @param address Указатель на узел, связи с которым должны быть удалены
 */
void Node::delink(Node *address)
{
  if (lowConnection == address)
    lowConnection = nullptr;
  if (highConnection == address)
    highConnection = nullptr;

  if (lowConnection)
    lowConnection->delink(address);
  if (highConnection)
    highConnection->delink(address);
}
