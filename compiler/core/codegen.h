#ifndef WEBCEE_CODEGEN_H
#define WEBCEE_CODEGEN_H

#include "ir.h"
#include <stdio.h>

// Generate C code from IR
void codegen_generate(WceIrNode* root, FILE* out);

#endif // WEBCEE_CODEGEN_H
