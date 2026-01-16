#ifndef WEBCEE_LEXER_H
#define WEBCEE_LEXER_H

#include "token.h"
#include "diagnostic.h"

typedef struct {
    const char* source;      // Source code string
    const char* file_name;   // File name
    int position;            // Current position (character index)
    int length;              // Total length of source code
    int line;                // Current line
    int column;              // Current column
    DiagnosticBag* diagnostics; // Associated diagnostic bag
} Lexer;

// Create Lexer
Lexer* lexer_create(const char* source, const char* file_name, DiagnosticBag* diagnostics);
void lexer_destroy(Lexer* lexer);

// Get next token
Token lexer_next_token(Lexer* lexer);

#endif // WEBCEE_LEXER_H
