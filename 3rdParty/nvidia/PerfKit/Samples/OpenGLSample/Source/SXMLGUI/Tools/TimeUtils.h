#ifndef TIME_UTILS_H
#define TIME_UTILS_H

#include "XMLUtils.h"

#if !defined(WIN32) && !defined(WIN64)
#define __int64 long long
#endif

/*******************************************************************************************/
/*Timer                                                                                    */
/*                                                                                         */
/*******************************************************************************************/

class Timer
{
  public:
    static void intialize();

  /*
   *Read the system's current time and return it
   **/
    static __int64 getCurrentTime();

   /*
    *Return the timer's precision (frequency)
    **/
    static __int64 getPrecision();

   /*
    *Return the elapsed time in seconds
    **/
    static float getElapsedTimeSeconds(__int64 lastTime);
};

/*******************************************************************************************/
/*FPSCounter                                                                               */
/*                                                                                         */
/*******************************************************************************************/

class FPSCounter
{
  public:
    FPSCounter();

    const float getFrameInterval() const;
    const float getElapsedTime()   const;
    const float getFPS()           const;

    virtual void  markFrameStart();
    virtual void  markFrameEnd();

  protected:
    __int64  frameStart;       // Mark the beginning of a frame
    float    frameInterval,    //The delay between two frames
             elapsedTime,
             internalFPS,      //An internal FPS counter
             tickCounter,      //This will count the clock ticks
             fps;              //The number of frames per second

};

/*******************************************************************************************/
/*Benchmark                                                                                */
/*                                                                                         */
/*******************************************************************************************/

class Benchmark : public FPSCounter, IOXMLObject
{
  private:
    std::string  logFilePath;
    float        framesCounter,
                 elapsedTime,
                 averageFPS,
                 duration,
                 minFPS,
                 maxFPS;
     bool        enabled;

  public:
    Benchmark(const std::string &logFilePath = "Results.xml");
    virtual ~Benchmark() {}

    void    setLogFilePath(const std::string &logFilePath);
    const   std::string &getLogFilePath() const;

    void    setDuration(float);

    virtual bool exportXMLSettings(const std::string &xmlPath);
    virtual bool loadXMLSettings(const TiXmlElement *element);

    virtual void  markFrameEnd();

    float  getTotalDuration() const;
    float  getAverageFrames() const;
    float  getTotalFrames()   const;
    float  getDuration()      const;
    float  getMinFPS()        const;
    float  getMaxFPS()        const;

    bool    exportResults();
    void    setEnabled(bool);

    bool    isEnabled()  const;
    bool    isRunning()  const;
};

#endif
