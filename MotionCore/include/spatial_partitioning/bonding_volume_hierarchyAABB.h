#pragma once

#include "spatial_partitioning_typedef.h"

namespace MotionCore
{
    struct PotentialContact
    {
        void* objectPtr[2] = { nullptr, nullptr};
    };
    
    
    struct ObjectWithBoundingVolume
    {
        void* objectPtr = nullptr;
        AABB boundingAABB;
    };

   
    class Node
    {
    public:
        void* objectPtr = nullptr;
        Node* parent = nullptr;
        Node* childs[2] = {nullptr, nullptr};
        AABB aabb;
        
        Node(const Node* _parent, void* _objectPtr, const AABB& _boundingAABB);
        
        Node() = default;
        
        ~Node() = default;

        bool IsLeaf() const;

        void InsertObject(ObjectWithBoundingVolume* _object);

        void ReComputeVolume();

        uint32_t GetPotentialContactsWith(const Node& _node, PotentialContact* _contacts, uint32_t limits);

        uint32_t GetPotentialContact(PotentialContact* _contacts, uint32_t limits);

    private:
        void Remove();
    };

  
    
    class BoundingVolumeHierarchyAABB
    {
    public:
        void Insert(ObjectWithBoundingVolume* _object);
        
        void Clear();
        
        BoundingVolumeHierarchyAABB();

        ~BoundingVolumeHierarchyAABB();
    
    private:
        Node root;
        
        void ClearNode(Node* _node);
        
    };

}
