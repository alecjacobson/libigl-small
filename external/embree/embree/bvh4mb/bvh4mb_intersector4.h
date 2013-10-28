// ======================================================================== //
// Copyright 2009-2013 Intel Corporation                                    //
//                                                                          //
// Licensed under the Apache License, Version 2.0 (the "License");          //
// you may not use this file except in compliance with the License.         //
// You may obtain a copy of the License at                                  //
//                                                                          //
//     http://www.apache.org/licenses/LICENSE-2.0                           //
//                                                                          //
// Unless required by applicable law or agreed to in writing, software      //
// distributed under the License is distributed on an "AS IS" BASIS,        //
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. //
// See the License for the specific language governing permissions and      //
// limitations under the License.                                           //
// ======================================================================== //

#ifndef __EMBREE_BVH4MB_INTERSECTOR4_CHUNK_H__
#define __EMBREE_BVH4MB_INTERSECTOR4_CHUNK_H__

#include "bvh4mb.h"
#include "../include/intersector4.h"

namespace embree
{
  /*! BVH4MB Traverser. Packet traversal implementation for a Quad BVH. */
  template<typename TriangleIntersector>
    class BVH4MBIntersector4Chunk : public Intersector4
  {
    /* shortcuts for frequently used types */
    typedef typename TriangleIntersector::Triangle Triangle;
    typedef typename BVH4MB::Base Base;
    typedef typename BVH4MB::Node Node;

  public:
    BVH4MBIntersector4Chunk (const BVH4MB* bvh) 
      : Intersector4((intersectFunc)intersect,(occludedFunc)occluded), bvh(bvh) {}

    static Intersector4* create(const Accel* bvh) { 
      return new BVH4MBIntersector4Chunk((const BVH4MB*)bvh); 
    }

    static   void intersect(const BVH4MBIntersector4Chunk* This, Ray4& ray, const __m128 valid);
    static __m128 occluded (const BVH4MBIntersector4Chunk* This, Ray4& ray, const __m128 valid);

  private:
    const BVH4MB* bvh;

  };
}

#endif
