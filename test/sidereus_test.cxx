/**
 * @file
 *
 * Tests for an sidereus class.
 *
 * SIDEREUS
 *
 * Copyright (c) 2009 Ederson de Moura
 *
 * @author Ederson de Moura
 *
 * @mainteiner: ederbsd@gmail.com
 *
 * $Id: Exp$
 */

#include <sidereus/sidereus.hxx>

#include <genesis/logger.hxx>

int main( int argc, char* argv[] ) 
{
  GEN_MSG( sidereus::library::version() );

  return 0;
}
