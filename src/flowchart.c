#include "flowchart.h"
#include "libms.h"

/* Functions match Tomodachi Life and Triforce Heros */

LMS_Flowchart* LMS_InitFlowchart(const void* data) 
{
    LMS_Flowchart* flowchart = (LMS_Flowchart*)LMSi_Malloc(sizeof(LMS_Flowchart));
    
    flowchart->common.data = (const char*)data;

    flowchart->flw3Offset = LMSi_SearchBlockByName(&flowchart->common, "FLW3");
    flowchart->fen1Offset = LMSi_SearchBlockByName(&flowchart->common, "FEN1");
    flowchart->ref1Offset = LMSi_SearchBlockByName(&flowchart->common, "REF1");
    
    return flowchart;
}


void LMS_CloseFlowchart(LMS_Flowchart* flowchart)
{
    if (flowchart->common.blocks) {

        LMSi_Free(flowchart->common.blocks);
    }
    
    LMSi_Free(flowchart);
}

u32 LMS_GetEntryNodeIndex(const LMS_Flowchart* flowchart, const char* label) {
    // TODO
}

// Inferring return type
const char* LMS_GetFlowParamText(LMS_Flowchart* flowchart, s32 offset) {
    
    LMS_BinaryBlock* flw3 = flowchart->common.blocks + flowchart->flw3Offset;

    if ((offset < 0) || (flw3->size <= (u32)offset)) {
        return NULL;
    }
    else {
        return (char *)((u32)flw3->data + offset);
    }

    return NULL;
}

const LMS_Node* LMS_GetNodeDataPtr(const LMS_Flowchart* flowchart, s32 index) {
    if (flowchart->flw3Offset == -1) {
        return NULL;
    }
  return (LMS_Node*)flowchart->common.blocks[flowchart->flw3Offset].data + (s32)index * 0x10 + 0x10;
}

s32 LMS_GetNodeNum(LMS_Flowchart* flowchart) 
{
    if (flowchart->flw3Offset == -1) {
        return NULL;
    }
  return (u32)*(flowchart->common).blocks[flowchart->flw3Offset].data;
}

const u16* LMS_GetCaseIndexesFromBranchNode(LMS_Flowchart* flowchart, s32 index)
{
    LMS_BinaryBlock* flw3 = (flowchart->common).blocks + flowchart->flw3Offset;

    if (flowchart->flw3Offset != -1) {
        char* data = flw3->data;
        char* nodeOffset = (char*)((s32)data + index * 0x10 + 0x10 );
        
        if (nodeOffset != NULL && (*nodeOffset == "\x02")) {
            return (u16*)((s32)data + (u32)*(u16*)(nodeOffset + 0xe) * 2 + 0x10 + (u32)*flw3->data * 0x10);
        }
    }
    return 0;
}
