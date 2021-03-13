#pragma once
#include <string_view>

/// \brief Декодирует HTML-сущность по её названию.
/// \param[in] entity HTML-сущность без `&` и `;`
/// \return Возвращает символьное представление HTML-сущности.
/// 	Если такого представления нет, возвращает `\0`.
char DecodeHtmlEntity(std::string_view const& entity);
