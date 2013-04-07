/*
 * base.h
 *
 *  Created on: Apr 7, 2013
 *      Author: Ashraf Saleh
 */

#ifndef BASE_H
#define BASE_H

#include <fstream>

#define MAX_IP 80 // max input
#define EPISILON 1

#define is_end_of_input(ch)       ((ch) == '\0')
#define is_layout(ch)             (!is_end_of_input(ch)  && (ch) <= ' ')
#define is_comment_starter(ch)    ((ch) == '{')
#define is_comment_stopper(ch)    ((ch) == '}' )
#define is_uc_letter(ch)          ('A' <= (ch) && (ch) <= 'Z')
#define is_lc_letter(ch)          ('a' <= (ch) && (ch) <= 'z')
#define is_letter(ch)             (is_uc_letter(ch) || is_lc_letter(ch))
#define is_digit(ch)              ('0' <= (ch) && (ch) <= '9')
#define is_letter_or_digit(ch)    (is_letter(ch) || is_digit(ch))
#define is_operator(ch)           (strchr("+-*/",   (ch)) != 0)
#define is_separator(ch)          (strchr(";,()",   (ch)) != 0)
#define is_blank(ch)              ((ch) == ' ')
#define is_delim(ch)              (is_operator(ch) || is_separator(ch) || is_blank(ch))

#define is_special_char(ch)       (strchr(".,;:<>/*[]+-=(){\t ",  (ch)) != 0)

const char VALID_SPECIAL_CHARS[] = ".,;:<>/*[]+-=(){\t ";
const char VALID_CHARS[] = "0123456789abcdefghijklmnopqrstuwvxyzABCDEFGHIJKLMNOPQRSTUVWXYZ.,;:<>/*[]+-=(){\t ";
const char EOF_CHAR = EOF;
const char L_CURLY  = '{';
const char R_CURLY  = '}';
const char BLANK    = ' ';
const char TAB      = '\t';
const char EOL_CHAR = '\0';

#endif	/* BASE_H */


