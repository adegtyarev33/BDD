#include "function.h"

Function::Function()
{
}

/**
 * @brief Вычисление вектора значений логической функции
 *
 * Находится число переменных логической функции,
 * вычисляются значения функции при каждом наборе
 * значений переменных.
 */
void Function::calculateValues()
{
  int value = 0;
  values = 0;
  findVariables();
  for (int i = 0; i < (1 << (numberOfVariables.unicode() - 48)); ++i)
  {
    QString substitution = substitute(formula, i);
    int position = 0;
    while (substitution != "0" && substitution != "1")
    {
      // Вычисление глубины вложенности скобок
      position = findPriorityPosition(substitution);
      reduceSubstitution(substitution, position);
    }
    value = (substitution == "0") ? 0 : 1;
    values = values | ((value << i) >> 1);
  }
}

/**
 * @brief Поиск переменных функции в формуле
 */
void Function::findVariables()
{
  numberOfVariables = 0;
  for (int i = 0; i < formula.size(); ++i)
  {
    if (formula[i] >= (QChar)(0x2080) && formula[i] <= (QChar)(0x2089) && formula[i] > numberOfVariables)
      numberOfVariables = formula[i];
  }
  numberOfVariables = numberOfVariables.unicode() - 0x2080 + 48;
}

/**
 * @brief Подстановка значений набора переменных в функцию
 * @param str Формула функции
 * @param value Значение набора переменных
 * @return функцию вида str(value[1], ... value[n])
 * @todo Улучшить удобочитаемость функции добавлением вспомогательных переменных
 */
QString Function::substitute(QString str, int value)
{
  for (int i = 0; i < str.length(); ++i)
  {
    if (str[i] == 'x')
    {
      int sym = (int)(str[i+1].unicode());
      sym -= 0x2080;
      QString rep = ((value >> ((int)(numberOfVariables.unicode()) - 48 - sym)) & 0x1) ? "1" : "0";
      str.replace(i, 2, rep);
    }
    else
      if (str[i] == ' ')
        str.remove(i--, 1);
  }
  return str;
}

/**
 * @brief Поиск операции с наивысшим приоритетом
 * @param str
 * @return Позицию операции с наивысшим приоритетом
 */
int Function::findPriorityPosition(QString str)
{
  int position = 0;
  int maxDepth = 0;
  for (int i = 0, curDepth = 0; i < str.length(); ++i)
  {
    if (str[i] == '(')
    {
      if (++curDepth > maxDepth)
      {
        maxDepth = curDepth;
        position = i;
      }
    }
    if (str[i] == ')')
      --curDepth;
  }
  int symbol = 0;
  for (int i = position, maxPriority = 0; str[i] != ')' && i < str.length(); ++i)
  {
    symbol = (int)(str[i].unicode());
    switch(symbol)
    {
    case 0x21D4: // Equivalence
      if (maxPriority < 1)
      {
        maxPriority = 1;
        position = i;
      }
      break;

    case 0x21D2:  // Implication
      if (maxPriority < 2)
      {
        maxPriority = 2;
        position = i;
      }
      break;

    case 0x2295:  // XOR
      if (maxPriority < 3)
      {
        maxPriority = 3;
        position = i;
      }
      break;

    case (int)('|'):  // OR
      if (maxPriority < 4)
      {
        maxPriority = 4;
        position = i;
      }
      break;

    case (int)('&'):  // AND
      if (maxPriority < 5)
      {
        maxPriority = 5;
        position = i;
      }
      break;

    case 0x00AC:  // NOT
      if (maxPriority < 6)
      {
        maxPriority = 6;
        position = i;
      }
      break;
    }
  }
  return position;
}

/**
 * @brief Вычисление значения операции с наивысшим приоритетом
 * @param str Функция с подставленным набором значений
 * @param position Позиция операции с наивысшим приоритетом
 */
