//
// Created by XL1TTE on 29.11.2025.
//

#ifndef XLENGINE_IBEHAVIOUROBJECT_H
#define XLENGINE_IBEHAVIOUROBJECT_H

class IBehaviourObject
{
  public:
    virtual ~IBehaviourObject();

    virtual void Awake();
    virtual void Update();
    virtual void Render();
    virtual void Destroy();
};

#endif // XLENGINE_IBEHAVIOUROBJECT_H
