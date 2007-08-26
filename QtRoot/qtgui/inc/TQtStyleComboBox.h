// @(#)root/gui:$Name:  $:$Id: TQtStyleComboBox.h,v 1.3 2007/08/26 17:46:59 fine Exp $
// Author: Valeri Fine 07/07/2006


#ifndef ROOT_TQtStyleComboBox
#define ROOT_TQtStyleComboBox

#include <qcombobox.h>

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// The TQtLineStyleComboBox user callable and it creates                //
// a combobox for selecting the line style.                             //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

class TEmbeddedPad;

class TQtStyleComboBox : public QComboBox {

 protected:
    TEmbeddedPad  *fPad;         // TPad to render the ROOT attributes
    int           fItemListSize; // The number of the items to constuct ComboBox
    
    virtual void Build();
    TEmbeddedPad  &Pad();
    virtual void AddItem(QPixmap &pix, QString &str);
 protected:
    virtual void resizeEvent(QResizeEvent *);

 public:
    TQtStyleComboBox(int listSize, QWidget *parent=0, QString name = QString::null);
    virtual ~TQtStyleComboBox();
    virtual void AddItem(int style, bool savepad=TRUE) = 0;
    virtual void SetCurrentItem(int style);
//    virtual void SavePrimitive(ostream &out, Option_t *option = "");
};

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// The TQtLineStyleComboBox user callable and it creates                //
// a combobox for selecting the line style.                             //
//                                                                      //
//////////////////////////////////////////////////////////////////////////


class TQtLineStyleComboBox : public TQtStyleComboBox {

protected:
   virtual void AddItem(QPixmap &pix, QString &str) {TQtStyleComboBox::AddItem(pix,str);}

public:
    TQtLineStyleComboBox(QWidget *parent=0,const QString name="lineStyle");
    virtual ~TQtLineStyleComboBox(){}
    virtual void AddItem(int style, bool savepad=TRUE);
};

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// The TQtLineWidthComboBox user callable and it creates                //
// a combobox for selecting the line width.                             //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

class TQtLineWidthComboBox : public TQtStyleComboBox {
protected:
   virtual void AddItem(QPixmap &pix, QString &str) {TQtStyleComboBox::AddItem(pix,str);}
   
public:
   TQtLineWidthComboBox(QWidget *parent=0,const QString name="Linewidth");
   virtual ~TQtLineWidthComboBox(){}
   virtual void AddItem(int style, bool savepad=TRUE);
};


//////////////////////////////////////////////////////////////////////////
//                                                                      //
// The TQtFontTypeComboBox is user callable and it creates              //
// a combobox for selecting the font.                                   //
//                                                                      //
//////////////////////////////////////////////////////////////////////////


class TQtFontComboBox : public TQtStyleComboBox {

protected:
   virtual void AddItem(QPixmap &pix, QString &str) {TQtStyleComboBox::AddItem(pix,str);}

public:
   TQtFontComboBox(QWidget *parent=0, const QString name="fontselector");
   virtual ~TQtFontComboBox(){;}
   virtual void AddItem(int style, bool savepad=TRUE);
};

#endif
