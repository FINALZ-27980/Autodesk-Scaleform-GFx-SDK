#include "TimeUtils.h"
#include "GenUtils.h"

/*******************************************************************************************/
/*Timer                                                                                    */
/*                                                                                         */
/*******************************************************************************************/

#if !defined(WIN32) && !defined(WIN64) // not windows, assuming POSIX
  #include <cstdlib>
  #include <sys/time.h>
  #include <unistd.h>
#define secondsToMicro 1000000

#else // windows
  #include <windows.h>

LARGE_INTEGER currentTime,
              frequency;
#endif


void Timer::intialize()
{
#if defined(WIN32) || defined(WIN64)
  QueryPerformanceFrequency(&frequency);
#endif
}


__int64 Timer::getCurrentTime(){
#if defined(WIN32) || defined(WIN64)
  QueryPerformanceCounter(&currentTime);
  return currentTime.QuadPart;
#else
  timeval internalTime;
  gettimeofday(&internalTime, NULL);
  return (__int64) internalTime.tv_sec * secondsToMicro + internalTime.tv_usec;
#endif
}

__int64 Timer::getPrecision(){
#if defined(WIN32) || defined(WIN64)
  return frequency.QuadPart;
#else
  return secondsToMicro;
#endif
}

float Timer::getElapsedTimeSeconds(__int64 lastTime){
#if defined(WIN32) || defined(WIN64)
  return float(getCurrentTime() - lastTime)/frequency.QuadPart;
#else
  return float(getCurrentTime() - lastTime) /secondsToMicro;
#endif
}

/*******************************************************************************************/
/*FPSCounter                                                                               */
/*                                                                                         */
/*******************************************************************************************/

FPSCounter::FPSCounter()
{
  Timer::intialize();
  frameInterval = 0.0f;
  internalFPS   = 0.0f;
  tickCounter   = 0.0f;
  elapsedTime   = 0.0f;
  frameStart    =    0;
  fps           = 0.0f;
}

const float FPSCounter::getFrameInterval() const { return frameInterval; }
const float FPSCounter::getElapsedTime()   const { return elapsedTime;   }
const float FPSCounter::getFPS()           const { return fps;           }

void FPSCounter::markFrameStart()
{
  frameStart = Timer::getCurrentTime();
}

void FPSCounter::markFrameEnd()
{
  if(frameStart)
  {
    frameInterval = Timer::getElapsedTimeSeconds(frameStart);
    tickCounter  += frameInterval;
    elapsedTime  += frameInterval;
    internalFPS++;

    if(tickCounter >= 1.0f)
    {
      fps          = internalFPS/tickCounter;
      internalFPS  = 0.0f;
      tickCounter  = 0.0f;
    }
  }
}

/*******************************************************************************************/
/*Benchmark                                                                                */
/*                                                                                         */
/*******************************************************************************************/

Benchmark::Benchmark(const std::string &logFilePath) : FPSCounter() , IOXMLObject("Benchmark")
{
  setLogFilePath(logFilePath);
  framesCounter  =   0.0f;
  elapsedTime    =   0.0f;
  averageFPS     =   0.0f;
  duration       =  10.0f;
  enabled        =   true;
  minFPS         = 10.0e5;
  maxFPS         =   0.0f;
}

bool   Benchmark::loadXMLSettings(const TiXmlElement *element)
{
  if(!XMLArbiter::inspectElementInfo(element, "Benchmark"))
    return  Logger::writeErrorLog("NULL Benchmark node");

  setLogFilePath(element->Attribute("logFilePath"));
  setDuration(XMLArbiter::fillComponents1f(element, "duration", duration));
  setEnabled(XMLArbiter::analyzeBooleanAttr(element, "enabled", enabled));
  return true;
}

bool Benchmark::exportXMLSettings(const std::string &xmlPath)
{
  if(!xmlPath.size())
  {
    if(!logFilePath.size())
      return Logger::writeErrorLog("Cannot export Benchmark results -> NULL log file path");
  }
  else
    logFilePath = xmlPath;

  ofstream exporter(logFilePath.c_str());

  exporter << "<BMResults  framesCount = \"" << framesCounter << "\"\n"
           << "            elapsedTime = \"" << elapsedTime   << "\"\n"
           << "            duration    = \"" << duration      << "\"\n"
           << "            averageFPS  = \"" << averageFPS    << "\"\n"
           << "            minFPS      = \"" << minFPS        << "\"\n"
           << "            maxFPS      = \"" << maxFPS        << "\"/>\n";

  exporter.close();
  return true;
}

void Benchmark::setLogFilePath(const std::string &lFilePath)
{
  logFilePath = lFilePath.size() ? lFilePath : logFilePath;
}

const std::string &Benchmark::getLogFilePath() const
{
  return logFilePath;
}

void Benchmark::markFrameEnd()
{

  if(frameStart)
  {
    frameInterval = Timer::getElapsedTimeSeconds(frameStart);
    tickCounter  += frameInterval;
    elapsedTime  += frameInterval*enabled;
    internalFPS++;

    if(tickCounter >= 1.0f)
    {
      fps          = internalFPS/tickCounter;
      internalFPS  = 0.0f;
      tickCounter  = 0.0f;
    }
  }

  framesCounter += 1.0f;

  if(elapsedTime >= duration || !enabled)
    return;

  if(fps && elapsedTime)
  {
    averageFPS = framesCounter/elapsedTime;
    minFPS     = (fps < minFPS) ? fps : minFPS;
    maxFPS     = (fps > maxFPS) ? fps : maxFPS;
  }
}

void   Benchmark::setEnabled(bool on)
{
  enabled = on;
}

bool   Benchmark::isEnabled() const
{
  return enabled;
}

bool Benchmark::isRunning()   const
{
  return (elapsedTime < duration);
}

void Benchmark::setDuration(float dur)
{ 
  duration = clamp(dur, 1.0f, 3600.0f);
}

float  Benchmark::getTotalDuration() const { return elapsedTime;       }
float  Benchmark::getAverageFrames() const { return averageFPS;        }
float  Benchmark::getTotalFrames()   const { return framesCounter;     }
float  Benchmark::getDuration()      const { return duration;          }
float  Benchmark::getMinFPS()        const { return minFPS;            }
float  Benchmark::getMaxFPS()        const { return maxFPS;            }
