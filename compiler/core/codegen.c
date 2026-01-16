#include "codegen.h"
#include "token.h"

static void emit_node(WceIrNode* node, FILE* out, int indent);
static void emit_children(WceIrNode* parent, FILE* out, int indent);
static void emit_properties(WceIrNode* node, FILE* out, int indent);

static void print_indent(FILE* out, int indent) {
    for (int i = 0; i < indent; i++) fprintf(out, "    ");
}

void codegen_generate(WceIrNode* root, FILE* out) {
    if (!root) return;

    WceIrNode* child = root->first_child;
    while (child) {
        emit_node(child, out, 1);
        child = child->next_sibling;
    }
}

static void emit_properties(WceIrNode* node, FILE* out, int indent) {
    if (!node) return;

    if (node->style) {
        print_indent(out, indent);
        fprintf(out, "wce_css(\"%s\");\n", node->style);
    }
    if (node->value_ref) {
        print_indent(out, indent);
        fprintf(out, "wce_bind(\"%s\");\n", node->value_ref);
    }
    if (node->event_handler) {
        print_indent(out, indent);
        fprintf(out, "wce_on_click(\"%s\");\n", node->event_handler);
    }
}

static void emit_children(WceIrNode* parent, FILE* out, int indent) {
    if (!parent) return;
    WceIrNode* child = parent->first_child;
    while (child) {
        emit_node(child, out, indent);
        child = child->next_sibling;
    }
}

static void emit_node(WceIrNode* node, FILE* out, int indent) {
    if (!node) return;

    const char* label = node->label ? node->label : "";

    switch (node->type) {
        case IR_NODE_CONTAINER:
            print_indent(out, indent);
            fprintf(out, "wce_container_begin();\n");
            emit_properties(node, out, indent + 1);
            emit_children(node, out, indent + 1);
            print_indent(out, indent);
            fprintf(out, "wce_container_end();\n");
            break;
        case IR_NODE_ROW:
            print_indent(out, indent);
            fprintf(out, "wce_row_begin();\n");
            emit_properties(node, out, indent + 1);
            emit_children(node, out, indent + 1);
            print_indent(out, indent);
            fprintf(out, "wce_row_end();\n");
            break;
        case IR_NODE_COL:
            print_indent(out, indent);
            fprintf(out, "wce_col_begin();\n");
            emit_properties(node, out, indent + 1);
            emit_children(node, out, indent + 1);
            print_indent(out, indent);
            fprintf(out, "wce_col_end();\n");
            break;
        case IR_NODE_CARD:
            print_indent(out, indent);
            fprintf(out, "wce_card_begin();\n");
            emit_properties(node, out, indent + 1);
            emit_children(node, out, indent + 1);
            print_indent(out, indent);
            fprintf(out, "wce_card_end();\n");
            break;
        case IR_NODE_PANEL:
            print_indent(out, indent);
            fprintf(out, "wce_panel_begin();\n");
            emit_properties(node, out, indent + 1);
            emit_children(node, out, indent + 1);
            print_indent(out, indent);
            fprintf(out, "wce_panel_end();\n");
            break;
        case IR_NODE_TEXT:
            print_indent(out, indent);
            fprintf(out, "wce_text_begin(\"%s\");\n", label);
            emit_properties(node, out, indent + 1);
            emit_children(node, out, indent + 1);
            print_indent(out, indent);
            fprintf(out, "wce_text_end();\n");
            break;
        case IR_NODE_BUTTON:
            print_indent(out, indent);
            fprintf(out, "wce_button_begin(\"%s\");\n", label);
            emit_properties(node, out, indent + 1);
            emit_children(node, out, indent + 1);
            print_indent(out, indent);
            fprintf(out, "wce_button_end();\n");
            break;
        case IR_NODE_INPUT:
            print_indent(out, indent);
            fprintf(out, "wce_input_begin(\"%s\");\n", label);
            emit_properties(node, out, indent + 1);
            emit_children(node, out, indent + 1);
            print_indent(out, indent);
            fprintf(out, "wce_input_end();\n");
            break;
        case IR_NODE_SLIDER:
            print_indent(out, indent);
            fprintf(out, "wce_slider_begin(\"%s\");\n", label);
            emit_properties(node, out, indent + 1);
            emit_children(node, out, indent + 1);
            print_indent(out, indent);
            fprintf(out, "wce_slider_end();\n");
            break;
        case IR_NODE_PROGRESS:
            print_indent(out, indent);
            fprintf(out, "wce_progress_begin(\"%s\");\n", label);
            emit_properties(node, out, indent + 1);
            emit_children(node, out, indent + 1);
            print_indent(out, indent);
            fprintf(out, "wce_progress_end();\n");
            break;
        default:
            // IR_NODE_ROOT or unknown types are not directly output here
            break;
    }
}
