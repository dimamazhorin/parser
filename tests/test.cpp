// Copyright 2020 dima <dmitrymazhorinjr@gmail.com>

#include <gtest/gtest.h>

#include <json_parser_student.hpp>
#include <sstream>

TEST(table, print_table) {
  std::stringstream json_stream;
  json_stream << R"(
{
  "items": [
    {
      "name": "Ivanov Petr",
      "group": "1",
      "avg": "4.25",
      "debt": null
    },
    {
      "name": "Sidorov Ivan",
      "group": 31,
      "avg": 4,
      "debt": "C++"
    },
    {
      "name": "Pertov Nikita",
      "group": "IU8-31",
      "avg": 3.33,
      "debt": [
        "C++",
        "Linux",
        "Network"
      ]
    }
  ],
  "_meta": {
    "count": 3
  }
}
)";
  auto students = parse_json(json_stream);
  std::stringstream printed_table;
  printed_table << students;
  std::string ref_string =
      R"(| name                | group     | avg   | debt      |
|---------------------|-----------|-------|-----------|
| Ivanov Petr         | 1         | 4.25  | null      |
|---------------------|-----------|-------|-----------|
| Sidorov Ivan        | 31        | 4     | C++       |
|---------------------|-----------|-------|-----------|
| Pertov Nikita       | IU8-31    | 3.33  | 3    items|
|---------------------|-----------|-------|-----------|
)";
  EXPECT_EQ(ref_string, printed_table.str());
}

TEST(exception, ItemsIsNotArray) {
  std::stringstream json_stream;

  std::string exception_String;
  json_stream << R"(
  {
    "items":
    {
      "name": "Ivanov Petr",
          "group": "1",
          "avg": "4.25",
          "debt": null
    },
"_meta": {
"count": 3
}
  }
)";
  try {
    auto students = parse_json(json_stream);
  } catch (std::runtime_error &e) {
    exception_String = e.what();
  }
  EXPECT_EQ(exception_String, "Items most be array type");
}
TEST(exception, invalid_count) {
  std::stringstream json_stream;
  std::string exception_string;
  json_stream << R"(
  {
    "items": [
      {
        "name": "Ivanov Petr",
            "group": "1",
            "avg": "4.25",
            "debt": null
      },
      {
        "name": "Sidorov Ivan",
            "group": 31,
            "avg": 4,
            "debt": "C++"
      },
      {
        "name": "Pertov Nikita",
            "group": "IU8-31",
            "avg": 3.33,
            "debt": [
        "C++",
            "Linux",
            "Network"
        ]
      }
      ],
      "_meta": {
      "count" : 11
    }
  })";
  try {
    auto students = parse_json(json_stream);
  } catch (std::runtime_error &e) {
    exception_string = e.what();
  }
  EXPECT_EQ(exception_string, "meta: count and items size mismatch");
}
