//StiKTNIterator.h
//M.L. Miller (Yale Software)
//12/01

/*! \class StiKTNIterator
  This class is an STL compliant forward iterator that will traverse from
  the leaf of a tree upward to a root.

  \author M.L. Miller (Yale Software)
  \note We use the defualt copy/assignment generated by compiler.
  \note Singularity (i.e., 'end') is represented by setting mNode=0.
  \note StiKTNIterator is a non-virtual class.
*/

#ifndef StiKTNIterator_HH
#define StiKTNIterator_HH
#ifdef GNU_GCC
  #if __GNUC__<3
    #define HACK_forward_iterator
  #endif
#endif

#include <iterator>
using namespace std;

#include "StiKalmanTrackNode.h"
typedef StiKalmanTrackNode KTN_t;

//This is a temp hack to get around old gcc ansi-non-compliant STL implementation
class StiKTNForwardIterator
#ifndef HACK_forward_iterator
    : public iterator<forward_iterator_tag, KTN_t, ptrdiff_t, KTN_t*, KTN_t&>
#else
    : public forward_iterator<KTN_t, int>
#endif
{
public:
    
public:
    ///ctr-dstr
    StiKTNForwardIterator() : mNode(0) {};
    StiKTNForwardIterator(StiKalmanTrackNode* leaf) : mNode(leaf) {};
    StiKTNForwardIterator(StiKalmanTrackNode& leaf) : mNode(&leaf) {};
    ~StiKTNForwardIterator() {};

    ///equality:
    bool operator==(const StiKTNForwardIterator& rhs);

    ///inequlity
    bool operator!=(const StiKTNForwardIterator& rhs);

    ////Dereference
    StiKalmanTrackNode& operator*();
    
    ///prefix
    StiKTNForwardIterator& operator++ ();
    
    ///postfix
    StiKTNForwardIterator operator++(int);

    ///We demarcate the end of the traversal via  a singular iterator
    StiKTNForwardIterator end();

private:
    StiKalmanTrackNode* mNode;
};

//inlines --

inline bool StiKTNForwardIterator::operator==(const StiKTNForwardIterator& rhs)
{
    return mNode==rhs.mNode;
}

inline bool StiKTNForwardIterator::operator!=(const StiKTNForwardIterator& rhs)
{
    return !(mNode==rhs.mNode);
}

inline StiKalmanTrackNode& StiKTNForwardIterator::operator*()
{
    return *mNode;
}

//prefix
/*! In the case where the prefix operator increments beyond the root of the tree,
  the pointer to mNode is set to 0.   This demarcates the end of the traversal.
 */
inline StiKTNForwardIterator& StiKTNForwardIterator::operator++ ()
{
    if (mNode->isRoot() ) {
	mNode=0;
    }
    else {
	mNode = static_cast<StiKalmanTrackNode*>(mNode->getParent());
    }
    return *this;
}
    

//postfix
/*! In the case where the prefix operator increments beyond the root of the tree,
  the pointer to mNode is set to 0.   This demarcates the end of the traversal.
*/
inline StiKTNForwardIterator StiKTNForwardIterator::operator++(int)
{
    StiKTNForwardIterator temp = *this;
    ++(*this);
    return temp;
}

inline StiKTNForwardIterator StiKTNForwardIterator::end()
{
    return StiKTNForwardIterator(0);
}


//This is a temp hack to get around old gcc ansi-non-compliant STL implementation
class StiKTNBidirectionalIterator
#ifndef HACK_forward_iterator
    : public iterator<bidirectional_iterator_tag, KTN_t, ptrdiff_t, KTN_t*, KTN_t&>
#else
    : public bidirectional_iterator<KTN_t, int>
#endif
{
public:
    
public:
    ///ctr-dstr
    StiKTNBidirectionalIterator() : mNode(0) {};
    StiKTNBidirectionalIterator(StiKalmanTrackNode* leaf) : mNode(leaf) {};
    StiKTNBidirectionalIterator(StiKalmanTrackNode& leaf) : mNode(&leaf) {};
    ~StiKTNBidirectionalIterator() {};

    ///equality:
    bool operator==(const StiKTNBidirectionalIterator& rhs);

    ///inequlity
    bool operator!=(const StiKTNBidirectionalIterator& rhs);

    ////Dereference
    StiKalmanTrackNode& operator*();
    
    ///prefix
    StiKTNBidirectionalIterator& operator++ ();
    
    ///postfix
    StiKTNBidirectionalIterator operator++(int);

    ///prefix
    StiKTNBidirectionalIterator& operator-- ();
    
    ///postfix
    StiKTNBidirectionalIterator operator--(int);

    ///We demarcate the end of the traversal via  a singular iterator
    StiKTNBidirectionalIterator end();

private:
    StiKalmanTrackNode* mNode;
};

//inlines --

inline bool StiKTNBidirectionalIterator::operator==(const StiKTNBidirectionalIterator& rhs)
{
    return mNode==rhs.mNode;
}

inline bool StiKTNBidirectionalIterator::operator!=(const StiKTNBidirectionalIterator& rhs)
{
    return !(mNode==rhs.mNode);
}

inline StiKalmanTrackNode& StiKTNBidirectionalIterator::operator*()
{
    return *mNode;
}

//prefix
/*! In the case where the prefix operator increments beyond the root of the tree,
  the pointer to mNode is set to 0.   This demarcates the end of the traversal.
 */
//inline StiKTNBidirectionalIterator& StiKTNBidirectionalIterator::operator++ ()
inline StiKTNBidirectionalIterator& StiKTNBidirectionalIterator::operator-- ()
{
    if (mNode->isRoot() ) {
	mNode=0;
    }
    else {
	mNode = static_cast<StiKalmanTrackNode*>(mNode->getParent());
    }
    return *this;
}
    

//postfix
/*! In the case where the prefix operator increments beyond the root of the tree,
  the pointer to mNode is set to 0.   This demarcates the end of the traversal.
*/
inline StiKTNBidirectionalIterator StiKTNBidirectionalIterator::operator++(int)
{
    StiKTNBidirectionalIterator temp = *this;
    ++(*this);
    return temp;
}

//prefix
/*! In the case where the prefix operator increments beyond the last leaf of the tree,
  the pointer to mNode is set to -.  This demarcates the end of traversal.
*/
//inline StiKTNBidirectionalIterator& StiKTNBidirectionalIterator::operator-- ()
inline StiKTNBidirectionalIterator& StiKTNBidirectionalIterator::operator++ ()
{
    if (mNode->isLeaf() ) {
	mNode=0;
    }
    else {
	mNode = static_cast<StiKalmanTrackNode*>(mNode->getFirstChild());
    }
    return *this;
}

//postfix decrement
/*! In the case where the prefix operator increments beyond the root of the tree,
  the pointer to mNode is set to 0.   This demarcates the end of the traversal.
*/
inline StiKTNBidirectionalIterator StiKTNBidirectionalIterator::operator--(int)
{
    StiKTNBidirectionalIterator temp = *this;
    --(*this);
    return temp;
}

inline StiKTNBidirectionalIterator StiKTNBidirectionalIterator::end()
{
    return StiKTNBidirectionalIterator(0);
}

#endif
