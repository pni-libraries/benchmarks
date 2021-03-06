//
// (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpniutils.
//
// libpniutils is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpniutils is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpniutils.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
//  Created on: Feb 19, 2013
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/core/types.hpp>
#include "../common/data_generator.hpp"

template<typename ATYPE> class BinaryArithmeticBenchmark
{
  private:
    using ArrayType = ATYPE;
    pni::core::shape_t _shape;
    ArrayType _a;
    ArrayType _b;
    ArrayType _c;
    ArrayType _d;
    ArrayType _e;
    ArrayType _f;
  public:
    BinaryArithmeticBenchmark(const pni::core::shape_t &s):
      _shape(s)
  {
  }

    void allocate()
    {
      using ValueType = typename ArrayType::value_type;


      deallocate();

      _a = ArrayType::create(_shape);
      _b = ArrayType::create(_shape);
      _c = ArrayType::create(_shape);
      _d = ArrayType::create(_shape);
      _e = ArrayType::create(_shape);
      _f = ArrayType::create(_shape);

      std::generate(_a.begin(),_a.end(),RandomGenerator<ValueType>());
      std::generate(_b.begin(),_b.end(),RandomGenerator<ValueType>());
      std::generate(_c.begin(),_c.end(),RandomGenerator<ValueType>());
      std::generate(_d.begin(),_d.end(),RandomGenerator<ValueType>());
      std::generate(_e.begin(),_e.end(),RandomGenerator<ValueType>());
      std::generate(_f.begin(),_f.end(),RandomGenerator<ValueType>());

    }

    void deallocate()
    {
      _a = ArrayType();
      _b = ArrayType();
      _c = ArrayType();
      _d = ArrayType();
      _e = ArrayType();
      _f = ArrayType();
    }

    void add() { _c = _a + _b; }

    void sub() { _c = _a - _b; }


    void mult() { _c = _a * _b; }

    void div() { _c= _a/_b; }

    void all() { _c = (_a*_b) + (_d-_e)/_f; }

};
