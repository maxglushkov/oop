#pragma once
#include <string>

/// \brief Проверяет возможность использования определённого основания системы счисления
/// 	в функциях `StringToInt` и `IntToString`.
/// \param[in] radix Основание системы счисления для проверки
/// \return Возвращает `true`, если использование `radix` допустимо.
/// 	В противном случае, возвращает `false`.
/// \details Основанием системы счисления может быть любое целое число из отрезка [2; 36].
bool IsValidRadix(int radix);

/// \brief Преобразует строку в целое число.
/// \param[in] str Строка в формате `/-?[0-9A-Z]+/`
/// \param[in] radix Основание системы счисления
/// \param[out] wasError Принимает значение `true` в случае ошибки, `false` – в случае успеха
/// \return Возвращает преобразованное целое число, в случае ошибки – 0.
/// \details Существует ряд причин, по которым преобразование может завершиться с ошибкой:
/// 	1. `str` не соответствует регулярному выражению `/-?[0-9A-Z]+/`
/// 	2. `IsValidRadix(radix)` – ложно
/// 	3. `str` содержит символ, недопустимый в системе счисления с основанием `radix`
/// 	4. Произошло целочисленное переполнение
int StringToInt(const std::string & str, int radix, bool & wasError);

/// \brief Преобразует целое число в строку.
/// \param[in] n Целое число для преобразования
/// \param[in] radix Основание системы счисления
/// \param[out] wasError Принимает значение `true` в случае ошибки, `false` – в случае успеха
/// \return Возвращает отформатированную строку, в случае ошибки строка будет пустой.
/// \details Преобразование завершается с ошибкой, если `IsValidRadix(radix)` – ложно.
std::string IntToString(int n, int radix, bool & wasError);

/// \brief Печатает в поток ошибок сообщение о допустимых основаниях системы счисления.
void PrintRadixConstraints();
