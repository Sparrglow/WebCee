#ifndef WEBCEE_ERROR_CODES_H
#define WEBCEE_ERROR_CODES_H

// Lexer Errors (001-099)
#define ERR_LEX_UNKNOWN_CHAR       1
#define ERR_LEX_UNTERMINATED_STR   2

// Parser Errors (100-199)
#define ERR_PARSER_EXPECTED_RBRACE 101 // Missing right brace `}`
#define ERR_PARSER_EXPECTED_RPAREN 102 // Missing right parenthesis `)`
#define ERR_PARSER_EXPECTED_LPAREN 103 // Missing left parenthesis `(`
#define ERR_PARSER_EXPECTED_ID     104 // Expected identifier
#define ERR_PARSER_EXPECTED_SEMI   105 // Expected semicolon
#define ERR_PARSER_UNEXPECTED_TOK  106 // Unexpected token
#define ERR_PARSER_EXPECTED_LBRACE 107 // Missing left brace `{`

// Semantic Errors (200-299)
#define ERR_SEMANTIC_UNDEFINED     201 // Undefined component or function
#define ERR_SEMANTIC_ARG_COUNT     202 // Argument count mismatch
#define ERR_SEMANTIC_TYPE_MISMATCH 203 // Argument type mismatch

// IR Errors (300-399)
#define ERR_IR_PROPERTY_CONTEXT    301 // Property context error
#define ERR_IR_UNKNOWN_COMPONENT   302 // Unknown component type

// Code Generation Warnings (400-499)
#define WARN_CODEGEN_UNUSED_BIND   401 // Unused binding
#define WARN_CODEGEN_DEEP_NESTING  402 // Deep nesting warning
#define WARN_CODEGEN_EMPTY_STYLE   403 // Empty style warning

#endif // WEBCEE_ERROR_CODES_H
