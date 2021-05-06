/**
 * @file help.h
 * @author Mariana Rodrigues, Matilde Bravo e Pedro Alves
 * @date 4 Maio 2021
 * @brief This Module is responsible to manipulated all information.
 */

#ifndef __HELP_H_
#define __HELP_H_

#define CMD_SHOW_HELP                                                          \
  BOLD FG_CYAN "-> " FG_YELLOW "show" RESET_ALL "(" FG_RED "table" RESET_ALL   \
               ": " FG_CYAN BOLD "TABLE" RESET_ALL ")\n"                       \
               "Returns: void\n\n"                                             \
               "Presents a table on the screen with a pager\n"                 \
               "Keys:\n"                                                       \
               "Arrow Up/Arrow Down: Go one line up and down, respectively\n"  \
               "Arrow Left/Arrow Right: Go one page backward and foward, "     \
               "respectively\n"                                                \
               "q: quit pager\n"

#define CMD_LOAD_SGR_HELP                                                      \
  BOLD FG_CYAN                                                                 \
      "-> " FG_YELLOW "load_sgr" RESET_ALL "([" FG_RED "users" RESET_ALL       \
      ": " FG_CYAN BOLD "String" RESET_ALL ", " FG_RED "businesses" RESET_ALL  \
      ": " FG_CYAN BOLD "String" RESET_ALL ", " FG_RED "reviews" RESET_ALL     \
      ": " FG_CYAN BOLD "String" RESET_ALL "])\n"                              \
      "Returns: " FG_CYAN BOLD "SGR" RESET_ALL "\n\n"                          \
      "Creates an " FG_CYAN BOLD "SGR" RESET_ALL                               \
      " structure which contains all the information retrieved "               \
      "from the input files(users,businesses and reviews), organized in a "    \
      "way so "                                                                \
      "as to facilitate the 9 possible queries.\n\n"                           \
      "When called with three valid paths to csv files, the first one will "   \
      "be "                                                                    \
      "used as source for user entries, second one for business entries and  " \
      "third one for review entries. Each line will be parsed and stored in "  \
      "the "                                                                   \
      "appropriate structure inside " FG_CYAN BOLD "SGR" RESET_ALL             \
      ".\n\n When called without arguments it uses the files specified in the" \
      "config or the default files, in case no config is provided.\n "

#define CMD_BUSINESSES_STARTED_BY_LETTER_HELP                                  \
  "-> " FG_YELLOW "businesses_started_by_letter" RESET_ALL "(" FG_RED          \
  "sgr" RESET_ALL ": " FG_CYAN BOLD "SGR" RESET_ALL ", " FG_RED                \
  "letter" RESET_ALL ": " FG_CYAN BOLD "String" RESET_ALL ")\n"                \
  "Returns: " FG_CYAN BOLD "TABLE" RESET_ALL "\n\n"                            \
  "Creates a table with the name of the businesses, present in the "           \
  "provided " FG_CYAN BOLD "SGR" RESET_ALL                                     \
  ",  whose names start with a given letter(case insensitive).\n"

#define CMD_BUSINESS_INFO_HELP                                                 \
  "-> " FG_YELLOW "business_info" RESET_ALL "(" FG_RED "sgr" RESET_ALL         \
  ": " FG_CYAN BOLD "SGR" RESET_ALL ", " FG_RED "business_id" RESET_ALL        \
  ": " FG_CYAN BOLD "String" RESET_ALL ")\n"                                   \
  "Returns: " FG_CYAN BOLD "TABLE" RESET_ALL "\n\n"                            \
  "Creates a table with information about a business, given its business id. " \
  "This information consists of: name, city, state, average number of stars "  \
  "and total number of reviews.\n"

#define CMD_BUSINESSES_REVIEWED_HELP                                           \
  "-> " FG_YELLOW "businesses_reviewed" RESET_ALL "(" FG_RED "sgr" RESET_ALL   \
  ": " FG_CYAN BOLD "SGR" RESET_ALL ", " FG_RED "user_id" RESET_ALL            \
  ": " FG_CYAN BOLD "String" RESET_ALL ")\n"                                   \
  "Returns: " FG_CYAN BOLD "TABLE" RESET_ALL "\n\n"                            \
  "Creates a table with information about all the businesses a user has "      \
  "reviewed, given its user id. This information consists of business id and " \
  "name.\n"

