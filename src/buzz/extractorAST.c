#include<stdlib.h>
#include<stdio.h>

#include "extractorAST.h"

static void ASTExtractor_Init(ASTExtractor*);

ASTExtractor ASTExtractor_Create(){
    ASTExtractor This;
    ASTExtractor_Init(&This);
    This.Free = ASTExtractor_Free;
    return This;
}

static void ASTExtractor_Init(ASTExtractor *This)
{
    This->epilogue = ASTExtractor_epilogue;
    This->prologue = ASTExtractor_prologue;
    This->astNodeIdSeed = 0;
    This->stack = TPile_Create();
}

void ASTExtractor_prologue(ASTExtractor* This,char* nodeType){
    int parentId;
    int astNodeId = ++ This->astNodeIdSeed;

    if(This->stack.Length(&This->stack) != 0)
        parentId = This->stack.Top->Value;
    else
        parentId = 0;

    This->stack.Push(&This->stack, astNodeId);
    visit_begin(astNodeId, parentId, nodeType);
}

void ASTExtractor_epilogue(ASTExtractor* This,char* nodeType){
    visit_end(This->stack.Top->Value,nodeType);
    This->stack.Pop(&This->stack);
}

void ASTExtractor_Free(ASTExtractor* This){
    This->stack.Free(&This->stack);
    This->astNodeIdSeed = 0;
    puts("Destruction of ASTExtracteur SUCCESS.\n");
}

void visit_begin(int nodeId,int parentId,char* nodeType){
    printf("astEdge  %d %d\n",parentId,nodeId);
    printf("astEdge  %d Begin:node %s\n",nodeId,nodeType);
}

void visit_end(int nodeId, char* nodeType){
    printf("astEdge  %d End:node %s_END\n",nodeId,nodeType);
}

void visitTok(int parentId, int childId, buzztok_t tk) {

    printf("ast_edge %d %d\n", parentId, childId);

    printf("node_type %d token\n", childId);
    printf("tk_type %d %d\n", childId, tk->type);
    printf("literal %d %s\n", childId, tk->value);
    printf("line_begin %d %llu\n", childId, tk->line);
    printf("column_begin %d %llu\n", childId, tk->col);
    // don't print file name (for the moment)
    //printf("file_name %d %s", childId, tk->fname);
  }

void dumpTok(ASTExtractor* This, buzztok_t tk) {
    int parentId = This->stack.Top->Value;
    int astNodeId = ++ This->astNodeIdSeed;
    visitTok(parentId, astNodeId, tk);
}
