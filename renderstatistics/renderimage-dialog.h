#ifndef H_RENDERSTATISTICS_RENDERIMAGE_DIALOG
#define H_RENDERSTATISTICS_RENDERIMAGE_DIALOG

// Render Statistics Headers
#include "logger.h"

// DAZ Studio SDK Headers
#include "dzbasicdialog.h"
#include "dzstyle.h"

// Qt SDK Headers
#include "QtCore\qstring.h"
#include "QtGui\qimage.h"
#include "QtGui\qlabel.h"
#include "QtGui\qlayout.h"
#include "QtGui\qwidget.h"

#define RENDER_IMAGE_DIALOG_WIDTH 600

/*
 * Class: RenderImageDialog
 * Description: Dialog for showing rendered image.
 */
class RenderImageDialog : public DzBasicDialog {

  Q_OBJECT

public:
  RenderImageDialog(QWidget *parent, QString renderImageFilename);
  virtual ~RenderImageDialog();


private:
  RenderStatisticsLogger *logger;
  QImage *renderImage;
  QLabel *errorLabel;

};

#endif