#ifndef FUNCTION_H
#define FUNCTION_H

#include <QString>
#include <vector>

using namespace std;

/**
 * @brief Логическая функция и вектор ее значений
 *
 * @warning Вектор значений функции представлен 32-битным машинным словом.
 * Из этого следует, что функция не может иметь более пяти переменных.
 *
 * @todo Добавить генерацию формулы функции
 */
class Function
{
public:
  Function();
  void calculateValues(); // вычисление вектора значений функции
  void setFormula(QString _formula); // задание формулы функции
  QString getFormula();
  QChar getNumberOfVariables();
  QString getValues();

private:
  QString formula; // запись функции
  QChar numberOfVariables; // число переменных
  int values; // вектор значений

  void findVariables(); // поиск переменных
  QString substitute(QString str, int value); // Подстановка в функцию значений
  int findPriorityPosition(QString str); // Вычисление глубины вложенности скобок
  void reduceSubstitution(QString &str, int position); // Сокращение подстановки
};

#endif // FUNCTION_H
