/**
 * @file
 *
 * Implementations for an sidereus.
 *
 * SIDEREUS - Astronomy Librarie
 *
 * Copyright (c) 2009 Ederson de Moura
 *
 * @author Ederson de Moura
 *
 * $Id: Exp$
 */

#ifndef SIDEREUS_SIDEREUS_HPP
#define SIDEREUS_SIDEREUS_HPP

#include <string>

namespace sidereus {
  /**
   * Class Sidereus Library.
   */
  class library {
  public:
    /**
     * Destructor.
     */
    virtual ~library();

    /**
     * Get library version string.
     *
     * @return Library version string.
     */
    static const char* version();

  private:
    /**
     * Private Constructor.
     */ 
    library();
  };

/**
 * This namespace works as if anything inside it were declared
 * staticaly in each source file.
 */
namespace {
}

}

#endif // SIDEREUS_SIDEREUS_HPP
