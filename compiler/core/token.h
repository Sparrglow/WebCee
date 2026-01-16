#ifndef WEBCEE_TOKEN_H
#define WEBCEE_TOKEN_H

typedef enum {
    TOKEN_EOF,
    TOKEN_UNKNOWN,
    
    // Literals
    TOKEN_IDENTIFIER,   // wce_button, my_var
    TOKEN_STRING,       // "hello"
    TOKEN_NUMBER,       // 123, 3.14
    
    // Symbols
    TOKEN_LPAREN,       // (
    TOKEN_RPAREN,       // )
    TOKEN_LBRACE,       // {
    TOKEN_RBRACE,       // }
    TOKEN_COMMA,        // ,
    TOKEN_SEMICOLON,    // ;
    
    // Operators
    TOKEN_PLUS,         // +
    TOKEN_MINUS,        // -
    TOKEN_STAR,         // *
    TOKEN_SLASH,        // /
    TOKEN_ASSIGN,       // =
    TOKEN_EQ,           // ==
    TOKEN_NEQ,          // !=
    TOKEN_LT,           // <
    TOKEN_GT,           // >
    TOKEN_LE,           // <=
    TOKEN_GE,           // >=
    
    // Keywords
    TOKEN_KW_IF,        // wce_if
    TOKEN_KW_ELSE,      // wce_else
    TOKEN_KW_FOR        // wce_for
} TokenType;

typedef struct {
    TokenType type;
    const char* text;   // Pointing to start in source (not owned)
    int length;         // Length
    int line;
    int column;
} Token;

#endif // WEBCEE_TOKEN_H
