#ifndef PASSWORD_CHECKER_H
#define PASSWORD_CHECKER_H

#include <stdbool.h>
bool check_length(const char *password);
bool check_range(char letter, char lower, char upper);
bool check_upper(const char *password);
bool check_lower(const char *password);
bool check_number(const char *password);
bool check_name(const char *first_name, const char *last_name, const char *password);

bool check_password(const char *first_name, const char *last_name, const char *password);

#endif // PASSWORD_CHECKER_H
