/* Adapted from David R. Cheriton's Advanced Object Oriented Programming from a 
  Modeling & Simulation's Perspective ~ Chapter 5: Memory management with smart
  pointers. */

#ifndef PTRINTERFACE_H_VGPMQRTI
#define PTRINTERFACE_H_VGPMQRTI

/* stl includes */
#include <string>

#include "exception.h"
#include "ptr.h"

namespace Simone {

template <typename T>
class PtrInterface {
  friend class Ptr<T>;
public:
  unsigned long references() const {
    return ref_;
  }
  
  virtual const PtrInterface * newRef() const {
    ++ref_;
    return this;
  }
  
  virtual const PtrInterface * deleteRef() const {
    if (ref_ == 0) {
      string msg = "attempt to delete an object with zero references";
      throw MemoryException(__FILE__, __LINE__, msg);
    }
    if( --ref_ == 0 ) {
      onZeroReferences();
      return 0;
    }
    return this;
  }
  
  /* allow use with Simone::ConcurrentCollection */
  template <typename Collection>
  void collectionIs(Collection *_c) const {}
protected:
  PtrInterface() : ref_(0) {}
  virtual ~PtrInterface() {}
  virtual void onZeroReferences() const { delete this; }
  
  mutable unsigned long ref_;
};

}

#endif
