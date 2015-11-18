/**
 * @file
 *
 * Definitions for an sidereus.
 *
 * SIDEREUS - Astronomy Librarie
 *
 * Copyright (c) 2009 Ederson de Moura
 *
 * @author Ederson de Moura
 *
 * $Id: Exp$
 */

#include <sidereus/sidereus.hxx>

#include <genesis/logger.hxx>
#include <genesis/string_util.hxx>

#include <iostream>
#include <cstdio>
#include <algorithm>

namespace sidereus {

  library::library()
  {
  }

  library::~library()
  {
  }

  const char* library::version()
  {
    static std::string v( genesis::string_util::to_uppercase( PACKAGE ) +
                          ", Version " VERSION + "\n" +
                          "Copyright 2009-2015 "
                          "Ederson de Moura" );

    return v.c_str();
  }

}
