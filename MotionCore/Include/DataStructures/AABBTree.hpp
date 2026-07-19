#pragma once

#include <memory>
#include <algorithm>
#include <numeric>
#include <random>
#include <stack>

#include "MotionCoreHeader.h"
#include "Core/MotionCoreAllocator.hpp"
#include <Primitive/AABB.hpp>

namespace MotionCore
{
    using NodeIndex = uint32_t;
    using ObjectIndex = uint32_t;
    
    constexpr static NodeIndex NullNodeIndex = std::numeric_limits<size_t>::max();

    struct ObjectBounded
    {
        ObjectIndex objectIndex;
        NodeIndex nodeIndex;
        Aabb<numeric> aabb;
    };
    using NodeFuncIteration = void(*)(ObjectBounded objectBounded, uint32_t depth, void* userData);

    
    template <size_t _NodeCount>
    class AABBTree
    {
    public:
        //static_assert(_NodeCount < std::numeric_limits<size_t>::max(), "NodeCount must be lower than std::numeric_limits<size_t>::max");

        void UpdateObjects(ObjectBounded* _objectBoundedArray, size_t _objectBoundedArraySize);

        void Remove(NodeIndex _nodeIndex);

        void ForEachNode(NodeFuncIteration nodeFuncIteration);

        //OVERLOAD_MEMORY_OPERATOR(AABBTree);

        AABBTree();

        ~AABBTree() = default;
    
    private:
        struct Node
        {
            NodeIndex parentIndex;
            NodeIndex left;
            NodeIndex right;
            Aabb<numeric> bound;
           
            //OVERLOAD_MEMORY_OPERATOR(Node)
        };

        NodeIndex FoundAvailableNode();

        NodeIndex InsertObject(ObjectBounded* _object, numeric _objectSurfaceArea);

        NodeIndex FindBestSibling(ObjectBounded* _object) const;

        std::unique_ptr<Node[]> m_Nodes;

        NodeIndex m_RootIndex;

        std::array<uint32_t, _NodeCount> randomeIndiciesArray;
    };


    template <size_t _NodeCount>
    void AABBTree<_NodeCount>::UpdateObjects(ObjectBounded* _objectBoundedArray, size_t _objectBoundedArraySize)
    {
        
    }

    template<size_t _NodeCount>
    inline void AABBTree<_NodeCount>::Remove(NodeIndex _nodeIndex)
    {
    }

    template<size_t _NodeCount>
    inline void AABBTree<_NodeCount>::ForEachNode(NodeFuncIteration nodeFuncIteration)
    {
        std::stack<NodeIndex> nodeIndexStack;
        

    }

    template <size_t _NodeCount>
    AABBTree<_NodeCount>::AABBTree()
    {
        Node* nodeBegin = m_Nodes.get();
        for (size_t i = 0; i < _NodeCount; i++)
        {
            const Node* n = nodeBegin[i];
            n->objectIndex = NullNodeIndex;
        }
    }

    template<size_t _NodeCount>
    inline NodeIndex AABBTree<_NodeCount>::FoundAvailableNode()
    {
        Node* nodeBegin = m_Nodes.get();

        for (size_t i = 0; i < _NodeCount; i++)
        {
            const Node* n = nodeBegin[i];
            if (n->objectIndex == NullNodeIndex)
                return i;
        }
        
        return NullNodeIndex;
    }

    template<size_t _NodeCount>
    inline NodeIndex AABBTree<_NodeCount>::InsertObject(ObjectBounded* _object, numeric _objectSurfaceArea)
    {
        return NodeIndex{};
    }

    template<size_t _NodeCount>
    inline NodeIndex AABBTree<_NodeCount>::FindBestSibling(ObjectBounded* _object) const
    {
        return NodeIndex{};
    }

}


#include "DataStructures/AABBTree.inl"