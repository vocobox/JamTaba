#include "WavePeakPanel.h"

#include <QPainter>
#include <QDebug>

const int WavePeakPanel::peaksRectWidth = 2;
const int WavePeakPanel::peaksPad = 0;

WavePeakPanel::WavePeakPanel(QWidget* parent)
    :   QWidget(parent),
      maxPeaks(0)
{
    setAutoFillBackground(false);

    recreatePeaksArray();
}

void WavePeakPanel::recreatePeaksArray(){
    this->maxPeaks = computeMaxPeaks();
    peaksArray.resize(maxPeaks);
    peaksArray.clear();
}

int WavePeakPanel::computeMaxPeaks(){
    return width() / (peaksRectWidth + peaksPad);
}

void WavePeakPanel::clearPeaks(){
    peaksArray.clear();
    update();
}

void WavePeakPanel::resizeEvent( QResizeEvent* e ){
    Q_UNUSED(e)
    recreatePeaksArray();
}


QSize WavePeakPanel::minimumSizeHint()  const{
    if(isEnabled()){
        return QSize(0, 80);
    }
    return QWidget::minimumSizeHint();
}

void WavePeakPanel::addPeak(float peak) {
    if(peaksArray.size() >= maxPeaks){
        peaksArray.clear();
    }
    peaksArray.push_back(peak);
    update();//repaint
}


void WavePeakPanel::paintEvent(QPaintEvent */*event*/){
    if (isVisible()) {
        QPainter painter(this);
        //painter.drawRect(QRect(0, 0, width()-1, height()-1));
        //qWarning() << "size: " << peaksArray.size();
        uint size = peaksArray.size();
        for (uint i = 0; i < size; i++) {
            int alpha = ((float)(i+1)/(size)) * 255;
            QColor color(90, 90, 90, alpha);
            int xPos = i * (peaksRectWidth + peaksPad);
            drawPeak(&painter, xPos, peaksArray[i], color);
        }
    }
}


void WavePeakPanel::drawPeak(QPainter* g, int x, float peak, QColor color) {
    int peakHeight = (int) (height() * peak);
    if (peakHeight == 0) {
        peakHeight = 2;
    }
    int y = (height() - peakHeight) / 2;

    g->fillRect(x, y, peaksRectWidth, peakHeight, color);
}

