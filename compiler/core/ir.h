#ifndef WEBCEE_IR_H
#define WEBCEE_IR_H

#include "token.h"
#include "memory_pool.h"
#include "ast.h"
#include "diagnostic.h"
#include <stdio.h>

typedef enum {
    IR_NODE_ROOT,
    IR_NODE_CONTAINER,
    IR_NODE_ROW,
    IR_NODE_COL,
    IR_NODE_CARD,
    IR_NODE_PANEL,
    IR_NODE_TEXT,
    IR_NODE_BUTTON,
    IR_NODE_INPUT,
    IR_NODE_SLIDER,
    IR_NODE_PROGRESS
} WceIrNodeType;

typedef struct WceIrNode WceIrNode;

struct WceIrNode {
    WceIrNodeType type;
    Token token;

    char* label;
    char* value_ref;
    char* event_handler;
    char* style;

    WceIrNode* first_child;
    WceIrNode* last_child;
    WceIrNode* next_sibling;
    WceIrNode* parent;
};

// IR top-level analysis structure
typedef struct {
    const char* key;
    int usage_count;
    Token token;
} IrBindingEntry;

typedef struct {
    const char* name;
    int usage_count;
    Token token;
} IrEventEntry;

typedef struct {
    const char* style_text;
    int usage_count;
    Token token;
} IrStyleEntry;

typedef struct {
    WceIrNode* root;
    MemoryPool* pool;

    IrBindingEntry* bindings;
    int binding_count;
    int binding_capacity;

    IrEventEntry* events;
    int event_count;
    int event_capacity;

    IrStyleEntry* styles;
    int style_count;
    int style_capacity;

    int max_nesting_depth;
} WceIrContext;

WceIrNode* ir_node_create(MemoryPool* pool, WceIrNodeType type, Token token);
void ir_node_add_child(WceIrNode* parent, WceIrNode* child);

// Build UI semantic IR tree from AST
WceIrContext* ir_build_from_ast(MemoryPool* pool, WceAstNode* ast_root, DiagnosticBag* diagnostics);

// IR analysis and checking
void ir_analyze(WceIrContext* ctx, DiagnosticBag* diagnostics);

// IR dump output
void ir_dump(WceIrContext* ctx, FILE* out);

// Helper function declarations
void ir_dump_node(WceIrNode* node, FILE* out, int indent);

#endif // WEBCEE_IR_H
