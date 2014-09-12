// this is for emacs file handling -*- mode: c++; indent-tabs-mode: nil -*-

// -- BEGIN LICENSE BLOCK ----------------------------------------------
// This file is part of the GPU Voxels Software Library.
//
// This program is free software licensed under the CDDL
// (COMMON DEVELOPMENT AND DISTRIBUTION LICENSE Version 1.0).
// You can find a copy of this license in LICENSE.txt in the top
// directory of the source code.
//
// © Copyright 2014 FZI Forschungszentrum Informatik, Karlsruhe, Germany
//
// -- END LICENSE BLOCK ------------------------------------------------

//----------------------------------------------------------------------
/*!\file
 *
 * \author  Andreas Hermann
 * \date    2014-06-12
 *
 */
//----------------------------------------------------------------------
#include <gpu_voxels/helpers/pcd_handling.h>

namespace gpu_voxels {
namespace pcd_handling {

bool readPointCloud(const std::string filename, std::vector<Vector3f> &points)
{
  float x;
  float y;
  float z;
  std::string line;
  std::ifstream file(filename.c_str());

  if (!file)
  {
    LOGGING_ERROR(Gpu_voxels_helpers, "Could not open file " << filename.c_str() << " !" << endl);
    return false;
  }
  while (std::getline(file, line))
  {
    std::istringstream iss(line);
    Vector3f vec;
    // reads the float value from the file and adds the offset.
    while (iss >> x && iss >> y && iss >> z)
    {
      vec.x = x;
      vec.y = y;
      vec.z = z;
      points.push_back(vec);
    }
  }
  LOGGING_INFO(
      Gpu_voxels_helpers,
      "PCD Handler: loaded " << points.size() << " points ("<< (points.size()*sizeof(Vector3f))/1024.0/1024.0 << " MB on CPU) from "<< filename.c_str() << "." << endl);
  file.close();
  return true;
}



bool loadPointCloud(const std::string filename, std::vector<Vector3f> &points, const bool shift_to_zero,
                    const Vector3f &offset_XYZ)
{
  if (!readPointCloud(filename, points))
  {
    return false;
  }

  if (shift_to_zero)
  {
    shiftPointCloudToZero(points);
  }

  for (size_t i = 0; i < points.size(); i++)
  {
    points[i].x += offset_XYZ.x;
    points[i].y += offset_XYZ.y;
    points[i].z += offset_XYZ.z;
  }
  return true;
}

} // end of namespace
} // end of namespace