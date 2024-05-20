/**
 * @file topological_sort.hpp
 * @author Ayzat Rizatdinov (dov4k1n)
 *
 * Реализация алгоритма топологической сортировки ориентированного
 * ациклического графа.
 */

#ifndef INCLUDE_TOPOLOGICAL_SORT_HPP_
#define INCLUDE_TOPOLOGICAL_SORT_HPP_

#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include "weighted_oriented_graph.hpp"

namespace graph {

/**
 * @brief Перечисление состояний вершины графа при обходе в глубину. 
 */
enum DFSVertexState {
  NotVisited,
  Processing,
  Processed
};

<template >
struct TSortOutput {
  std::vector<size_t> order;

}

/**
 * @brief Массив для печати состояния вершины графа при обходе в глубину
 * в читаемом виде.
 *
 * Пример использования: 
 * std::cout << DFSVertexState_txt[DFXVertexState.NotVisited]; // not visited
 */
const char* DFSVertexState_txt[] = {
  "not visited",
  "processing",
  "processed"
};

<template typename Weight>
void dfs(
  const OrientedGraph& graph,
  const size_t& vertex,
  std::unordered_map<size_t, DFSVertexState>& visited,
  std::vector<size_t>& result_order,
  bool& is_cyclic
);

/**
 * @brief Алгоритм топологической сортировки.
 *
 * @param graph На вход подаётся ссылка на объект типа graph::OrientedGraph,
 * описанный в файле @sa oriented_graph.hpp
 *
 * @return Алгоритм возвращает вектор вершин такой, что
 * для любого ребра (U, V) вершина U в этом векторе находится раньше 
 * вершины V, или пустой вектор, если в графе есть цикл.
 *
 * Функция инициализирует словарь посещённых вершин, алгоритмом 
 * обхода в глубину проверяет граф на ацикличность и кладёт их в 
 * итоговый вектор, начиная с листьев. В самом конце вектор разворачивается.
 */
<template typename Weight>
std::vector<size_t> TopologicalSort(OrientedGraph& graph) {
  std::unordered_map<size_t, DFSVertexState> visited;
  std::vector<size_t> result_order;
  bool is_cyclic = false;

  std::cout << std::endl << "in TopologicalSort graph.Vertices():" << std::endl;

  for (auto vertex : graph.Vertices()) {
    visited[vertex] = DFSVertexState::NotVisited;
    std::cout << vertex << " ";
  }
  std::cout << std::endl;
  
  for (auto vertex : graph.Vertices()) {
    if (is_cyclic) {
      std::cout << "is cyclic!" << std::endl;
      return std::vector<size_t>();
    }
    
    if (visited[vertex] == DFSVertexState::NotVisited) {
      dfs(graph, vertex, visited, result_order, is_cyclic);
    }
  }

  std::reverse(result_order.begin(), result_order.end());

  return result_order;
}

/**
 * @brief Алгоритм обхода в глубину для топологической сортировки.
 *
 * @param graph Объект типа graph::OrientedGraph, описанный в файле:
 * @sa oriented_graph.hpp
 * @param vertex Итерируемая вершина графа.
 * @param visited Словарь пройденных вершин.
 * @param result_order Вектор, куда будут добавляться вершины по мере сортировки.
 * @param is_cyclic Булевая переменная (по умолчанию false), в которую
 * записывается true, если по ходу работы выяснилось, что граф циклический.
 *
 * Функция отмечает вершину, в которую мы попали, и для всех исходящих из неё
 * рёбер применяет рекурсию, если их ещё не обработали. В конце добавляет
 * в итоговый вектор вершину.
 */
<template typename Weight>
void dfs(
  const OrientedGraph& graph,
  const size_t& vertex,
  std::unordered_map<size_t, DFSVertexState>& visited,
  std::vector<size_t>& result_order,
  bool& is_cyclic
) {
  visited[vertex] = DFSVertexState::Processing;

  std::cout << std::endl << "in dfs vertex: " << vertex << std::endl;

  for (auto destination : graph.Edges(vertex)) {
    std::cout << 
      "destination " << destination << 
      " is visited?: " << DFSVertexState_txt[visited[destination]] << 
      std::endl;

    if (visited[destination] == DFSVertexState::NotVisited)
      dfs(graph, destination, visited, result_order, is_cyclic);
    if (visited[destination] == DFSVertexState::Processing) {
      is_cyclic = true;
      return;
    }
  }

  visited[vertex] = DFSVertexState::Processed;
  std::cout << 
    vertex << 
    " is now " << 
    DFSVertexState_txt[visited[vertex]] << 
    std::endl;

  result_order.push_back(vertex);
}

}  // namespace graph

#endif  // INCLUDE_BRIDGE_SEARCH_HPP_