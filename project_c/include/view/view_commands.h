#ifndef VCOMMANDS_H
#define VCOMMANDS_H

#include "model/state.h"

// Comandos utilizados no programa
Variable print(Variable *args);
Variable quit(Variable *args);
Variable help(Variable *args);
Variable cmd_from_csv(Variable *args);
Variable cmd_to_csv(Variable *args);

Variable cmd_load_sgr(Variable *args);
Variable cmd_businesses_started_by_letter(Variable *args);
Variable cmd_business_info(Variable *args);
Variable cmd_businesses_reviewed(Variable *args);
Variable cmd_businesses_with_stars_and_city(Variable *args);
Variable cmd_top_businesses_by_city(Variable *args);
Variable cmd_international_users(Variable *args);
Variable cmd_top_businesses_with_category(Variable *args);
Variable cmd_reviews_with_word(Variable *args);

Variable show(Variable *args);
Variable cmd_projection(Variable *args);
Variable cmd_filter(Variable *args);
Variable cmd_join(Variable *args);

#endif
