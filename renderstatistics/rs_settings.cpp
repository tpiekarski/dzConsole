/*
* Project:   dzUtilities::RenderStatistics
* Github:    https://github.com/tpiekarski/dzUtilities
* Copyright: (c) 2017-2018 Thomas Piekarski <t.piekarski@deloquencia.de>
* License:   Mozilla Public License, v. 2.0
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
*
*/

#include "rs_constants.h"
#include "rs_settings.h"
#include <dzapp.h>

RenderStatisticsSettings::RenderStatisticsSettings(RenderStatisticsLogger* logger) {
  setObjectName("RenderStatisticsSettings");
  this->logger = logger;
  settings = new DzAppSettings(RS_SETTINGS_PATH);
  scalingAlgorithms << QString(RS_SCALING_FAST_TRANSFORMATION) << QString(RS_SCALING_SMOOTH_TRANSFORMATION);

  connect(dzApp, SIGNAL(starting()), this, SLOT(loadSettings()));
  connect(dzApp, SIGNAL(closing()), this, SLOT(saveSettings()));
}

RenderStatisticsSettings::~RenderStatisticsSettings() {
  if (settings != nullptr) {
    delete settings;
    settings = nullptr;
  }
}

void RenderStatisticsSettings::setRenderImageWidth(const int renderImageWidth) {
  this->renderImageWidth = renderImageWidth;
}

void RenderStatisticsSettings::setScalingAlgorithm(const QString scalingAlgorithm) {
  if (scalingAlgorithm == RS_SCALING_FAST_TRANSFORMATION) {
    this->scalingAlgorithm = Qt::TransformationMode::FastTransformation;
  } else if (scalingAlgorithm == RS_SCALING_SMOOTH_TRANSFORMATION){
    this->scalingAlgorithm = Qt::TransformationMode::SmoothTransformation;
  } else {
    this->scalingAlgorithm = RS_DEFAULT_SCALING_ALGORITHM;
  }
}

void RenderStatisticsSettings::saveSettings() {
  settings->setIntValue(RS_SETTINGS_RENDERIMAGE_WIDTH_KEY, renderImageWidth);
  settings->setIntValue(RS_SETTINGS_SCALING_ALGORITHM_KEY, (int) scalingAlgorithm);
}

void RenderStatisticsSettings::loadSettings() {
  bool readSuccess = false;

  int storedRenderImageWidth = settings->getIntValue(
    RS_SETTINGS_RENDERIMAGE_WIDTH_KEY, RS_DEFAULT_RENDER_IMAGE_DIALOG_WIDTH, &readSuccess
  );

  if (readSuccess && validateRenderImageWidth(storedRenderImageWidth)) {
    renderImageWidth = storedRenderImageWidth;
  } else {
    logger->log(RS_SETTINGS_RENDERIMAGE_WIDTH_READING_FAILED_MSG);
    renderImageWidth = RS_DEFAULT_RENDER_IMAGE_DIALOG_WIDTH;
  }

  int storedScalingAlgorithm = settings->getIntValue(
    RS_SETTINGS_SCALING_ALGORITHM_KEY, RS_DEFAULT_SCALING_ALGORITHM, &readSuccess
  );

  if (readSuccess) {
    scalingAlgorithm = (Qt::TransformationMode) storedScalingAlgorithm;
  } else {
    logger->log(RS_SETTINGS_SCALING_ALGORITHM_READING_FAILED_MSG);
    scalingAlgorithm = RS_DEFAULT_SCALING_ALGORITHM;
  }
}

bool RenderStatisticsSettings::validateRenderImageWidth(int newRenderImageWidth) {
  return newRenderImageWidth >= RS_RENDER_IMAGE_DIALOG_MIN_WIDTH && newRenderImageWidth <= RS_RENDER_IMAGE_DIALOG_MAX_WIDTH;
}
