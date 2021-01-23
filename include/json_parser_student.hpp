// Copyright 2020 dima <dmitrymazhorinjr@gmail.com>

#ifndef INCLUDE_JSON_PARSER_STUDENT_HPP_
#define INCLUDE_JSON_PARSER_STUDENT_HPP_

#include <any>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

using nlohmann::json;

const int cname_column_width = 20;
const int cgroup_column_width = 10;
const int cavg_column_width = 6;
const int cdebt_column_width = 10;

struct student_t {
 private:
  std::string name;
  std::any group;
  std::any avg;
  std::any debt;
  static student_t from_json(const json& j);

  friend void print(const student_t& student, std::ostream& os);
  friend std::vector<student_t> parse_json(std::istream& json_stream);
  friend std::ostream& operator<<(std::ostream& os,
                                  const std::vector<student_t>& students);
};
std::ostream& operator<<(std::ostream& os,
                         const std::vector<student_t>& students);

void print(const student_t& student, std::ostream& os);
std::vector<student_t> parse_json(std::istream& json_stream);

#endif  // INCLUDE_JSON_PARSER_STUDENT_HPP_