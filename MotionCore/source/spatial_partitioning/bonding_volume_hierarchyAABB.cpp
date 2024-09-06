#include "spatial_partitioning/bonding_volume_hierarchyAABB.h"

using namespace MotionCore;

Node::Node(const Node* _parent, void* _objectPtr, const AABB& _boundingAABB) : objectPtr(_objectPtr), aabb(_boundingAABB)
{
    
}



bool Node::IsLeaf() const
{
    return objectPtr != nullptr;
}

void Node::InsertObject(ObjectWithBoundingVolume* _object)
{
    if (IsLeaf())
    {
        childs[0] = new Node();
        childs[1] = new Node();
        objectPtr = nullptr;
        
        aabb.GetGrowVolume(_object->boundingAABB);
    }
    else
    {
        const numeric child1V = childs[0]->aabb.GetGrowVolume(_object->boundingAABB);
        const numeric child2V = childs[1]->aabb.GetGrowVolume(_object->boundingAABB);

        if (child1V < child2V)
        {
            childs[0]->InsertObject(_object);
        }
        else
        {
            childs[1]->InsertObject(_object);
        }
    }
}

void Node::ReComputeVolume()
{
    for (size_t i = 0; i < 2; i++)
        aabb.GrowToInclude(childs[i]->aabb);
}

uint32_t Node::GetPotentialContactsWith(const Node& _node, PotentialContact* _contacts, uint32_t limits)
{
    if (aabb.Overlaps(_node.aabb) || limits == 0)
        return 0;

    if (IsLeaf() && _node.IsLeaf())
    {
        _contacts->objectPtr[0] = objectPtr;
        _contacts->objectPtr[1] = _node.objectPtr;
        return 1;
    }

    if(_node.IsLeaf() ||(!IsLeaf() && aabb.GetArea() >= _node.aabb.GetArea()))
    {
        const uint32_t count = childs[0]->GetPotentialContactsWith(_node, _contacts, limits);

        if (limits > count)
        {
            return count + childs[1]->GetPotentialContactsWith(_node, _contacts, limits - count);
        }
        else
        {
            return count;
        }
    }
    else
    {
        const uint32_t count = childs[0]->GetPotentialContactsWith(*_node.childs[0], _contacts, limits);
        if (limits > count)
        {
            return count + GetPotentialContactsWith(*_node.childs[1],_contacts, limits - count); 
        }
        else
        {
            return count;
        }
    }
}

uint32_t Node::GetPotentialContact(PotentialContact* _contacts, uint32_t limits)
{
    if (IsLeaf() || limits == 0)
        return 0;

    return childs[0]->GetPotentialContactsWith(*childs[1], _contacts, limits);
}

void Node::Remove()
{
    if (parent != nullptr)
    {
        Node* sibling = nullptr;

        if (parent->childs[0] == this)
        {
            sibling = parent->childs[1];
        }
        else
        {
            sibling = parent->childs[0];
        }

        // Write sibling info to parent
        for (size_t i = 0; i < 2; i++)
        {
            parent->childs[i] = sibling->childs[i];
        }
        parent->objectPtr = sibling->parent;
        parent->aabb = sibling->aabb;

        sibling->parent = nullptr;
        sibling->childs[0] = nullptr;
        sibling->childs[1] = nullptr;
        sibling->objectPtr = nullptr;
        delete sibling;
    }

    if (childs[0] != nullptr)
    {
        childs[0]->parent = nullptr;
        delete childs[0];
    }

    if (childs[1] != nullptr)
    {
        childs[1]->parent = nullptr;
        delete childs[1];
    }
}

void BoundingVolumeHierarchyAABB::Insert(ObjectWithBoundingVolume* object)
{
   root.InsertObject(object);
}



void BoundingVolumeHierarchyAABB::ClearNode(Node* _node)
{
    if (_node->IsLeaf())
    {
        _node->objectPtr = nullptr;
    }
    _node->aabb = {};
    
    for (size_t i = 0; i < 2; i++)
    {
        if (_node->childs[i] != nullptr)
        {
            ClearNode(_node->childs[i]);
        }
    }
}

void BoundingVolumeHierarchyAABB::Clear()
{
    ClearNode(&root);
}

BoundingVolumeHierarchyAABB::BoundingVolumeHierarchyAABB()
{
}

BoundingVolumeHierarchyAABB::~BoundingVolumeHierarchyAABB()
{
}