void Function::reduceSubstitution(QString &str, int position)
{
  QChar replacement = 0;
  int code = (int)(str[position].unicode());
  switch (code)
  {
  case (int)('('):  // Variable
    replacement = ((int)str[position + 1].unicode());
    str.replace(position, 3, replacement);
    break;

  case 0x21D4: // Equivalence
    replacement = (str[position - 1] == str[position + 1]) ? '1' : '0';
    if (position - 2 >= 0 && position + 2 < str.length())
    {
      if (str[position - 2] == '(' && str[position + 2] == ')')
        str.replace(position - 2, 5, replacement);
      else
        str.replace(position - 1, 3, replacement);
    }
    else
      str.replace(position - 1, 3, replacement);
    break;

  case 0x21D2:  // Implication
    replacement = (str[position - 1].unicode() == (int)('1') &&
                   str[position + 1].unicode() == (int)('0')) ? '0' : '1';
    if (position - 2 >= 0 && position + 2 < str.length())
    {
      if (str[position - 2] == '(' && str[position + 2] == ')')
        str.replace(position - 2, 5, replacement);
      else
        str.replace(position - 1, 3, replacement);
    }
    else
      str.replace(position - 1, 3, replacement);
    break;

  case 0x2295:  // XOR
    replacement = (str[position - 1] == str[position + 1]) ? '0' : '1';
    if (position - 2 >= 0 && position + 2 < str.length())
    {
      if (str[position - 2] == '(' && str[position + 2] == ')')
        str.replace(position - 2, 5, replacement);
      else
        str.replace(position - 1, 3, replacement);
    }
    else
      str.replace(position - 1, 3, replacement);
    break;

  case (int)('|'):  // OR
    replacement = (str[position - 1].unicode() == (int)('0') &&
                   str[position + 1].unicode() == (int)('0')) ? '0' : '1';
    if (position - 2 >= 0 && position + 2 < str.length())
    {
      if (str[position - 2] == '(' && str[position + 2] == ')')
        str.replace(position - 2, 5, replacement);
      else
        str.replace(position - 1, 3, replacement);
    }
    else
      str.replace(position - 1, 3, replacement);
    break;

  case (int)('&'):  // AND
    replacement = (str[position - 1].unicode() == (int)('1') &&
                   str[position + 1].unicode() == (int)('1')) ? '1' : '0';
    if (position - 2 >= 0 && position + 2 < str.length())
    {
      if (str[position - 2] == '(' && str[position + 2] == ')')
        str.replace(position - 2, 5, replacement);
      else
        str.replace(position - 1, 3, replacement);
    }
    else
      str.replace(position - 1, 3, replacement);
    break;

  case 0x00AC:  // NOT
    replacement = (str[position + 1].unicode() == (int)('1')) ? '0' : '1';
    if (position - 1 >= 0 && position < str.length())
    {
      if (str[position - 1] == '(' && str[position + 2] == ')')
        str.replace(position - 1, 4, replacement);
      else
        str.replace(position, 2, replacement);
    }
    else
      str.replace(position, 2, replacement);
    break;
  }
}

/**
 * @brief Изменить запись функции
 * @param _formula
 */
void Function::setFormula(QString _formula)
{
  formula = _formula;
}

/**
 * @return Строку, содержащую запись функции
 */
QString Function::getFormula()
{
  return formula;
}

/**
 * @return Количество переменных функции
 */
QChar Function::getNumberOfVariables()
{
  return numberOfVariables;
}

/**
 * @brief Вывод вектора значений
 * @return Строковую запись вектора значений
 */
QString Function::getValues()
{
  QString vect;
  QChar symbol;
  int limit = 1 << ((int)numberOfVariables.unicode() - 48);
  for (int i = 0; i < limit; ++i)
  {
    symbol = ( ((values >> (i - 1)) & 0x1) ) ? '1' : '0';
    vect.append(symbol);
  }
  return vect;
}