#define CMD_BUSINESSES_WITH_STARS_AND_CITY_HELP                                \
  "-> " FG_YELLOW "businesses_with_stars_and_city" RESET_ALL "(" FG_RED        \
  "sgr" RESET_ALL ": " FG_CYAN BOLD "SGR" RESET_ALL ", " FG_RED                \
  "stars" RESET_ALL ": " FG_CYAN BOLD "float" RESET_ALL ", " FG_RED            \
  "city" RESET_ALL ": " FG_CYAN BOLD "String" RESET_ALL ")\n"                  \
  "Returns: " FG_CYAN BOLD "TABLE" RESET_ALL "\n\n"                            \
  "Creates  a table with information about all the businesses in that city "   \
  "which have an average number of stars above the provided one.\n"

#define CMD_FROM_CSV_HELP                                                      \
  "-> " FG_YELLOW "from_csv" RESET_ALL "(" FG_RED "filename" RESET_ALL         \
  ": " FG_CYAN BOLD "String" RESET_ALL ", " FG_RED "delim" RESET_ALL           \
  ": " FG_CYAN BOLD "String" RESET_ALL ")\n"                                   \
  "Returns: " FG_CYAN BOLD "TABLE" RESET_ALL "\n\n"                            \
  "Creates a table with all the content from the provided CSV file, which "    \
  "must contain a header, separated by the given delimiter.The number of "     \
  "columns of the table will be the same as the fields in the header."

#define CMD_TOP_BUSINESSES_BY_CITY_HELP                                        \
  "-> " FG_YELLOW "top_businesses_by_city" RESET_ALL "(" FG_RED                \
  "sgr" RESET_ALL ": " FG_CYAN BOLD "SGR" RESET_ALL ", " FG_RED                \
  "top" RESET_ALL ": " FG_CYAN BOLD "Number" RESET_ALL ")\n"                   \
  "Returns: " FG_CYAN BOLD "TABLE" RESET_ALL "\n\n"                            \
  "Creates a table with information about the n businesses with the most "     \
  "stars in all city.\n"

#define CMD_INTERNATIONAL_USERS_HELP                                           \
  "-> " FG_YELLOW "international_users" RESET_ALL "(" FG_RED "sgr" RESET_ALL   \
  ": " FG_CYAN BOLD "SGR" RESET_ALL RESET_ALL ")\n"                            \
  "Returns: " FG_CYAN BOLD "TABLE" RESET_ALL "\n\n"                            \
  "Creates a table with information with all the users that have visited "     \
  "more than one state.\n"

#define CMD_TO_CSV_HELP                                                        \
  "-> " FG_YELLOW "to_csv" RESET_ALL "(" FG_RED "table" RESET_ALL              \
  ": " FG_CYAN BOLD "TABLE" RESET_ALL ", " FG_RED "filename" RESET_ALL         \
  ": " FG_CYAN BOLD "String" RESET_ALL ", " FG_RED "delim" RESET_ALL           \
  ": " FG_CYAN BOLD "String" RESET_ALL ")\n"                                   \
  "Returns: " FG_CYAN BOLD "void" RESET_ALL "\n\n"                             \
  "Converts a  table to a CSV file, using the provided delimiter. The first "  \
  "line of the CSV will be the header contained in the table.\n"

#define CMD_TOP_BUSINESSES_WITH_CATEGORY_HELP                                  \
  "-> " FG_YELLOW "top_businesses_with_category" RESET_ALL "(" FG_RED          \
  "sgr" RESET_ALL ": " FG_CYAN BOLD "SGR" RESET_ALL ", " FG_RED                \
  "top" RESET_ALL ": " FG_CYAN BOLD "Number" RESET_ALL ", " FG_RED             \
  "category" RESET_ALL ": " FG_CYAN BOLD "String" RESET_ALL ")\n"              \
  "Returns: " FG_CYAN BOLD "TABLE" RESET_ALL "\n\n"                            \
  "Creates a table with information about the n businesses with the most "     \
  "stars in that category.\n"

#define CMD_PROJECTION_HELP                                                    \
  "-> " FG_YELLOW "projection" RESET_ALL "(" FG_RED "table" RESET_ALL          \
  ": " FG_CYAN BOLD "TABLE" RESET_ALL ", " FG_RED "columns" RESET_ALL          \
  ": " FG_CYAN BOLD "Number[]" RESET_ALL ")\n"                                 \
  "Returns: " FG_CYAN BOLD "TABLE" RESET_ALL "\n\n"                            \
  "Provided a table, creates another one with only the columns whose index "   \
  "is in the array passed as parameter.\n"

