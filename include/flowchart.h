#pragma once
#include "commonbin.h"

typedef struct LMS_Flowchart
{
    LMS_Binary common;
    s32 flw3Offset; 
    s32 fen1Offset; 
    s32 ref1Offset; 
} LMS_Flowchart;

/* Official Names */
typedef enum LMS_NodeType {
    MESSAGE = 0x1,
    BRANCH = 0x2,
    EVENT = 0x3,
    ENTRY = 0x4,
    JUMP = 0x5
} LMS_NodeTypes;

/* Unofficial Names */
typedef enum LMS_NodeParameterType {
    PARAM_32_0 = 0x0,
    PARAM_16_16 = 0x1,
    PARAM_16_8_8 = 0x2,
    PARAM_8_8_16 = 0x3,
    PARAM_8_8_8_8 = 0x4,
    STRING = 0x5,
    PARAM_32_1 = 0x6,
} LMS_NodeParameterType;

typedef struct LMS_Node 
{
    LMS_NodeType type; // 0
    LMS_NodeParameterType parameterType; // 1
    u16 reserved; // 2
    u32 parameterValue; // 4
    LMS_NodeInfo* nodeInfo; // 8 
} LMS_Node;

typedef struct LMS_NodeInfo 
{
    u16 nextNodeIndex;
    u16 identifier; // Only for Branch/Event nodes
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

