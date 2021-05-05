#ifndef __HELP_H_
#define __HELP_H_

#define CMD_SHOW_HELP                                                          \
  "Presents a table on the screen with a pager\n"                              \
  "Keys:\n"                                                                    \
  "Arrow Up/Arrow Down: Go one line up and down, respectively\n"               \
  "Arrow Left/Arrow Right: Go one page backward and foward, respectively\n"    \
  "q: quit pager\n"

#define CMD_JOIN_HELP                                                          \
  " join(table_a: TABLE ,table_b: Table)\n"                                    \
  "Returns: TABLE\n"                                                           \
  "Creates a  new table which is essentially the result of appending all the " \
  "lines of table_b to table_a. If the tables don't have the same "            \
  "field_names and number, it will return NULL.\n"

#define CMD_LOAD_SGR_HELP                                                      \
  " load_sgr([users: String, businesses: String, reviews: String])"            \
  "Returns: SGR\n\n"                                                           \
  "Creates an SGR structure which contains all the information retrieved "     \
  "from the input files(users,businesses and reviews), organized in a way so " \
  "as to facilitate the 9 possible queries.\n\n"                               \
  "When called with three valid paths to csv files, the first one will be "    \
  "used as source for user entries, second one for business entries and  "     \
  "third one for review entries. Each line will be parsed and stored in the "  \
  "appropriate structure inside SGR.\n\n"                                      \
  "When called without arguments it uses the files specified in the config or" \
  "the default files,in case no config is provided.\n"

#define CMD_BUSINESSES_STARTED_BY_LETTER_HELP                                  \
  "businesses_started_by_letter(sgr: SGR, letter: String)\n\n"                 \
  "Returns: TABLE\n\n"                                                         \
  "Creates a table with the name of the businesses, present in the "           \
  "provided SGR,  whose names start with a given letter(case insensitive).\n"

#define CMD_BUSINESSES_INFO_HELP                                               \
  "businesses_info(sgr: SGR,  business_id: String)\n\n"                        \
  "Returns: TABLE\n\n"                                                         \
  "Creates a table with information about a business, given its business id. " \
  "This information consists of: name, city, state, average number of stars "  \
  "and total number of reviews.\n"

#define CMD_BUSINESSES_REVIEWED_HELP                                           \
  "businesses_reviewed(sgr: SGR,  user_id: String)\n\n"                        \
  "Returns: TABLE\n\n"                                                         \
  "Creates a table with information about all the business a user has "        \
  "reviewed, given its user id. This information consists of business id and " \
  "name.\n"

#define CMD_BUSINESSES_WITH_STARS_AND_CITY_HELP                                \
  "businesses_with_stars_and_city(sgr: SGR,  stars: float, city: String)\n\n"  \
  "Returns: TABLE\n\n"                                                         \
  "Creates  a table with information about all the businesses in that city "   \
  "which have an average number of stars above the provided one.\n"

#define CMD_FROM_CSV_HELP                                                      \
  "from_csv(filename: String, delim: String)\n\n"                              \
  "Returns: TABLE\n\n"                                                         \
  "Creates a table with all the content from the provided CSV file, which "    \
  "must contain a header, separated by the given delimiter.The number of "     \
  "columns of the table will be the same as the fields in the header."

#define CMD_TOP_BUSINESSES_BY_CITY_HELP                                        \
  "top_businesses_by_city(SGR: sgr, int: top)\n\n"                             \
  "Return: TABLE\n\n"                                                          \
  "Creates a table with information about the n businesses with the most "     \
  "stars in all city.\n"

#define CMD_INTERNATIONAL_USERS_HELP                                           \
  "international_users(SGR: sgr) \n\n"                                         \
  "Return: TABLE\n\n"                                                          \
  "Creates a table with information with all the users that have visited "     \
  "more than one state.\n"

#define CMD_TO_CSV_HELP                                                        \
  "to_csv(table: TABLE , filename: String,  delim: String)\n\n"                \
  "Returns: void\n\n"                                                          \
  "Converts a  table to a CSV file, using the provided delimiter. The first "  \
  "line of the CSV will be the header contained in the table.\n"

#define CMD_TOP_BUSINESSES_WITH_CATEGORY_HELP                                  \
  "top_businesses_with_category(SGR: sgr, int: top, char*: category)\n\n"      \
  "Return: TABLE\n"                                                            \
  "Creates a table with information about the n businesses with the most "     \
  "stars in that category.\n"

#define CMD_PROJECTION_HELP                                                    \
  "projection(table: TABLE ,  columns: int[])\n\n"                             \
  "Returns: TABLE\n\n"                                                         \
  "Provided a table, creates another one with only the columns whose index "   \
  "is in the array passed as parameter.\n"

#define CMD_REVIEWS_WITH_WORD_HELP                                             \
  "reviews_with_word(SGR: sgr, char*: word)\n\n"                               \
  "Return: TABLE\n\n"                                                          \
  "Creates a table with the id of all reviews which contain the given word "   \
  "on its field text.\n"

#define CMD_FILTER_HELP                                                        \
  "filter(table: TABLE ,  field_name: String, value: String,  op: "            \
  "Operator)\n\n"                                                              \
  "Returns: TABLE\n\n"                                                         \
  "Provided a table, creates another one containing only the lines which "     \
  "match a certain condition. The condition which must be met is that the "    \
  "chosen  field in that line(field_name) must be equal(EQ), less than(LT) "   \
  "or greater than(GT) the value passed as parameter, depending on the "       \
  "chosen operator.\n"

#define CMD_JOIN_HELP                                                          \
  "join(table_a: TABLE ,table_b: Table)\n\n"                                   \
  "Returns: TABLE\n\n"                                                         \
  "Creates a  new table which is essentially the result of appending all the " \
  "lines of table_b to table_a. If the tables don't have the same "            \
  "field_names and number, it will return NULL.\n"

#define CMD_AVG_HELP                                                           \
  "avg(table: TABLE ,  field_name: String)\n\n"                                \
  "Returns: String\n\n"                                                        \
  "Provided a table and a column name, it calculates de average of all the "   \
  "values in it,  should they be numbers."

#endif // __HELP_H_
