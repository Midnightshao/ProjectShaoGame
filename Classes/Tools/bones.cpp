//
//  bones.cpp
//  PojectShaoGame
//
//  Created by shao on 2018/5/10.
//

#include "bones.hpp"

static int yDown;

void bones::spBone_setYDown(int value){
    yDown = value;
}
int bones::spBone_isYDown () {
    return yDown;
}
bones *bones::spBone_create(spBoneData *data, struct spSkeleton *skeleton, spBone *parent){
    bones* self = NEW(bones);
    CONST_CAST(spBoneData*, self->data) = data;
    CONST_CAST(spSkeleton*, self->skeleton) = skeleton;
    CONST_CAST(spBone*, self->parent) = parent;
    self->spBone_setToSetupPose(self);
    
    return self;
};

void bones::spBone_setToSetupPose (spBone* self) {
    self->x = self->data->x;
    self->y = self->data->y;
    self->rotation = self->data->rotation;
    self->scaleX = self->data->scaleX;
    self->scaleY = self->data->scaleY;
    self->shearX = self->data->shearX;
    self->shearY = self->data->shearY;
}
void bones::spBone_rotateWorld(spBone *self, float degrees){
    float a = self->a, b = self->b, c = self->c, d = self->d;
    float cosine = COS_DEG(degrees), sine = SIN_DEG(degrees);
    CONST_CAST(float, self->a) = cosine * a - sine * c;
    CONST_CAST(float, self->b) = cosine * b - sine * d;
    CONST_CAST(float, self->c) = sine * a + cosine * c;
    CONST_CAST(float, self->d) = sine * b + cosine * d;
    CONST_CAST(int, self->appliedValid) = 1;
}
void bones::spBone_updateWorldTransform(spBone *self){
    spBone* parent = self->parent;
    self->appliedValid = 1;
    if (!parent) {
        self->ax = self->worldX;
        self->ay = self->worldY;
        self->arotation = ATAN2(self->c, self->a) * RAD_DEG;
        self->ascaleX = SQRT(self->a * self->a + self->c * self->c);
        self->ascaleY = SQRT(self->b * self->b + self->d * self->d);
        self->ashearX = 0;
        self->ashearY = ATAN2(self->a * self->b + self->c * self->d, self->a * self->d - self->b * self->c) * RAD_DEG;
    } else {
        float pa = parent->a, pb = parent->b, pc = parent->c, pd = parent->d;
        float pid = 1 / (pa * pd - pb * pc);
        float dx = self->worldX - parent->worldX, dy = self->worldY - parent->worldY;
        float ia = pid * pd;
        float id = pid * pa;
        float ib = pid * pb;
        float ic = pid * pc;
        float ra = ia * self->a - ib * self->c;
        float rb = ia * self->b - ib * self->d;
        float rc = id * self->c - ic * self->a;
        float rd = id * self->d - ic * self->b;
        self->ax = (dx * pd * pid - dy * pb * pid);
        self->ay = (dy * pa * pid - dx * pc * pid);
        self->ashearX = 0;
        self->ascaleX = SQRT(ra * ra + rc * rc);
        if (self->ascaleX > 0.0001f) {
            float det = ra * rd - rb * rc;
            self->ascaleY = det / self->ascaleX;
            self->ashearY = ATAN2(ra * rb + rc * rd, det) * RAD_DEG;
            self->arotation = ATAN2(rc, ra) * RAD_DEG;
        } else {
            self->ascaleX = 0;
            self->ascaleY = SQRT(rb * rb + rd * rd);
            self->ashearY = 0;
            self->arotation = 90 - ATAN2(rd, rb) * RAD_DEG;
        }
    }
}
void bones::spBone_updateAppliedTransform(spBone *self){
    spBone* parent = self->parent;
    self->appliedValid = 1;
    if (!parent) {
        self->ax = self->worldX;
        self->ay = self->worldY;
        self->arotation = ATAN2(self->c, self->a) * RAD_DEG;
        self->ascaleX = SQRT(self->a * self->a + self->c * self->c);
        self->ascaleY = SQRT(self->b * self->b + self->d * self->d);
        self->ashearX = 0;
        self->ashearY = ATAN2(self->a * self->b + self->c * self->d, self->a * self->d - self->b * self->c) * RAD_DEG;
    } else {
        float pa = parent->a, pb = parent->b, pc = parent->c, pd = parent->d;
        float pid = 1 / (pa * pd - pb * pc);
        float dx = self->worldX - parent->worldX, dy = self->worldY - parent->worldY;
        float ia = pid * pd;
        float id = pid * pa;
        float ib = pid * pb;
        float ic = pid * pc;
        float ra = ia * self->a - ib * self->c;
        float rb = ia * self->b - ib * self->d;
        float rc = id * self->c - ic * self->a;
        float rd = id * self->d - ic * self->b;
        self->ax = (dx * pd * pid - dy * pb * pid);
        self->ay = (dy * pa * pid - dx * pc * pid);
        self->ashearX = 0;
        self->ascaleX = SQRT(ra * ra + rc * rc);
        if (self->ascaleX > 0.0001f) {
            float det = ra * rd - rb * rc;
            self->ascaleY = det / self->ascaleX;
            self->ashearY = ATAN2(ra * rb + rc * rd, det) * RAD_DEG;
            self->arotation = ATAN2(rc, ra) * RAD_DEG;
        } else {
            self->ascaleX = 0;
            self->ascaleY = SQRT(rb * rb + rd * rd);
            self->ashearY = 0;
            self->arotation = 90 - ATAN2(rd, rb) * RAD_DEG;
        }
    }
}
