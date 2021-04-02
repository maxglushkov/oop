#pragma once
#include <string_view>

/// \brief Декодирует HTML-сущность по её названию.
/// \param[in] entity Срез строки, начинающийся с `&`
/// \param[out] decoded Cимвольное представление HTML-сущности
/// \return Возвращает количество декодированных символов.
/// \details Если символьного представления HTML-сущности нет, возвращает 0 и не изменяет `decoded`.
size_t DecodeHtmlEntity(std::string_view const& entity, char & decoded);
