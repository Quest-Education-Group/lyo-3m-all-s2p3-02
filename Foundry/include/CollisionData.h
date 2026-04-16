#ifndef FOUNDRY_COLLISIONDATA__H_
#define FOUNDRY_COLLISIONDATA__H_

struct CollisionData
{
    void* pNode;
    enum type { RIGIDBODY, TRIGGER } type;
};

#endif