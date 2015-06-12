#ifndef MESH_BOOLEAN_TYPE_H
#define MESH_BOOLEAN_TYPE_H

namespace igl
{
  namespace boolean
  {
    enum MeshBooleanType
    {
      MESH_BOOLEAN_TYPE_UNION = 0,
      MESH_BOOLEAN_TYPE_INTERSECT = 1,
      MESH_BOOLEAN_TYPE_MINUS = 2,
      MESH_BOOLEAN_TYPE_XOR = 3,
      MESH_BOOLEAN_TYPE_RESOLVE = 4,
      NUM_MESH_BOOLEAN_TYPES = 5
    };
  }
};

#endif
