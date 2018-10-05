//
//  AnimationStateData.cpp
//  PojectShaoGame
//
//  Created by shao on 2018/5/11.
//

#include "AnimationStateData.hpp"
#include <spine/AnimationStateData.h>
#include <spine/extension.h>
typedef struct _ToEntry _ToEntry;
struct _ToEntry {
    spAnimation* animation;
    float duration;
    _ToEntry* next;
};

_ToEntry* _ToEntry_create (spAnimation* to, float duration) {
    _ToEntry* self = NEW(_ToEntry);
    self->animation = to;
    self->duration = duration;
    return self;
}

void _ToEntry_dispose (_ToEntry* self) {
    FREE(self);
}

/**/

typedef struct _FromEntry _FromEntry;
struct _FromEntry {
    spAnimation* animation;
    _ToEntry* toEntries;
    _FromEntry* next;
};

_FromEntry* _FromEntry_create (spAnimation* from) {
    _FromEntry* self = NEW(_FromEntry);
    self->animation = from;
    return self;
}

void _FromEntry_dispose (_FromEntry* self) {
    FREE(self);
}

AnimationStateData *AnimationStateData::spAnimationStateData_create(spSkeletonData* skeletonData){
    AnimationStateData *self = new AnimationStateData();
    CONST_CAST(spSkeletonData*, self->skeletonData) = skeletonData;
    return self;
};
void AnimationStateData::spAnimationStateData_dispose(AnimationStateData *self){
    _ToEntry* toEntry;
    _ToEntry* nextToEntry;
    _FromEntry* nextFromEntry;
    
    _FromEntry* fromEntry = (_FromEntry*)self->entries;
    while (fromEntry) {
        toEntry = fromEntry->toEntries;
        while (toEntry) {
            nextToEntry = toEntry->next;
            _ToEntry_dispose(toEntry);
            toEntry = nextToEntry;
        }
        nextFromEntry = fromEntry->next;
        _FromEntry_dispose(fromEntry);
        fromEntry = nextFromEntry;
    }
    FREE(self);
}
void AnimationStateData::spAnimationStateData_setMix(AnimationStateData *self, spAnimation *from, spAnimation *to, float duration){
    /* Find existing FromEntry. */
    _ToEntry* toEntry;
    _FromEntry* fromEntry = (_FromEntry*)self->entries;
    while (fromEntry) {
        if (fromEntry->animation == from) {
            /* Find existing ToEntry. */
            toEntry = fromEntry->toEntries;
            while (toEntry) {
                if (toEntry->animation == to) {
                    toEntry->duration = duration;
                    return;
                }
                toEntry = toEntry->next;
            }
            break; /* Add new ToEntry to the existing FromEntry. */
        }
        fromEntry = fromEntry->next;
    }
    if (!fromEntry) {
        fromEntry = _FromEntry_create(from);
        fromEntry->next = (_FromEntry*)self->entries;
        CONST_CAST(_FromEntry*, self->entries) = fromEntry;
    }
    toEntry = _ToEntry_create(to, duration);
    toEntry->next = fromEntry->toEntries;
    fromEntry->toEntries = toEntry;
};
