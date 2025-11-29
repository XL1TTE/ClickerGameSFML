//
// Created by XL1TTE on 29.11.2025.
//

#ifndef CLICKER_IBEHAVIOUROBJECT_H
#define CLICKER_IBEHAVIOUROBJECT_H

class IBehaviourObject
{
  public:
    virtual ~IBehaviourObject();

    virtual void Awake();
    virtual void Update();
    virtual void Render();
    virtual void Destroy();
};

#endif // CLICKER_IBEHAVIOUROBJECT_H
