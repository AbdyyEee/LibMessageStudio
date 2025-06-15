#pragma once

#include "commonbin.h"

typedef struct LMS_Flowchart
{
    LMS_Binary common;
    s32 flw3Offset; 
    s32 fen1Offset; 
    s32 ref1Offset; 
} LMS_Flowchart;

typedef enum LMS_NodeTypes {
    MESSAGE = 1,
    BRANCH = 2,
    EVENT = 3,
    ENTRY = 4,
    JUMP = 5
} LMS_NodeTypes;

typedef struct LMS_Node 
{
    LMS_NodeTypes type; // 0
    s8 paramType; // 1
    u16 reserved; // 2
    u32 paramValue; // 4
    LMS_NodeInfo* nodeInfo; // 8 
} LMS_Node;

typedef struct LMS_NodeInfo 
{
    u16 nextNodeID;
    u16 identifier;
    u16 short1;
    u16 short2;

} LMS_NodeInfo;

LMS_Flowchart* LMS_InitFlowchart(const void* data);
void LMS_CloseFlowchart(LMS_Flowchart* flowchart);

int LMS_GetEntryNodeIndex(const LMS_Flowchart* flowchart, const char *label);

char* LMS_GetFlowParamText(LMS_Flowchart* flowchart, s32 offset);
const LMS_Node* LMS_GetNodeDataPtr(const LMS_Flowchart* flowchart, s32 index);

int LMS_GetNodeNum(LMS_Flowchart* flowchart);
int* LMS_GetCaseIndexesFromBranchNode(LMS_Flowchart* flowchart, s32 startIndex);

