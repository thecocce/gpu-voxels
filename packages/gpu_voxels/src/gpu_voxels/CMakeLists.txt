# this is for emacs file handling -*- mode: cmake; indent-tabs-mode: nil -*-

# -- BEGIN LICENSE BLOCK ----------------------------------------------
# -- END LICENSE BLOCK ------------------------------------------------

#----------------------------------------------------------------------
#
# \author  Sebastian Klemm
# \date    2012-06-06
#
#----------------------------------------------------------------------

#------------- anounce basic libs ----------------------------
ADD_SUBDIRECTORY(logging)
ADD_SUBDIRECTORY(helpers)

#------------- gpu_voxels_core libaray -----------------------
ICMAKER_SET("gpu_voxels_core" IDE_FOLDER ${GPU_VOXELS_IDE_FOLDER})

ICMAKER_ADD_HEADERS(
  GpuVoxelsMap.h
  ManagedMap.h
  )

ICMAKER_ADD_SOURCES(
  GpuVoxelsMap.cpp
  )

ICMAKER_ADD_CUDA_FILES(
  octree/VoxelTypeFlags.h
  octree/DataTypes.h
  )
  


# removing unknown pragma warnings due to OpenNI spam
ICMAKER_LOCAL_CPPDEFINES(-DGPU_VOXELS_EXPORT_SYMBOLS -Wno-unknown-pragmas)
ICMAKER_GLOBAL_CPPDEFINES(-D_IC_BUILDER_GPU_VOXELS_)
ICMAKER_INCLUDE_DIRECTORIES(${GPU_VOXELS_INCLUDE_DIRS})

ICMAKER_INTERNAL_DEPENDENCIES(EXPORT
  icl_core
  icl_core_config
  icl_core_logging
  gpu_voxels_logging
  gpu_voxels_helpers
  )

ICMAKER_EXTERNAL_DEPENDENCIES(
  CUDA
  OpenNI
  Boost_SYSTEM
  PCL
  OpenNI
  )

ICMAKER_BUILD_LIBRARY()
ICMAKER_INSTALL_HEADERS(gpu_voxels)

#------------- anounce high level libs and tests ------------------
ADD_SUBDIRECTORY(robot)
ADD_SUBDIRECTORY(voxelmap)
ADD_SUBDIRECTORY(vis_interface)
ADD_SUBDIRECTORY(octree)

#------------- gpu_voxels library ---------------------------------
# This library resembles the high level interface to link against.
#------------------------------------------------------------------
ICMAKER_SET("gpu_voxels" IDE_FOLDER ${GPU_VOXELS_IDE_FOLDER})

ICMAKER_ADD_HEADERS(
  GpuVoxels.h
  )

ICMAKER_ADD_SOURCES(
  GpuVoxels.cpp
  )

ICMAKER_ADD_CUDA_FILES(
  )

# removing unknown pragma warnings due to OpenNI spam
ICMAKER_LOCAL_CPPDEFINES(-DGVL_EXPORT_SYMBOLS -Wno-unknown-pragmas)
ICMAKER_GLOBAL_CPPDEFINES(-D_IC_BUILDER_GPU_VOXELS_)
ICMAKER_INCLUDE_DIRECTORIES(${GPU_VOXELS_INCLUDE_DIRS})


ICMAKER_INTERNAL_DEPENDENCIES(EXPORT
  icl_core
  icl_core_config
  icl_core_logging
  gpu_voxels_core
  gpu_voxels_robot
  gpu_voxels_voxelmap
  gpu_voxels_octree
  gpu_voxels_vis_interface
  )

ICMAKER_EXTERNAL_DEPENDENCIES(
  CUDA
  OpenNI
  Boost_SYSTEM
  PCL
  OpenNI
  )

ICMAKER_BUILD_LIBRARY()
ICMAKER_INSTALL_HEADERS(gpu_voxels)

ADD_SUBDIRECTORY(test)
