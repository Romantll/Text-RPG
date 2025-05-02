#ifndef NPC_H
#define NPC_H

typedef enum {
    NPC_FRIENDLY,
    NPC_HOSTILE,
    NPC_MERCHANT,
    NPC_NEUTRAL
} NPCType;

typedef struct NPC {
    const char* name;
    const char* dialogue;
    NPCType type;
    struct NPC* next; 
}NPC;

NPC* createNPC(const char* name, const char* dialogue, NPCType type);

#endif // NPC_H