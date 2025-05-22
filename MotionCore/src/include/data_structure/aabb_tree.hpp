#pragma once

#include <memory>

#include "motion_core_header.h"
#include "core/motion_core_allocator.hpp"
#include "primitive/aabb.hpp"

namespace MotionCore
{
   

    template <size_t _NodeCount>
    class AABBTree
    {
    public:
        static_assert(_NodeCount < std::std::numeric_limits<size_t>::max(), "NodeCount must be lower than std::numeric_limits<size_t>::max");
        
        using NodeIndex = size_t;
        using ObjectIndex = size_t;
        constexpr static NodeIndex NullNodeIndex = std::numeric_limits<size_t>::max();


        NodeIndex Insert(ObjectIndex _objectIndex, const Aabb<numeric>& _aabb);

        void Remove(NodeIndex _nodeIndex);

        const Aabb<numeric>& GetBound(NodeIndex _nodeIndex);

        OVERLOAD_MEMORY_OPERATOR(AABBTree);

        AABBTree();

        ~AABBTree();
    
    private:
        struct Node
        {
            size_t parentIndex;
            Aabb<numeric> aabb;
            ObjectIndex objectIndex;

            OVERLOAD_MEMORY_OPERATOR(Node)
        };

        NodeIndex AllocateNode();

        std::unique_ptr<Node[]> m_Nodes;
    };

 
}


#include "data_structure/aabb_tree.inl"