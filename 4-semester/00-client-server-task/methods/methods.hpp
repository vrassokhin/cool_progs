/**
 * @file methods/methods.hpp
 * @author Mikhail Lozhnikov, Ayzat Rizatdinov (dov4k1n)
 *
 * Объявления функций для серверной части алгоритмов. Эти функции должны
 * считать JSON, который прислал клиент, выполнить алгоритм и отправить клиенту
 * JSON с результатом работы алгоритма.
 */

#ifndef METHODS_METHODS_HPP_
#define METHODS_METHODS_HPP_

namespace graph {

/* Сюда нужно вставить объявление серверной части алгоритма. */

int TopologicalSortMethod(const nlohmann::json& input, nlohmann::json* output);

/* Конец вставки. */

}  // namespace graph

#endif  // METHODS_METHODS_HPP_
