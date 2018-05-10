/* A 'string set' is defined as a set of strings stored
 * in a hashtable that uses chaining to resolve collisions.
 *
 * Peter Jensen
 * January 30, 2018
 */

#ifndef STRING_SET_H
#define STRING_SET_H

#include "node.h"
#include <vector>
int main();
namespace cs3505
{
  
  class string_set
    {
      friend int ::main();
      // Default visibility is private. 
      int capacity;  // The size of the hashtable array
      int count;     // The number of elements in the set
      node** table;  // The hashtable, a pointer to a node pointer
                     //   (which will really be an array of node pointers)

    public:
      string_set(int capacity = 100);        // Constructor.  Notice the default parameter value.
      string_set(const string_set & other);  // Copy constructor
      ~string_set();                         // Destructor
      
      void add      (const std::string & element);        // Not const - modifies the object
      void remove   (const std::string & element);        // Not const - modifies the object
      bool contains (const std::string & element) const;  // Const - does not change the object
      int  size     () const;                             // Const - does not change object

      string_set & operator= (const string_set & rhs);    // Not const - modifies this object

    /** This function populates and returns a std::vector<std::string>
    * with elements from this set.  The elements in the vector will be in the
    * same order as the natural ordering in this hashtable (table[0] first, etc.).
    * The size of the vector will be exactly equal to the element count
    * in this hashtable.
    */
    std::vector<std::string> get_elements() const;

    private:
      int  hash (const std::string & s) const;            // Const - does not change this object
      void clean ();                                      // Not const - modifies the object

      // Below are a few definitions that I use to make sure I am cleaning
      //   up memory properly.  (Notice that I can switch back to public / private
      //   as many times as I like.)  These are not part of a normal
      //   hashtable, but they are here because they help with debugging.
      // These functions and variables are declared static - they exist in the
      //   class, but not in any particular object.  (The objects can access
      //   them, of course.)
      
    public:
      static long long constructor_count ();  // A debugging function
      static long long destructor_count ();   // A debugging function
      
    private:
      static long long constructor_calls;  // A debugging variable
      static long long destructor_calls;   // A debugging variable

  };

}

#endif
