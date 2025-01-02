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
    Message,
    Branch,
    Event,
    Entry, 
    Jump
} LMS_NodeTypes;

typedef struct LMS_Node 
{
    LMS_NodeTypes type;
    u8 subType;
    u16 reserved;
    u16 subTypeValue;
    LMS_NodeInfo* nodeInfo;
} LMS_Node;

typedef struct LMS_NodeInfo 
{
    u16 param1;
    u16 nextNodeID;
    u16 param3;
    u16 param4;

} LMS_NodeInfo;

LMS_Flowchart* LMS_InitFlowchart(const void* data);
void LMS_CloseFlowchart(LMS_Flowchart* flowchart);

int LMS_GetEntryNodeIndex(const LMS_Flowchart* flowchart, const char *label);

char* LMS_GetFlowParamText(LMS_Flowchart* flowchart, s32 offset);
const LMS_Node* LMS_GetNodeDataPtr(const LMS_Flowchart* flowchart, s32 index);

int LMS_GetNodeNum(LMS_Flowchart* flowchart);
int* LMS_GetCaseIndexesFromBranchNode(LMS_Flowchart* flowchart, s32 startIndex);

