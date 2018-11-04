#ifndef valkkafs_HEADER_GUARD
#define valkkafs_HEADER_GUARD
/*
 * valkkafs.h :
 * 
 * Copyright 2017, 2018 Valkka Security Ltd. and Sampsa Riikonen.
 * 
 * Authors: Sampsa Riikonen <sampsa.riikonen@iki.fi>
 * 
 * This file is part of the Valkka library.
 * 
 * Valkka is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>
 *
 */

/** 
 *  @file    valkkafs.h
 *  @author  Sampsa Riikonen
 *  @date    2017
 *  @version 0.8.0 
 *  
 *  @brief
 */ 

#include "thread.h"

#include "Python.h"
#include "numpy/ndarraytypes.h"
#include "numpy/arrayobject.h"

/*
#include "boost/python/numpy.hpp"
namespace p = boost::python;
namespace np = boost::python::numpy;
// https://www.boost.org/doc/libs/1_64_0/libs/python/doc/html/numpy/reference/ndarray.html
// https://github.com/ndarray/Boost.NumPy/blob/master/libs/numpy/example/simple.cpp
*/

/** Book-keeping for ValkkaFS
 * 
 * @param device_file   File where payload is written.  Can be /dev/sdb etc., or just a plain file with some space reserved
 * @param block_file    Book-keeping of the blocks in the device file
 * @param blocksize     Size of a single block in bytes
 * @param device_size   Size of the device (or the part we want to use) in bytes
 * 
 */
class ValkkaFS {        // <pyapi>

public:                 // <pyapi>
    ValkkaFS(const char *device_file, const char *block_file, long int blocksize, long int n_blocks); // <pyapi>
    ~ValkkaFS();        // <pyapi>

protected:
    std::string     device_file;
    std::string     block_file;
    long int        blocksize;
    long int        n_blocks;
    PyArray_Descr  *descr;
    PyArrayObject   *arr;
    // np::ndarray     *py_array;
    
    /*
    getMinTime
    getMaxTime
    getMinBlock
    getMaxBlock
    
    writeBlock      
    newBlock
    
    markFrame               Used by cpp class that writes the filesystem
    markKeyFrame            (same)

    ** Python API **
    */
    
public:
    PyObject *getNumpyArrayCall();  // <pyapi>       Returns a numpy array copy of the blocktable
    
};                                  // <pyapi>


class ValkkaFSWriterThread : public Thread {

public:
    ValkkaFSWriterThread(const char *name, ValkkaFS &valkkafs);
    ~ValkkaFSWriterThread();
    
private:
    ValkkaFS    &valkkafs;
    
    
    /*
    setSlotId(slot, id)     Defines an id for a certain slot
    getFilter               Gives the terminal FrameFilter for writing

    **Python API**
    
    setSlotIdCall(slot, id)
    getFilter
    */
    
};


class ValkkaFSReaderThread : public Thread {
    
public:
    ValkkaFSReaderThread(const char *name, ValkkaFS &valkkafs);
    ~ValkkaFSReaderThread();

private:
    ValkkaFS    &valkkafs;
    
    
    /*
    ValkkaFSReadThread(ValkkaFS valkkafs) / or "ValkkaFSDumpThread"

    pullBlocks(std::list)     Dump all blocks in the list to output filters
    
    **Python API**
    
    getValkkaFS()
    pullBlocksCall(PyObject)
    RegisterOutputCall(context with id and cam id)
    deRegisterOutputCall(cam id)
    
    ? put here playCall, seekCall, etc.
    =>
    */
};
    


#endif
