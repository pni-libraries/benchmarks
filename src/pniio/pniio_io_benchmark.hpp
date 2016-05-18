//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpniio.
//
// libpniio is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpniio is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
// Created on: Jan 05, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>
#include "file_io_benchmark.hpp"

#include <pni/io/nx/nx.hpp>

#include "../common/data_generator.hpp"

using namespace pni::core;
using namespace pni::io::nx::h5;

template<typename T> class pniio_io_benchmark : public file_io_benchmark
{
    public:
        typedef dynamic_array<T> array_type;
        typedef random_generator<T> data_generator_type;
    private:
        //! array holding the buffer for the frame data
        array_type _frame_buffer; 
        nxfield    _field;
        nxfile     _file;
    public:
        //===================constructors and destructor=======================
        //! default constructor
        pniio_io_benchmark():
            file_io_benchmark(),
            _frame_buffer()
        {}

        //======================public member functions========================
        //! create data structures
        virtual void create();
        virtual void close();

        //---------------------------------------------------------------------
        //! run the benchmark
        virtual void run() ;

};

//-----------------------------------------------------------------------------
template<typename T> void pniio_io_benchmark<T>::create()
{
    //create data 
    shape_t shape{nx(),ny()};
    _frame_buffer = array_type::create(shape);

    std::generate(_frame_buffer.begin(),_frame_buffer.end(),
                  data_generator_type());

    //create the file
    if(split_size())
    {
        _file = nxfile::create_files(filename(),true,split_size());
    }
    else
    {
        _file = nxfile::create_file(filename(),true);
    }

    shape_t s{0,nx(),ny()};
    shape_t cs{1,nx(),ny()};
    nxgroup root = _file.root();
    _field = root.template create_field<T>("data",s,cs);
}

//-----------------------------------------------------------------------------
template<typename T> void pniio_io_benchmark<T>::close()
{
    _field.close();
    _file.close();
}


//-----------------------------------------------------------------------------
template<typename T> void pniio_io_benchmark<T>::run() 
{
    for(size_t n = 0; n<nframes();n++)
    {
        _field.grow(0);
        _field(n,slice(0,nx()),slice(0,ny())).write(_frame_buffer);
        _file.flush();
    }
}