#define CMD_REVIEWS_WITH_WORD_HELP                                             \
  "-> " FG_YELLOW "reviews_with_word" RESET_ALL "(" FG_RED "sgr" RESET_ALL     \
  ": " FG_CYAN BOLD "SGR" RESET_ALL ", " FG_RED "word" RESET_ALL               \
  ": " FG_CYAN BOLD "String" RESET_ALL ")\n"                                   \
  "Returns: " FG_CYAN BOLD "TABLE" RESET_ALL "\n\n"                            \
  "Creates a table with the id of all reviews which contain the given word "   \
  "on its field text.\n"

#define CMD_FILTER_HELP                                                        \
  "-> " FG_YELLOW "filter" RESET_ALL "(" FG_RED "table" RESET_ALL              \
  ": " FG_CYAN BOLD "TABLE" RESET_ALL ", " FG_RED "field_name" RESET_ALL       \
  ": " FG_CYAN BOLD "String" RESET_ALL ", " FG_RED "value" RESET_ALL           \
  ": " FG_CYAN BOLD "String" RESET_ALL ", " FG_RED "op" RESET_ALL              \
  ": " FG_CYAN BOLD "Operator" RESET_ALL ")\n"                                 \
  "Returns: " FG_CYAN BOLD "TABLE" RESET_ALL "\n\n"                            \
  "Provided a table, creates another one containing only the lines which "     \
  "match a certain condition. The condition which must be met is that the "    \
  "chosen  field in that line(field_name) must be equal(EQ), less than(LT) "   \
  "or greater than(GT) the value passed as parameter, depending on the "       \
  "chosen operator.\n"

#define CMD_JOIN_HELP                                                          \
  "-> " FG_YELLOW "join" RESET_ALL "(" FG_RED "table_a" RESET_ALL              \
  ": " FG_CYAN BOLD "TABLE" RESET_ALL ", " FG_RED "table_b" RESET_ALL          \
  ": " FG_CYAN BOLD "TABLE" RESET_ALL ")\n"                                    \
  "Returns: " FG_CYAN BOLD "TABLE" RESET_ALL "\n\n"                            \
  "Creates a  new table which is essentially the result of appending all the " \
  "lines of table_b to table_a. If the tables don't have the same "            \
  "field_names and number, it will return NULL.\n"

#define CMD_AVG_HELP                                                           \
  "-> " FG_YELLOW "avg" RESET_ALL "(" FG_RED "table" RESET_ALL                 \
  ": " FG_CYAN BOLD "TABLE" RESET_ALL ", " FG_RED "field_name" RESET_ALL       \
  ": " FG_CYAN BOLD "String" RESET_ALL ")\n"                                   \
  "Returns: " FG_CYAN BOLD "float" RESET_ALL "\n\n"                            \
  "Provided a table and a column name, it calculates de average of all the "   \
  "values in it,  should they be numbers."
#define CMD_MIN_HELP                                                           \
  "-> " FG_YELLOW "min" RESET_ALL "(" FG_RED "table" RESET_ALL                 \
  ": " FG_CYAN BOLD "TABLE" RESET_ALL ", " FG_RED "field_name" RESET_ALL       \
  ": " FG_CYAN BOLD "String" RESET_ALL ")\n"                                   \
  "Returns: " FG_CYAN BOLD "TABLE" RESET_ALL "\n\n"                            \
  "Provided a table and a column name, it returns a table with all the lines " \
  "which have the minimum value in that column\n"

#define CMD_MAX_HELP                                                           \
  "-> " FG_YELLOW "max" RESET_ALL "(" FG_RED "table" RESET_ALL                 \
  ": " FG_CYAN BOLD "TABLE" RESET_ALL ", " FG_RED "field_name" RESET_ALL       \
  ": " FG_CYAN BOLD "String" RESET_ALL ")\n"                                   \
  "Returns: " FG_CYAN BOLD "TABLE" RESET_ALL "\n\n"                            \
  "Provided a table and a column name, it returns a table with all the lines " \
  "which have the maximum value in that column\n"

#endif // __HELP_H_
