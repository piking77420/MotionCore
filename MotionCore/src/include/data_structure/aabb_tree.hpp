#pragma once

#include <memory>
#include <algorithm>
#include <numeric>
#include <random>
#include <stack>

#include "motion_core_header.h"
#include "core/motion_core_allocator.hpp"
#include "primitive/aabb.hpp"

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

        OVERLOAD_MEMORY_OPERATOR(AABBTree);

        AABBTree();

        ~AABBTree() = default;
    
    private:
        struct Node
        {
            NodeIndex parentIndex;
            NodeIndex left;
            NodeIndex right;
            Aabb<numeric> bound;
           
            OVERLOAD_MEMORY_OPERATOR(Node)
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
        assert(_objectBoundedArraySize < _NodeCount && "_objectBoundedArraySize is greater than nodeCount");

        // heuristic insert array

        // init random once
        static std::mt19937 randomGenerator;
                
        // fill the array of index
        std::iota(randomeIndiciesArray, randomeIndiciesArray.begin() + _objectBoundedArraySize, 0);
        // shuffle the array of indicies
        std::shuffle(randomeIndiciesArray, randomeIndiciesArray.begin() + _objectBoundedArraySize, randomGenerator);

        // insert all the object
        for (size_t i = 0; i < _objectBoundedArraySize; i++)
        {
            uint32_t randomIndex = randomeIndiciesArray[i];
            ObjectBounded* boundedObject = &_objectBoundedArray[randomIndex];
            const numeric surfaceArea = GetSurfaceArea(boundedObject->aabb);

            if (boundedObject->nodeIndex == NullNodeIndex)
            {
                boundedObject->nodeIndex = InsertObject(boundedObject);
            }
            else
            {
                const Aabb<numeric>& objectNodeBound = m_Nodes.get()[boundedObject->nodeIndex]->bound;
                
                // if objectNodeBound contain boundedObject;
                // is ok proceed next one
                // if not remove and insert it 

                if (Countain(boundedObject->aabb, objectNodeBound)) continue;

                // TO DO REMOVE
                boundedObject->nodeIndex = InsertObject(boundedObject);
            }
        }
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
        assert(_object != nullptr, "Ptr is null");

        NodeIndex n = FoundAvailableNode();
        Node* node = m_Nodes.get()[n];

       

        return n;
    }

    template<size_t _NodeCount>
    inline NodeIndex AABBTree<_NodeCount>::FindBestSibling(ObjectBounded* _object) const
    {


    }

}


#include "data_structure/aabb_tree.inl"