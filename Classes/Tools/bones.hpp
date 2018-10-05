//
//  bones.hpp
//  PojectShaoGame
//
//  Created by shao on 2018/5/10.
//

#ifndef bones_hpp
#define bones_hpp

#include <iostream>
#include "cocos2d.h"
#include <spine/BoneData.h>
#include "spine/Bone.h"
#include "spine/extension.h"
#include <spine/spine-cocos2dx.h>
class bones  :public spBone{
//    struct spSkeleton;

//    typedef struct  bones bones;

public:
    void spBone_setYDown (int/*bool*/yDown);
    int/*bool*/spBone_isYDown ();
    
    /* @param parent May be 0. */
    static bones* spBone_create (spBoneData* data, struct spSkeleton* skeleton, spBone* parent);
    void spBone_dispose (spBone* self);
    
    void spBone_setToSetupPose (spBone* self);
    
    void spBone_updateWorldTransform (spBone* self);
    void spBone_updateWorldTransformWith (spBone* self, float x, float y, float rotation, float scaleX, float scaleY, float shearX, float shearY);
    
    float spBone_getWorldRotationX (spBone* self);
    float spBone_getWorldRotationY (spBone* self);
    float spBone_getWorldScaleX (spBone* self);
    float spBone_getWorldScaleY (spBone* self);
    
    float spBone_worldToLocalRotationX (spBone* self);
    float spBone_worldToLocalRotationY (spBone* self);
    void spBone_rotateWorld (spBone* self, float degrees);
    void spBone_updateAppliedTransform (spBone* self);
    
    void spBone_worldToLocal (spBone* self, float worldX, float worldY, float* localX, float* localY);
    void spBone_localToWorld (spBone* self, float localX, float localY, float* worldX, float* worldY);
    
};

#endif /* bones_hpp */
