#ifndef _EXTRACTORAST_H
#define _EXTRACTORAST_H

#include <buzz/Pile.h>
#include <buzz/buzzlex.h>

#ifdef __cplusplus
  extern "C" {
#endif

    typedef struct ASTExtractor
            {
                    int astNodeIdSeed;
                    struct TPile stack;

                    void(*epilogue)(struct ASTExtractor*,char*);
                    void(*prologue)(struct ASTExtractor*,char*);
                    void(*Free)(struct ASTExtractor*);
            } ASTExtractor ;


    ASTExtractor ASTExtractor_Create();

    void ASTExtractor_epilogue(ASTExtractor*,char*);

    void ASTExtractor_prologue(ASTExtractor*,char*);

    void ASTExtractor_Free(ASTExtractor*);

    void visit_begin(int nodeId,int parentId,char* nodeType);

    void visit_end(int nodeId, char* nodeType);

    void visitTok(int parentId, int childId, buzztok_t tk);

    void dumpTok(ASTExtractor* This, buzztok_t tk);

#ifdef __cplusplus
}
#endif

#endif
