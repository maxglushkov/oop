#pragma once
#include <iostream>

/// \brief Декодирует строку, заменяя HTML-сущности их символьными представлениями.
/// \param[in] html Исходная строка
/// \return Возвращает результат декодирования в виде новой строки.
/// \details Некорректные HTML-сущности копируются как есть.
std::string HtmlDecode(std::string const& html);

/// \brief Декодирует входной поток, заменяя HTML-сущности их символьными представлениями.
/// \param[in] input Входной поток
/// \param[in] output Выходной поток
/// \return Возвращает `true`, если был успешно достигнут конец входного потока.  
/// 	При попытке обработать строку длиннее `std::string::max_size` или ошибке ввода-вывода
/// 	возвращает `false`.
/// \details Потоки обрабатываются построчно функцией `HtmlDecode`.
bool HtmlDecodeStream(std::istream & input, std::ostream & output);
