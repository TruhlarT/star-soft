#if !defined(EDITABLEPARAMETER_H_INCLUDED_)
#define EDITABLEPARAMETER_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ConstrainedParameter.h"
#include "StiObjectFactoryInterface.h"

class EditableParameter : public ConstrainedParameter
{
 public:

  EditableParameter();
  EditableParameter(const string & name, 
		    const string & description,
		    double value, 
		    double defaultValue, 
		    double min, 
		    double max,
		    double increment,
		    int    type,
		    int    key);
  EditableParameter(const EditableParameter & parameter);
  virtual ~EditableParameter();
  
  const EditableParameter & operator=(const EditableParameter & parameter);
  
  double  getIncrement() const;
  void    setIncrement(double increment);
  void    set(const string & name, 
	      const string & description,
	      double value, 
	      double defaultValue, 
	      double min, 
	      double max,
	      double increment,
	      int    type,
	      int    key);
  void    reset();

 protected:
  
  double  _increment;
  
};

inline const EditableParameter & EditableParameter::operator=(const EditableParameter & parameter)
{
  if (&parameter==this)
    return *this;  
  _key      = parameter._key;
  _type      = parameter._type;
  _value     = parameter._value; 
  _minimum   = parameter._minimum;
  _maximum   = parameter._maximum;
  _default   = parameter._default;
  _increment = parameter._increment;
  return *this;
}

inline double  EditableParameter::getIncrement() const
{
  return _increment;
}

inline void    EditableParameter::setIncrement(double increment)
{
  _increment = increment;
}

inline void    EditableParameter::reset()
{
  _value = _default;
}

/*! EditableParameter factory
 */
class EditableParameterFactory : public StiObjectFactoryInterface<Parameter>
{
public:
    ///This is the only constructor available.
    EditableParameterFactory(const string& newName, 
		      int original=-1, int 
		      incremental=-1, 
		      int maxInc=-1);
    ///Default destructor.
    virtual ~EditableParameterFactory();
    
protected:
    ///Return a pointer to a new Parameter object on the heap.
    virtual void* makeNewObject() const;
    
private:
    EditableParameterFactory(); // no imp
};

#endif // !defined(EDITABLEPARAMETER_H_INCLUDED_)
