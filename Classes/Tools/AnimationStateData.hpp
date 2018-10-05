//
//  AnimationStateData.hpp
//  PojectShaoGame
//
//  Created by shao on 2018/5/11.
//

#include "spine/spine.h"
#include <spine/Animation.h>
#include <spine/SkeletonData.h>
#include "iostream"
#include <spine/Animation.h>
#include <spine/SkeletonData.h>
class AnimationStateData :public spAnimationStateData{
public:
    typedef struct{
        spSkeletonData *skeletonData;
        float defaultMix;
         void*  entries;
    } spAnimationStateData;
    
    static AnimationStateData * spAnimationStateData_create (spSkeletonData* skeletonData);
    
    void spAnimationStateData_dispose (AnimationStateData* self);
    
    void spAnimationStateData_setMixByName (AnimationStateData* self, const char* fromName, const char* toName, float duration);
    void spAnimationStateData_setMix (AnimationStateData* self, spAnimation* from, spAnimation* to, float duration);
    /* Returns 0 if there is no mixing between the animations. */
    float spAnimationStateData_getMix (AnimationStateData* self, spAnimation* from, spAnimation* to);
    
    typedef AnimationStateData animationStateData;
    
};

