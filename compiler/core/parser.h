#ifndef WEBCEE_PARSER_H
#define WEBCEE_PARSER_H

#include "lexer.h"
#include "ast.h"
#include "diagnostic.h"
#include "memory_pool.h"

typedef struct {
    Lexer* lexer;
    Token current_token;
    DiagnosticBag* diagnostics;
    MemoryPool* pool;
    int panic_mode; // Error recovery mode flag
} Parser;

Parser* parser_create(Lexer* lexer, DiagnosticBag* diagnostics, MemoryPool* pool);
void parser_destroy(Parser* parser);

// Parsing entry point
WceAstNode* parser_parse(Parser* parser);

#endif // WEBCEE_PARSER_H
