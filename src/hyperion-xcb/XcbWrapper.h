#pragma once

// QT includes
#include <QTimer>

// Hyperion-Xcb includes
#include <grabber/xcb/XcbGrabber.h>
#include <hyperion/GrabberWrapper.h>

//Utils includes
#include <utils/VideoMode.h>

class XcbWrapper : public QObject
{
	Q_OBJECT
public:
	XcbWrapper( int updateRate_Hz=GrabberWrapper::DEFAULT_RATE_HZ,
				int pixelDecimation=GrabberWrapper::DEFAULT_PIXELDECIMATION,
				int cropLeft=0, int cropRight=0,
				int cropTop=0, int cropBottom=0
				);

	const Image<ColorRgb> & getScreenshot();

	///
	/// Starts the timed capturing of screenshots
	///
	void start();

	void stop();

	bool screenInit();

signals:
	void sig_screenshot(const Image<ColorRgb> & screenshot);

public slots:
	///
	/// Set the video mode (2D/3D)
	/// @param[in] mode The new video mode
	///
	void setVideoMode(const VideoMode videoMode);

private slots:
	///
	/// Performs a single screenshot capture and publishes the capture screenshot on the screenshot
	/// signal.
	///
	void capture();

private:
	/// The QT timer to generate capture-publish events
	QTimer _timer;

	/// The grabber for creating screenshots
	XcbGrabber _grabber;

	Image<ColorRgb>  _screenshot;

	// prevent cont dimension updates
	bool _inited = false;
};
