#pragma once
#include <iostream>

enum StreamReplaceError
{
	Success,
	IOError,
	TooLongLine
};

/// \brief Заменяет все вхождения подстроки в заданной строке на другую строку.
/// \param[in] original Исходная (заданная) строка
/// \param[in] searchStr Заменяемая подстрока
/// \param[in] replacementStr Заменяющая строка
/// \return Возвращает результат замены в виде новой строки.
std::string TextStringReplace(const std::string & original,
	const std::string & searchStr, const std::string & replacementStr);

/// \brief Заменяет все вхождения подстроки во входном потоке на другую строку
/// 	и записывает результат в выходной поток.
/// \param[in] input Входной поток
/// \param[in] output Выходной поток
/// \param[in] searchStr Заменяемая подстрока
/// \param[in] replacementStr Заменяющая строка
/// \return Возвращает `Success`, если был успешно достигнут конец входного потока.  
/// 	При ошибке ввода-вывода возвращает `IOError`.  
/// 	При попытке обработать строку длиннее `std::string::max_size` возвращает `TooLongLine`.
/// \details Потоки обрабатываются построчно. В связи с этим:
/// 	1. Обработка строк длиннее `std::string::max_size` приводит к ошибке.
/// 	2. Символы перевода строки не обрабатываются.
StreamReplaceError TextStreamReplace(std::istream & input, std::ostream & output,
	const std::string & searchStr, const std::string & replacementStr);
