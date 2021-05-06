/**
 * @file view_commands.h
 * @author Mariana Rodrigues, Matilde Bravo e Pedro Alves
 * @date 4 Maio 2021
 * @brief This Module is responsible to manipulated all information.
 */

#ifndef VCOMMANDS_H
#define VCOMMANDS_H

#include "model/state.h"

// Comandos utilizados no programa
Variable print(STATE s, Variable *args);
Variable quit(STATE s, Variable *args);
Variable help(STATE s, Variable *args);
Variable cmd_from_csv(STATE s, Variable *args);
Variable cmd_to_csv(STATE s, Variable *args);

Variable cmd_load_sgr(STATE s, Variable *args);
Variable cmd_businesses_started_by_letter(STATE s, Variable *args);
Variable cmd_business_info(STATE s, Variable *args);
Variable cmd_businesses_reviewed(STATE s, Variable *args);
Variable cmd_businesses_with_stars_and_city(STATE s, Variable *args);
Variable cmd_top_businesses_by_city(STATE s, Variable *args);
Variable cmd_international_users(STATE s, Variable *args);
Variable cmd_top_businesses_with_category(STATE s, Variable *args);
Variable cmd_reviews_with_word(STATE s, Variable *args);

Variable show(STATE s, Variable *args);
Variable cmd_state(STATE s, Variable *args);
Variable cmd_projection(STATE s, Variable *args);
Variable cmd_filter(STATE s, Variable *args);
Variable cmd_join(STATE s, Variable *args);
Variable cmd_avg(STATE s, Variable *args);
Variable cmd_max(STATE s, Variable *args);
Variable cmd_min(STATE s, Variable *args);

#endif
