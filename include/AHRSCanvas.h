/*
RoscoPi Stratux AHRS Display
(c) 2018 Allen K. Lair, Unexploded Minds
*/

#ifndef __AHRSCANVAS_H__
#define __AHRSCANVAS_H__

#include <QWidget>
#include <QPixmap>
#include <QMap>
#include <QList>
#include <QDateTime>

#include "StratuxStreams.h"
#include "Canvas.h"
#include "TrafficMath.h"


class AHRSCanvas : public QWidget
{
    Q_OBJECT

public:
    explicit AHRSCanvas( QWidget *parent = 0 );
    ~AHRSCanvas();

    void    showAllTraffic( bool bAll );
    void    showOutside( bool bOut );
    void    showAirports( Canvas::ShowAirports eShow );
    void    setPortrait( bool bPortrait ) { m_bPortrait = bPortrait; }
    void    setFuelTanks( FuelTanks tanks ) { m_tanks = tanks; }
    void    timerReminder( int iMinutes, int iSeconds );
    Canvas *canvas() { return m_pCanvas; }
#if defined( Q_OS_ANDROID )
    void    orient( bool bPortrait );
#endif
    int     magDev() { return m_iMagDev; }

    QPixmap *m_pHeadIndicator;

public slots:
    void init();
    void situation( StratuxSituation s );
    void traffic( int iICAO, StratuxTraffic t );

protected:
    void paintEvent( QPaintEvent *pEvent );
    void mouseReleaseEvent( QMouseEvent *pEvent );
    void mousePressEvent( QMouseEvent *pEvent );
    void timerEvent( QTimerEvent *pEvent );

private:
    void updateTraffic( QPainter *pAhrs, CanvasConstants *c );
    void updateAirports( QPainter *pAhrs, CanvasConstants *c );
    void cullTrafficMap();
    void zoomIn();
    void zoomOut();
    void handleScreenPress( const QPoint &pressPt );
    void paintPortrait();
    void paintLandscape();
    void paintInfo( QPainter *pAhrs, CanvasConstants *c );
    void paintTimer( QPainter *pAhrs, CanvasConstants *c );
    void paintSwitchNotice( QPainter *pAhrs, CanvasConstants *c );
    void loadSettings();

    Canvas *m_pCanvas;

    bool      m_bInitialized;
    QPixmap   m_planeIcon;
    QPixmap   m_headIcon;
    QPixmap   m_windIcon;
    int       m_iHeadBugAngle;
    int       m_iWindBugAngle;
    int       m_iWindBugSpeed;
    QPixmap  *m_pRollIndicator;
    QPixmap  *m_pAltTape;
    QPixmap  *m_pSpeedTape;
    QPixmap  *m_pVertSpeedTape;
    QPixmap  *m_pZoomInPixmap;
    QPixmap  *m_pZoomOutPixmap;
    QPixmap  *m_pMagHeadOffLessPixmap;
    QPixmap  *m_pMagHeadOffMorePixmap;
    int       m_iDispTimer;
    int       m_iUpdateCount;
    bool      m_bUpdated;
    bool      m_bShowGPSDetails;
    double    m_dZoomNM;
    bool      m_bShowAllTraffic;
    bool      m_bShowOutside;
    bool      m_bShowOutsideHeading;
    bool      m_bPortrait;
    bool      m_bLongPress;
    QDateTime m_longPressStart;
    bool      m_bShowCrosswind;
    int       m_iTimerMin;
    int       m_iTimerSec;
    int       m_iMagDev;
    bool      m_bDisplayTanksSwitchNotice;

    Canvas::ShowAirports m_eShowAirports;
    QList<Airport>       m_airports;
    FuelTanks            m_tanks;
};

#endif // __AHRSCANVAS_H__
