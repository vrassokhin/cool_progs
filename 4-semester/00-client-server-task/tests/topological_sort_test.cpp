/**
 * @file topological_sort_test.cpp
 * @author Ayzat Rizatdinov (dov4k1n)
 *
 * Реализация набора тестов для алгоритма топологической сортировки.
 */

#include <vector>
#include <httplib.h>
#include <nlohmann/json.hpp>
#include "topological_sort.hpp"
#include "oriented_graph.hpp"
#include "test_core.hpp"
#include "test.hpp"

static void SimpleTest(httplib::Client* client);
static void EmptyTest(httplib::Client* client);
static void LinearTest(httplib::Client* client);
static void ReverseLinearTest(httplib::Client* client);
static void CyclicTest(httplib::Client* client);
// static void RandomTest(httplib::Client* cli);

void TestTopologicalSort(httplib::Client* client) {
  TestSuite suite("TestTopologicalSort");

  RUN_TEST_REMOTE(suite, client, SimpleTest);
  RUN_TEST_REMOTE(suite, client, EmptyTest);
  RUN_TEST_REMOTE(suite, client, LinearTest);
  RUN_TEST_REMOTE(suite, client, ReverseLinearTest);
  RUN_TEST_REMOTE(suite, client, CyclicTest);
  // RUN_TEST_REMOTE(suite, client, RandomTest); нельзя сделать, так как
  // результат топологической сортировки неоднозначный.
}

/** 
 * @brief Простой статический тест.
 *
 * @param cli Указатель на HTTP клиент.
 */
static void SimpleTest(httplib::Client* client) {
  /*
    Библиотека nlohmann json позволяет преобразовать
    строку в объект nlohmann::json не только при помощи
    функции nlohmann::json::parse(), но и при помощи
    специального литерала _json. Если его поставить после строки
    в кавычках, то она конвертируется в json объект.
    
    R"(
    )" Так записывается строка, содержащая символы перевода строки
    в C++. Всё, что между скобками это символы строки. Переводы строк
    можно ставить просто как перевод строки в текстовом редактора
    (а не через \n).     
  */
  nlohmann::json input = R"(
{
  "id": 1,
  "vertices": [ 1, 2, 3 ],
  "edges": [ 
    {
      "start": 2,
      "end":  1
    },
    {
      "start": 1,
      "end": 3
    }
  ]
}
)"_json;

  /* Делаем POST запрос по адресу нашего метода на сервере.
  Метод dump() используется для преобразования JSON обратно в строку.
  (Можно было сразу строку передать). При передаче JSON данных
  необходимо поставить тип MIME "application/json".
  */
  httplib::Result result = client->Post(
    "/TopologicalSort",
    input.dump(),
    "application/json"
  );

  /* Используем метод parse() для преобразования строки ответа сервера
  (result->body) в объект JSON. */
  nlohmann::json output = nlohmann::json::parse(result->body);

  /* Проверка результатов сортировки. */
  REQUIRE_EQUAL(1, output["id"]);

  REQUIRE_EQUAL(output["result"][0], 2);
  REQUIRE_EQUAL(output["result"][1], 1);
  REQUIRE_EQUAL(output["result"][2], 3);
}

/**
 * @brief Тест для сортировки пустого графа.
 *
 * @param cli Указатель на HTTP клиент.
 */
static void EmptyTest(httplib::Client* client) {
  nlohmann::json input = R"(
{
  "id": 2,
  "vertices": [ ],
  "edges": [ ]
}
)"_json;

  httplib::Result result = client->Post(
    "/TopologicalSort",
    input.dump(),
    "application/json"
  );

  nlohmann::json output = nlohmann::json::parse(result->body);
  std::vector<size_t> empty_vector;

  REQUIRE_EQUAL(2, output["id"]);

  REQUIRE_EQUAL(output["result"], empty_vector);
}

/**
 * @brief Тест для сортировки линейного графа.
 *
 * @param cli Указатель на HTTP клиент.
 */
static void LinearTest(httplib::Client* client) {
  nlohmann::json input = R"(
{
  "id": 3,
  "vertices": [ 1, 2, 3, 4 ],
  "edges": [ 
    {
      "start": 1,
      "end": 2
    },
    {
      "start": 2,
      "end": 3
    },
    {
      "start": 3,
      "end": 4
    } 
  ]
}
)"_json;

  httplib::Result result = client->Post(
    "/TopologicalSort",
    input.dump(),
    "application/json"
  );

  nlohmann::json output = nlohmann::json::parse(result->body);
  REQUIRE_EQUAL(3, output["id"]);

  REQUIRE_EQUAL(output["result"][0], 1);
  REQUIRE_EQUAL(output["result"][1], 2);
  REQUIRE_EQUAL(output["result"][2], 3);
  REQUIRE_EQUAL(output["result"][3], 4);
}

/**
 * @brief Тест для сортировки обратного линейного графа.
 *
 * @param cli Указатель на HTTP клиент.
 */
static void ReverseLinearTest(httplib::Client* client)  {
  nlohmann::json input = R"(
{
  "id": 4,
  "vertices": [ 1, 2, 3, 4 ],
  "edges": [ 
    {
      "start": 4,
      "end": 3
    },
    {
      "start": 3,
      "end": 2
    },
    {
      "start": 2,
      "end": 1
    }
  ]
}
)"_json;

  httplib::Result result = client->Post(
    "/TopologicalSort",
    input.dump(),
    "application/json"
  );

  nlohmann::json output = nlohmann::json::parse(result->body);
  REQUIRE_EQUAL(4, output["id"]);

  REQUIRE_EQUAL(output["result"][0], 4);
  REQUIRE_EQUAL(output["result"][1], 3);
  REQUIRE_EQUAL(output["result"][2], 2);
  REQUIRE_EQUAL(output["result"][3], 1);
}

/**
 * @brief Тест для сортировки графа с циклом.
 *
 * @param cli Указатель на HTTP клиент.
 */
static void CyclicTest(httplib::Client* client) {
  nlohmann::json input = R"(
{
  "id": 5,
  "vertices": [ 1, 2, 3 ],
  "edges": [ 
    {
      "start": 1,
      "end": 2
    },
    {
      "start": 2,
      "end": 3
    }, 
    {
      "start": 3,
      "end": 1
    } 
  ]
}
)"_json;

  httplib::Result result = client->Post(
    "/TopologicalSort",
    input.dump(),
    "application/json"
  );

  nlohmann::json output = nlohmann::json::parse(result->body);
  std::vector<size_t> empty_vector;

  REQUIRE_EQUAL(5, output["id"]);

  REQUIRE_EQUAL(output["result"], empty_vector);
}